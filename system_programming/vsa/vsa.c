#include <assert.h>  /*assert*/

#include "vsa.h"

#define MAGIC_NUM (15)
#define TRUE (1)
#define FALSE (0)
#define SWITCH_SIGN (-1)

struct variable_sized_allocator
{
	long size;
	#ifndef NDEBUG	
    	long magic_num;
    #endif 	
};

#define VSA_SIZE sizeof(VSA_t)
#define DUMMY_SIZE sizeof(VSA_t)




VSA_t *VSAInit(void *memory, size_t memory_size)
{
	VSA_t *allocator = NULL;
	VSA_t *end_dummy = NULL;

	assert(NULL != memory);

	if (memory_size < (VSA_SIZE + DUMMY_SIZE + 1))
	{
		return NULL;
	}

	allocator = (VSA_t *)memory;
	allocator->size = memory_size - (VSA_SIZE + DUMMY_SIZE);
	
	end_dummy = (VSA_t *)((char *)memory + memory_size - VSA_SIZE);
	end_dummy->size = 0;

	#ifndef NDEBUG	
    	allocator->magic_num = MAGIC_NUM;
    	end_dummy->magic_num = MAGIC_NUM;
    #endif 

    return allocator;	
}



static VSA_t *NextChunk(VSA_t *allocator)
{
	char *allocator_as_char = (char *)allocator;

	assert(NULL != allocator);
	assert(MAGIC_NUM == allocator->magic_num);

	if(0 > allocator->size)
	{
		return (VSA_t *)(allocator_as_char + VSA_SIZE + (allocator->size * SWITCH_SIGN));
	}
	
	return (VSA_t *)(allocator_as_char + VSA_SIZE + allocator->size);	
}

static int IsChunkBigEnough(VSA_t *allocator, size_t size_in_bytes)
{
	assert(NULL != allocator);
	assert(MAGIC_NUM == allocator->magic_num);

	if (allocator->size < (long)size_in_bytes)
	{
		return FALSE;
	}

	return TRUE;
}

static void *SplitChunk(VSA_t *allocator, size_t size_in_bytes)
{
	VSA_t *next_allocator = NULL;

	assert(NULL != allocator);
	assert(MAGIC_NUM == allocator->magic_num);

	if (allocator->size > (long)(size_in_bytes + VSA_SIZE))
	{
		next_allocator =(VSA_t *)((char *)allocator + VSA_SIZE + size_in_bytes);
		next_allocator->size = allocator->size - VSA_SIZE - size_in_bytes;
		
		#ifndef NDEBUG
			next_allocator->magic_num = MAGIC_NUM;
		#endif

		allocator->size = (long)size_in_bytes * SWITCH_SIGN;
	}
	else
	{
		allocator->size = allocator->size * SWITCH_SIGN;
	}
	
	return (void *)((char *)allocator + VSA_SIZE);
}

static int IsNextChunkAvailable(VSA_t *allocator)
{
	VSA_t *next_chunk = NULL;

	assert(NULL != allocator);
	assert(MAGIC_NUM == allocator->magic_num);

	next_chunk = NextChunk(allocator);
	
	return (0  < next_chunk->size);
}

static int IsChunkAvailable(VSA_t *allocator)
{
	assert(NULL != allocator);
	assert(MAGIC_NUM == allocator->magic_num);

	return (allocator->size > 0);
}

static void MergeChunks(VSA_t *allocator)
{
	VSA_t *next_chunk = NULL;

	assert(NULL != allocator);
	assert(MAGIC_NUM == allocator->magic_num);

	next_chunk = NextChunk(allocator);

	allocator->size += next_chunk->size + (long)VSA_SIZE;
}

void *VSAAlloc(VSA_t *allocator, size_t size_in_bytes)
{
	assert(NULL != allocator);
	assert(MAGIC_NUM == allocator->magic_num);
	
	while (0 != allocator->size)
	{
		if (IsChunkAvailable(allocator))
		{
			if (IsChunkBigEnough(allocator, size_in_bytes))
			{
				return SplitChunk(allocator, size_in_bytes);
			}
			else 
			{
				while (IsNextChunkAvailable(allocator))
				{
					MergeChunks(allocator);

					if (IsChunkBigEnough(allocator, size_in_bytes))
					{
						return SplitChunk(allocator, size_in_bytes);
					}
				}
			}
		}
		allocator = NextChunk(allocator);
	}

	return NULL;
}

void VSAFree(void *block)
{
	VSA_t* vsa = NULL;
	
	assert(NULL != block);

	vsa = (VSA_t*)((char *)block - VSA_SIZE);

	assert(MAGIC_NUM == vsa->magic_num);

	vsa->size = vsa->size * SWITCH_SIGN;
}

size_t VSALargestChunkAvailable(VSA_t *allocator)
{
	size_t largest_chunk_size = 0;

	assert(NULL != allocator);
	assert(MAGIC_NUM == allocator->magic_num);

	largest_chunk_size = 0;

	while (0 != allocator->size)
	{
		if (IsChunkAvailable(allocator))
		{
			while (IsNextChunkAvailable(allocator))
			{
				MergeChunks(allocator);
			}
			if ((long)largest_chunk_size < allocator->size)
			{
				largest_chunk_size = allocator->size;
			}
		}
		allocator = NextChunk(allocator);
	}

	return largest_chunk_size;
}

int WasAllMemoryFreed(VSA_t* pool)
{
	assert(NULL != pool);
	assert(MAGIC_NUM == pool->magic_num);

	while (0 != pool->size)
	{
		if (!IsChunkAvailable(pool))
		{
			return FALSE;
		}

		pool = NextChunk(pool);
	}
	return TRUE;
}

#ifndef NDEBUG
	int IsBlockValidDebugMode(void *block)
	{

		VSA_t* vsa = NULL;
		
		assert(NULL != block);

		vsa = (VSA_t*)((char *)block - VSA_SIZE);

		return MAGIC_NUM == vsa->magic_num;
	}
#endif