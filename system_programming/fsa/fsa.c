#include <assert.h>/*assert*/
#include "fsa.h"

struct fixed_size_allocator
{
	size_t block_size;
	size_t num_free_blocks;
	size_t next_free;
};

#define WORD_SIZE sizeof(size_t)
#define FSA_SIZE sizeof(FSA_t)

static size_t FindAllignedBlockSize(size_t block_size);


size_t FSASuggestSize(size_t block_size, size_t num_of_blocks)
{
	return FindAllignedBlockSize(block_size) * num_of_blocks + FSA_SIZE;
}
static size_t FindAllignedBlockSize(size_t block_size)
{
	return block_size + (WORD_SIZE - block_size % WORD_SIZE) % WORD_SIZE;
}
static void InitAllBlocks(FSA_t *fsa, size_t memory_size)
{
	char *runner = ((char *)fsa + fsa->next_free);
	while(runner < (char *)fsa + memory_size )
	{
		*(size_t *)runner = (size_t)(runner - (char*)fsa + fsa->block_size);
		runner += fsa->block_size;
	}
}

FSA_t *FSAInit(void *memory, size_t memory_size, size_t block_size)
{
	FSA_t *fsa = memory;
	assert(NULL != fsa);
	if(memory_size <= FSA_SIZE + FindAllignedBlockSize(block_size))
	{
		return NULL;
	}
	fsa->block_size = FindAllignedBlockSize(block_size) ;
	fsa->num_free_blocks = (memory_size - FSA_SIZE) / (fsa->block_size ) ;
	fsa->next_free = FSA_SIZE;
	InitAllBlocks(fsa, memory_size);
	return fsa;
}


void *FSAAlloc(FSA_t *allocator)
{
	void *alloc_block = NULL;
	assert(NULL != allocator);
	if(0 == allocator->num_free_blocks)
	{
		return NULL;
	}
	alloc_block = (char *)allocator + allocator->next_free;
	allocator->next_free = *(size_t *)alloc_block;
	--allocator->num_free_blocks;
	return alloc_block;
}
void FSAFree(FSA_t *allocator, void *block)
{
	assert(NULL != allocator);
	*(size_t *)block = allocator->next_free;
	allocator->next_free = (char *)block - (char *)allocator;
	++allocator->num_free_blocks;
}

size_t FSACountFree(const FSA_t *allocator)
{
	
	return allocator->num_free_blocks;
}


