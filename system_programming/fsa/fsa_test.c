#include "test.h" /*REQUIRE RUNTEST*/

#include <stdlib.h>/*malloc free*/

#include "fsa.h"

#define TRUE (1)
#define FALSE (0)


static test_status_t StageOneTest(void);

int main()
{
	RUNTEST(StageOneTest);
	return 0; 
}

static test_status_t StageOneTest(void)
{
    FSA_t *fsa = NULL;
    void *memory = NULL;
    void *block1 = NULL;
    void *block2 = NULL;
    void *block3 = NULL;
    void *block4 = NULL;
    void *block5 = NULL;
    void *block6 = NULL;
    void *block7 = NULL;
    void *block8 = NULL;
    void *block9 = NULL;
    void *block10 = NULL;
    void *block11 = NULL;
    void *block12 = NULL;
    void *block13 = NULL;
    void *block14 = NULL;
    void *block15 = NULL;
    size_t memory_size = 64;
    REQUIRE(memory_size == FSASuggestSize(8, 5));
    memory = malloc(sizeof(char) * memory_size);
    fsa = FSAInit(memory, memory_size, (size_t)5);
    REQUIRE(NULL != fsa);
    REQUIRE(NULL != FSAAlloc(fsa));
    REQUIRE(NULL != FSAAlloc(fsa));
    
    REQUIRE(3 == FSACountFree(fsa));
   
    REQUIRE(NULL != FSAAlloc(fsa));
    REQUIRE(NULL != FSAAlloc(fsa));
    REQUIRE(NULL != FSAAlloc(fsa));
 
    REQUIRE(0 == FSACountFree(fsa));
    REQUIRE(NULL == FSAAlloc(fsa));
    
    REQUIRE(0 == FSACountFree(fsa));
    free(memory);

    memory_size = 264;
    REQUIRE(memory_size == FSASuggestSize(10, 15));
    memory = malloc(sizeof(char) * memory_size);


    fsa = FSAInit(memory, memory_size, 10);
    REQUIRE(15 == FSACountFree(fsa));
    block1 =  FSAAlloc(fsa);
    block2 =  FSAAlloc(fsa);
    block3 =  FSAAlloc(fsa);
    block4 =  FSAAlloc(fsa);
    block5 =  FSAAlloc(fsa);
    REQUIRE(10 == FSACountFree(fsa));
 	block6 =  FSAAlloc(fsa);
    block7 =  FSAAlloc(fsa);
    block8 =  FSAAlloc(fsa);
    block9 =  FSAAlloc(fsa);
    block10 =  FSAAlloc(fsa);
    REQUIRE(5 == FSACountFree(fsa));
 	block11 = FSAAlloc(fsa);
    block12 = FSAAlloc(fsa);
    block13 = FSAAlloc(fsa);
    block14 = FSAAlloc(fsa);
    block15 =  FSAAlloc(fsa);
    REQUIRE(0 == FSACountFree(fsa));

    *(size_t *)block1 = 1;
    *(size_t *)block2 = 2;
    *(size_t *)block3 = 3;
    *(size_t *)block4 = 4;
    *(size_t *)block5 = 5;
	*(size_t *)block6 =  6;
    *(size_t *)block7 =  7;
    *(size_t *)block8 =  8;
    *(size_t *)block9 =  9;
    *(size_t *)block10 = 10;
    *(size_t *)block11 = 11;
    *(size_t *)block12 = 12;
    *(size_t *)block13 = 13;
    *(size_t *)block14 = 14;
    *(size_t *)block15 = 15;

    REQUIRE(1 == *(size_t *)block1);
    REQUIRE(2 == *(size_t *)block2);
    REQUIRE(3 == *(size_t *)block3);
    REQUIRE(4 == *(size_t *)block4);
    REQUIRE(5 == *(size_t *)block5);
    REQUIRE(6 == *(size_t *)block6);
  	REQUIRE(7 == *(size_t *)block7);
    REQUIRE(8 == *(size_t *)block8);
    REQUIRE(9 == *(size_t *)block9);
    REQUIRE(10 == *(size_t *)block10);
  	REQUIRE(11 == *(size_t *)block11);
    REQUIRE(12 == *(size_t *)block12);
    REQUIRE(13 == *(size_t *)block13);
    REQUIRE(14 == *(size_t *)block14);
    REQUIRE(15 == *(size_t *)block15);

    FSAFree(fsa, block6);
    FSAFree(fsa, block7);
    FSAFree(fsa, block8);
    FSAFree(fsa, block9);
    FSAFree(fsa, block10);
    REQUIRE(5 == FSACountFree(fsa));

    block6 = FSAAlloc(fsa);
    block7 = FSAAlloc(fsa);
    block8 = FSAAlloc(fsa);
    block9 = FSAAlloc(fsa);
    block10 = FSAAlloc(fsa);

	*(size_t *)block6 =  6;
    *(size_t *)block7 =  7;
    *(size_t *)block8 =  8;
    *(size_t *)block9 =  9;
    *(size_t *)block10 = 10;

 	REQUIRE(1 == *(size_t *)block1);
    REQUIRE(2 == *(size_t *)block2);
    REQUIRE(3 == *(size_t *)block3);
    REQUIRE(4 == *(size_t *)block4);
    REQUIRE(5 == *(size_t *)block5);
    REQUIRE(6 == *(size_t *)block6);
  	REQUIRE(7 == *(size_t *)block7);
    REQUIRE(8 == *(size_t *)block8);
    REQUIRE(9 == *(size_t *)block9);
    REQUIRE(10 == *(size_t *)block10);
  	REQUIRE(11 == *(size_t *)block11);
    REQUIRE(12 == *(size_t *)block12);
    REQUIRE(13 == *(size_t *)block13);
    REQUIRE(14 == *(size_t *)block14);
    REQUIRE(15 == *(size_t *)block15);

    free(memory);

    return PASSED;

}