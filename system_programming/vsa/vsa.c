#include <assert.h>

#include "vsa.h"

#define MAGIC_NUM (15)
#define VSA_SIZE sizeof(VSA_t)
#define TRUE (1)
#define FALSE (0)
#define SWITCH_SIGN (-1)

struct variable_sized_allocator
{
	#ifdef NDEBUG
		long size;
	#else
    	long size;
    	long magic_num;
    #endif 	
};

VSA_t *VSAInit(void *memory, size_t memory_size)
{
	VSA_t *allocator = NULL;
	VSA_t *end_dummy = NULL;
	assert(NULL != memory);

	if (memory_size < VSA_SIZE)
	{
		return NULL;
	}

	allocator = (VSA_t *)memory;
	 
	#ifdef NDEBUG	
	#else
    	allocator->magic_num = MAGIC_NUM;
    #endif 
	allocator->size = memory_size - (2 * VSA_SIZE);
	end_dummy =(VSA_t *)( (char *)memory + memory_size - VSA_SIZE);

    #ifdef NDEBUG	
	#else
    	end_dummy->magic_num = MAGIC_NUM;
	#endif

	end_dummy->size = 0;
    return allocator;	
}

static VSA_t *NextChunck(VSA_t *allocator)
{
	char *allocator_as_char = (char *)allocator;
	assert(NULL != allocator);
	if(0 > allocator->size)
	{
		return (VSA_t *)(allocator_as_char + VSA_SIZE + allocator->size * SWITCH_SIGN);
	}
	else
	{
		return (VSA_t *)(allocator_as_char + VSA_SIZE + allocator->size);
	} 
}
static int IsChunkBigEnough(VSA_t *allocator, size_t size_in_bytes)
{
	assert(NULL != allocator);

	if (allocator->size < (long)size_in_bytes)
	{
		return FALSE;
	}
	return TRUE;
}
static void *SplitChunck(VSA_t *allocator, size_t size_in_bytes)
{
	VSA_t *next_allocator = NULL;

	assert(NULL != allocator);

	if (allocator->size > (long)(size_in_bytes + VSA_SIZE))
	{
		next_allocator =(VSA_t *)( (char *)allocator + VSA_SIZE + size_in_bytes);
		#ifdef NDEBUG
			next_allocator->size = allocator->size - VSA_SIZE - size_in_bytes;
		#else
			next_allocator->size = allocator->size - VSA_SIZE - size_in_bytes;
			next_allocator->magic_num = MAGIC_NUM;
		#endif
	}

	allocator->size = size_in_bytes * SWITCH_SIGN;	
	return (void *)((char *)allocator + VSA_SIZE);
}

static int IsNextChunckAvailable(VSA_t *allocator)
{
	VSA_t * next_chunck = NULL;

	assert(NULL != allocator);

	next_chunck = NextChunck(allocator);

	if(0 < next_chunck->size)
	{
		return TRUE;
	}

	return FALSE;
}
static int IsChunckAvailable(VSA_t *allocator)
{
	assert(NULL != allocator);

	return (allocator->size > 0);
}
static void MergeChuncks(VSA_t *allocator)
{
	VSA_t * next_chunck = NULL;

	assert(NULL != allocator);

	next_chunck = NextChunck(allocator);

	allocator->size += next_chunck->size + VSA_SIZE;
}

void *VSAAlloc(VSA_t *allocator, size_t size_in_bytes)
{
	assert(NULL != allocator);
	while (0 != allocator->size)
	{
		if (IsChunckAvailable(allocator))
		{
			if (IsChunkBigEnough(allocator, size_in_bytes))
			{
				return SplitChunck(allocator, size_in_bytes);
			}
			else 
			{
				while (IsNextChunckAvailable(allocator))
				{
					MergeChuncks(allocator);

					if (IsChunkBigEnough(allocator, size_in_bytes))
					{
						return SplitChunck(allocator, size_in_bytes);
					}
				}
			}
		}
		allocator = NextChunck(allocator);
	}
	return NULL;
}


void VSAFree(void *block)
{
	VSA_t* vsa = NULL;
	
	assert(NULL != block);

	vsa = (VSA_t*)((char *)block - VSA_SIZE);
	
	#ifdef NDEBUG

	#else
		if(MAGIC_NUM != vsa->magic_num )
		{
			return;
		}
	#endif

	vsa->size = vsa->size * SWITCH_SIGN;
}

size_t VSALargestChunkAvailable(VSA_t *allocator)
{
	size_t largest_chunk_size = 0;

	assert(NULL != allocator);

	largest_chunk_size = 0;
	while (0 != allocator->size)
	{
		if (IsChunckAvailable(allocator))
		{
			while (IsNextChunckAvailable(allocator))
			{
				MergeChuncks(allocator);
			}
			if ((long)largest_chunk_size < allocator->size)
			{
				largest_chunk_size = allocator->size;
			}
		}
		allocator = NextChunck(allocator);
	}
	return largest_chunk_size;
}