#include <stdlib.h>/*sizeof*/
#include <assert.h>/*assert*/
#include "fsa.h"

struct fixed_size_allocator
{
	size_t block_size;
	size_t num_free_blocks;
	size_t next_free;
};

#define WORD_SIZE (sizeof(size_t))

static size_t FindAllinedBlockSize(size_t block_size);


size_t FSASuggestSize(size_t block_size, size_t num_of_blocks)
{
	return FindAllinedBlockSize(block_size) * num_of_blocks + sizeof(FSA_t);
}
static size_t FindAllinedBlockSize(size_t block_size)
{
	while(0 != block_size % WORD_SIZE)
	{
		++block_size;
	}
	return block_size;
}
FSA_t *FSAInit(void *memory, size_t memory_size, size_t block_size)
{
	FSA_t *fsa = memory;
	char *runner = NULL;
	assert(NULL != fsa);
	if(memory_size <= sizeof(FSA_t) + FindAllinedBlockSize(block_size))
	{
		return NULL;
	}
	fsa->block_size = FindAllinedBlockSize(block_size) ;
	fsa->num_free_blocks = (memory_size - sizeof(FSA_t)) / (fsa->block_size ) ;
	fsa->next_free = sizeof(FSA_t);
	runner = (char *)((char *)memory + fsa->next_free);
	while(runner < (char *)fsa + memory_size )
	{
		*(size_t *)runner = (size_t)(runner - (char*)fsa + fsa->block_size);
		runner += fsa->block_size;
	}
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


