#include "../../ds/utils/test.h" /*REQUIRE RUNTEST*/

#include <stdlib.h>/*malloc free*/

#include "vsa.h"

#define TRUE (1)
#define FALSE (0)


static test_status_t Test(void);
static test_status_t AdvTest(void);

int main()
{
    RUNTEST(Test);
    RUNTEST(AdvTest);
    return 0; 
}

static test_status_t Test(void)
{
    VSA_t *vsa = NULL;
    void *memory = NULL;
    void *block1 = NULL;
    void *block2 = NULL;
    void *block3 = NULL;
    void *block4 = NULL;
    void *block5 = NULL;

    size_t memory_size = 200;
    memory = malloc(sizeof(char) * memory_size);

    vsa = VSAInit(memory, memory_size);
    REQUIRE(NULL != vsa);
    REQUIRE(150 < VSALargestChunkAvailable(vsa));

    block1 =  VSAAlloc(vsa, 20);
    REQUIRE(NULL != block1);
    *(size_t *)block1 = 1;
    REQUIRE(130 < VSALargestChunkAvailable(vsa));

    block2 =  VSAAlloc(vsa, 20);
    REQUIRE(NULL != block2);
    *(size_t *)block2 = 2;

    block3 =  VSAAlloc(vsa, 20);
    REQUIRE(NULL != block3);
    *(size_t *)block3 = 3;

    block4 =  VSAAlloc(vsa, 40);
    REQUIRE(NULL != block4);
    *(size_t *)block4 = 4;

    block5 =  VSAAlloc(vsa, 20);
    REQUIRE(NULL == block5);
    REQUIRE(36 > VSALargestChunkAvailable(vsa));

    REQUIRE(1 == *(size_t *)block1);
    REQUIRE(2 == *(size_t *)block2);
    REQUIRE(3 == *(size_t *)block3);
    REQUIRE(4 == *(size_t *)block4);
    
    VSAFree(block3);
    VSAFree(block2);
    
    REQUIRE(50 < VSALargestChunkAvailable(vsa));

    block3 = VSAAlloc(vsa, 40);
    REQUIRE(NULL != block3);
     *(size_t *)block3 = 3;

    block2 =  VSAAlloc(vsa, 5);
    REQUIRE(NULL == block2);
   
    REQUIRE(1 == *(size_t *)block1);
    REQUIRE(3 == *(size_t *)block3);
    REQUIRE(4 == *(size_t *)block4);
    
    VSAFree(block4);
    
  
    memory_size = 10;
    vsa = VSAInit(memory, memory_size);
    REQUIRE(NULL == vsa);

    free(memory);

   
    return PASSED;

}
static test_status_t AdvTest(void)
{
    VSA_t *vsa = NULL;
    void *memory = NULL;
    void *block1 = NULL;
    size_t memory_size = 200;
    memory = malloc(sizeof(char) * memory_size);
    vsa = VSAInit(memory, memory_size);
    REQUIRE(NULL != vsa);
    REQUIRE(TRUE == WasAllMemoryFreed(vsa));
    block1 =  VSAAlloc(vsa, 20);
    REQUIRE(NULL != block1);
    REQUIRE(FALSE == WasAllMemoryFreed(vsa)); 
    REQUIRE(TRUE == IsBlockValidDebugMode(block1));
    REQUIRE(FALSE == IsBlockValidDebugMode((void *)((char *)block1 + 6)));
    VSAFree(block1);
    REQUIRE(TRUE == WasAllMemoryFreed(vsa)); 
    free(memory);
    return PASSED; 
}