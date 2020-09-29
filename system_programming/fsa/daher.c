#include <assert.h> /*assert*/
#include "fsa.h"

/*------------------------MACRO---------------------------*/
#define SIZE_OF_WORD (sizeof(size_t))
#define OFFSETOF(TYPE, ELEMENT) ((size_t)&(((TYPE *) 0)->ELEMENT))
#define ONE_BLOCK (1)
#define NUM_OF_SIZE_T_IN_STRUCT (3)
#define CALC_ALIGNED_BLOCK_SIZE(BLOCK) (BLOCK + SIZE_OF_WORD * !!(BLOCK % SIZE_OF_WORD) - (BLOCK % SIZE_OF_WORD))

/*---------------FUNCTION DECLERATION---------------------*/

/*-----------------------TYPEDEF--------------------------*/

/*-----------------------STRUCTS--------------------------*/

struct fixed_size_allocator
{
	size_t block_size;
	size_t num_of_free_blocks;
	size_t next_free;
};

/*--------------------------------------------------------*/

size_t FSASuggestSize(size_t block_size, size_t num_of_blocks)
{
	assert(0 < block_size);
	assert(0 < num_of_blocks);

	block_size = CALC_ALIGNED_BLOCK_SIZE(block_size)  
	printf("%lu\n",block_size );

	return (sizeof(FSA_t) + block_size * num_of_blocks);
}
/*--------------------------------------------------------*/

FSA_t *FSAInit(void *memory, size_t memory_size, size_t block_size)
{
	FSA_t *new_fsa = memory;
	size_t num_of_blocks = 0;
	size_t offset = 0;
	size_t *fsa_runner = NULL;
	assert(NULL != memory);

	if(memory_size < FSASuggestSize(block_size,ONE_BLOCK))
	{
		return NULL;
	}

	block_size = CALC_ALIGNED_BLOCK_SIZE(block_size) ;
	new_fsa->block_size = block_size;

	num_of_blocks = (memory_size - sizeof(FSA_t)) / block_size;
	new_fsa->num_of_free_blocks = num_of_blocks;

	new_fsa->next_free = sizeof(FSA_t);
	offset += sizeof(FSA_t);
	fsa_runner = (size_t*)new_fsa + NUM_OF_SIZE_T_IN_STRUCT;


	while (1 != num_of_blocks)
	{

		offset += block_size;
		*fsa_runner = offset;

		fsa_runner += block_size/SIZE_OF_WORD;

		--num_of_blocks;
	}

	*fsa_runner = 0; 

	return new_fsa;
}
/*--------------------------------------------------------*/

void *FSAAlloc(FSA_t *allocator)
{
	void *index_to_return = NULL;
	assert(NULL != allocator);

	if(allocator->next_free != 0)
	{

		index_to_return = (size_t*)allocator + allocator->next_free/SIZE_OF_WORD;
		allocator->next_free = *(size_t*)index_to_return;
		--allocator->num_of_free_blocks; 
	}
	return index_to_return;

}
/*--------------------------------------------------------*/

void FSAFree(FSA_t *allocator, void *block)
{
	assert(NULL != allocator);
	*(size_t*)block = allocator->next_free;

	allocator->next_free = (char*)block - (char*)allocator;
	++allocator->num_of_free_blocks;


}
/*--------------------------------------------------------*/

size_t FSACountFree(const FSA_t *allocator)
{
	assert(NULL != allocator);
	return allocator->num_of_free_blocks;
}
/*--------------------------------------------------------*/
