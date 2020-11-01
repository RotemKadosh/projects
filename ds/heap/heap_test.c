

#include "../utils/test.h"
#include "heap.h"

#define FALSE (0)
#define TRUE (1)
#define SUCCESS (0)

static test_status_t TestCreate(void);
static test_status_t TestpushIsEmptypeek(void);
static test_status_t TestRemovepopsize(void);



int main(void)
{
    RUNTEST(TestCreate);
    RUNTEST(TestpushIsEmptypeek);
    RUNTEST(TestRemovepopsize);


    return 0;
}

int CompareFunc(const void *data, const void *data_to_compare)
{
   return (*(int *)data - *(int *)data_to_compare);
}

int IsMatchFunc(const void *data, const void *param)
{
  return (*(int *)data == *(int *)param);
}

int PrintFunc(const void *data, void * param)
{
    *(int *)param = 0;

    printf("%d\n", *(int *)data);
    return 0;
}

static test_status_t TestCreate(void)
{
    Heap_ty *heap = HeapCreate(CompareFunc);
    REQUIRE(NULL != heap);

    HeapDestroy(heap);
    return PASSED;
}
static test_status_t TestpushIsEmptypeek(void)
{
    int insert1 = 5, insert2 = 16, insert3 = 3, insert4 = 12;
    int insert5 = -1, insert6 = 20, insert7 = 50, insert8 = 7;
    void *pinsert1 = &insert1;
    void *pinsert2 = &insert2;
    void *pinsert3 = &insert3;
    void *pinsert4 = &insert4;
    void *pinsert5 = &insert5;
    void *pinsert6 = &insert6;
    void *pinsert7 = &insert7;
    void *pinsert8 = &insert8;
    Heap_ty *heap = HeapCreate(CompareFunc);
    REQUIRE(NULL != heap);
    REQUIRE(TRUE == HeapIsEmpty(heap));
    REQUIRE(SUCCESS == HeapPush(heap ,pinsert1));
    REQUIRE(pinsert1 == HeapPeek(heap));
    REQUIRE(SUCCESS == HeapPush(heap ,pinsert2));
    REQUIRE(pinsert2 == HeapPeek(heap));
    REQUIRE(SUCCESS == HeapPush(heap ,pinsert3));
    REQUIRE(pinsert2 == HeapPeek(heap));
    REQUIRE(SUCCESS == HeapPush(heap ,pinsert4));
    REQUIRE(pinsert2 == HeapPeek(heap));
    REQUIRE(SUCCESS == HeapPush(heap ,pinsert5));
    REQUIRE(pinsert2 == HeapPeek(heap));
    REQUIRE(SUCCESS == HeapPush(heap ,pinsert6));
    REQUIRE(pinsert6 == HeapPeek(heap));
    REQUIRE(SUCCESS == HeapPush(heap ,pinsert7));
    REQUIRE(pinsert7 == HeapPeek(heap));
    REQUIRE(SUCCESS == HeapPush(heap ,pinsert8));
    REQUIRE(pinsert7 == HeapPeek(heap));
    REQUIRE(FALSE == HeapIsEmpty(heap));

    HeapDestroy(heap);
    return PASSED;
}
static test_status_t TestRemovepopsize(void)
{
    int insert1 = 10, insert2 = 6, insert3 = 11, insert4 = 8;
    int insert5 = -1, insert6 = 50, insert7 = 20, insert8 = 7;
    void *pinsert1 = &insert1;
    void *pinsert2 = &insert2;
    void *pinsert3 = &insert3;
    void *pinsert4 = &insert4;
    void *pinsert5 = &insert5;
    void *pinsert6 = &insert6;
    void *pinsert7 = &insert7;
    void *pinsert8 = &insert8;
    Heap_ty *heap = HeapCreate(CompareFunc);
    REQUIRE(NULL != heap);
    REQUIRE(0 == HeapSize(heap));
    REQUIRE(SUCCESS == HeapPush(heap ,pinsert1));
    REQUIRE(SUCCESS == HeapPush(heap ,pinsert2));
    REQUIRE(SUCCESS == HeapPush(heap ,pinsert3));
    REQUIRE(SUCCESS == HeapPush(heap ,pinsert4));
    REQUIRE(4 == HeapSize(heap));
    REQUIRE(SUCCESS == HeapPush(heap ,pinsert5));
    REQUIRE(SUCCESS == HeapPush(heap ,pinsert6));
    REQUIRE(SUCCESS == HeapPush(heap ,pinsert7));
    REQUIRE(SUCCESS == HeapPush(heap ,pinsert8));
    REQUIRE(8 == HeapSize(heap));
    REQUIRE(pinsert6 == HeapPeek(heap));
    HeapPop(heap);
    REQUIRE(pinsert7 == HeapPeek(heap));
    HeapPop(heap);
    REQUIRE(pinsert3 == HeapPeek(heap));
    REQUIRE(6 == HeapSize(heap));
    REQUIRE(pinsert4 == HeapRemove(heap, IsMatchFunc, pinsert4));
    REQUIRE(pinsert3 == HeapPeek(heap));
    REQUIRE(5 == HeapSize(heap));
    REQUIRE(pinsert3 == HeapRemove(heap, IsMatchFunc, pinsert3));
    REQUIRE(pinsert8 == HeapRemove(heap, IsMatchFunc, pinsert8));
    REQUIRE(pinsert1 == HeapPeek(heap));
    REQUIRE(3 == HeapSize(heap));

    HeapDestroy(heap);
    return PASSED;
}