#include "../utils/test.h" /*REQUIRE RUNTEST*/
#include "sorted_list.h"
#include "dlist.h"

#define TRUE (1)
#define FALSE (0)


int UpDataByPram(void *data, void *param);
int compare(const void *data,const void *date_to_compare);
int match4(const void *data,const void *date_to_compare);

static test_status_t StageOneTest(void);
static test_status_t StageTwoTest(void);
static test_status_t StageThreeTest(void);
static test_status_t StageFourTest(void);
static test_status_t StageFiveTest(void);
static test_status_t StageSixTest(void);

int main()
{
	RUNTEST(StageOneTest);
	
	RUNTEST(StageTwoTest);
	
	RUNTEST(StageThreeTest);
	
	RUNTEST(StageFourTest);
	
	RUNTEST(StageFiveTest);
	
	RUNTEST(StageSixTest);
	/*
	RUNTEST(StageSevenTest);
	RUNTEST(StageEightTest);
*/
	return PASSED; 
}

int UpDataByPram(void *data, void *param)
{
	*(int *)data += *(int *)param;
	return 0;
}
int compare(const void *data,const void *date_to_compare)
{
	return ( *(int *)data - *(int *)date_to_compare);
}


static test_status_t StageOneTest(void)
{
	int a = 1;
	int b = 2;

	sorted_list_t *list = SortedListCreate(compare);
	REQUIRE(TRUE == SortedListIsSameIter(SortedListBegin(list), SortedListEnd(list)));
	SortedListInsert(list, (void *)&a);
	SortedListInsert(list, (void *)&b);
	REQUIRE(*(int *)SortedListGetData( SortedListBegin(list)) == a);
	SortedListDestroy(list);

	return PASSED;
}
static test_status_t StageTwoTest(void)
{
	int a = 1;
	int b = 2;
	sorted_list_iter_t iter;
	sorted_list_t *list = SortedListCreate(compare);
	REQUIRE(TRUE == SortedListIsSameIter(SortedListBegin(list), SortedListEnd(list)));
	REQUIRE(TRUE == SortedListIsEmpty(list));
	SortedListInsert(list, (void *)&a);
	REQUIRE(FALSE == SortedListIsEmpty(list));
	iter = SortedListInsert(list, (void *)&b);
	REQUIRE(*(int *)SortedListGetData( SortedListBegin(list)) == a);
	REQUIRE(TRUE == SortedListIsSameIter(SortedListNext( SortedListBegin(list)), iter));
	REQUIRE(TRUE == SortedListIsSameIter(SortedListPrev(iter), SortedListBegin(list)));
	REQUIRE(TRUE == SortedListIsSameIter(SortedListPrev( SortedListEnd(list)), iter));
	SortedListDestroy(list);

	return PASSED;
}
static test_status_t StageThreeTest(void)
{
	int a = 1;
	int b = 2;
	sorted_list_iter_t iter;
	sorted_list_t *list = SortedListCreate(compare);
	REQUIRE(TRUE == SortedListIsSameIter(SortedListBegin(list), SortedListEnd(list)));
	REQUIRE(TRUE == SortedListIsEmpty(list));
	SortedListInsert(list, (void *)&a);
	REQUIRE(FALSE == SortedListIsEmpty(list));
	iter = SortedListInsert(list, (void *)&b);
	REQUIRE(*(int *)SortedListGetData( SortedListBegin(list)) == a);
	REQUIRE(TRUE == SortedListIsSameIter(SortedListNext( SortedListBegin(list)), iter));
	REQUIRE(TRUE == SortedListIsSameIter(SortedListPrev(iter), SortedListBegin(list)));
	REQUIRE(TRUE == SortedListIsSameIter(SortedListPrev( SortedListEnd(list)), iter));
	SortedListPopFront(list);
	REQUIRE(TRUE == SortedListIsSameIter(SortedListBegin(list), iter));
	iter = SortedListInsert(list, (void *)&a);
	REQUIRE(TRUE == SortedListIsSameIter( SortedListBegin(list), iter));
	SortedListPopBack(list);
	REQUIRE(TRUE == SortedListIsSameIter(SortedListPrev( SortedListEnd(list)), iter));
	SortedListDestroy(list);

	return PASSED;
}
static test_status_t StageFourTest(void)
{
	int a = 1;
	int b = 2;
	int c = 3;
	int d = 4;
	int e = 5;
	sorted_list_iter_t iter;
	sorted_list_t *list = SortedListCreate(compare);
	REQUIRE(TRUE == SortedListIsSameIter(SortedListBegin(list), SortedListEnd(list)));
	REQUIRE(TRUE == SortedListIsEmpty(list));
	SortedListInsert(list, (void *)&a);
	REQUIRE(FALSE == SortedListIsEmpty(list));
	iter = SortedListInsert(list, (void *)&b);
	REQUIRE(*(int *)SortedListGetData( SortedListBegin(list)) == a);
	REQUIRE(TRUE == SortedListIsSameIter(SortedListNext( SortedListBegin(list)), iter));
	REQUIRE(TRUE == SortedListIsSameIter(SortedListPrev(iter), SortedListBegin(list)));
	REQUIRE(TRUE == SortedListIsSameIter(SortedListPrev( SortedListEnd(list)), iter));
	SortedListPopFront(list);
	REQUIRE(TRUE == SortedListIsSameIter(SortedListBegin(list), iter));
	iter = SortedListInsert(list, (void *)&a);
	REQUIRE(TRUE == SortedListIsSameIter( SortedListBegin(list), iter));
	SortedListPopBack(list);
	REQUIRE(TRUE == SortedListIsSameIter(SortedListPrev( SortedListEnd(list)), iter));
	iter = SortedListInsert(list, (void *)&b);
	SortedListInsert(list, (void *)&c);
	SortedListInsert(list, (void *)&d);
	SortedListInsert(list, (void *)&e);
	iter = SortedListRemove(list, iter);
	REQUIRE(*(int *)SortedListGetData(iter) == c);
	REQUIRE(TRUE == SortedListIsSameIter(SortedListNext(SortedListBegin(list)), iter));
	iter = SortedListRemove(list, iter);
	iter = SortedListRemove(list, iter);
	iter = SortedListRemove(list, iter);
	REQUIRE(TRUE == SortedListIsSameIter(SortedListEnd(list), iter));
	SortedListRemove(list, SortedListPrev(iter));
	SortedListDestroy(list);

	return PASSED;
}
static test_status_t StageFiveTest(void)
{
	int a = 1;
	int b = 2;
	int c = 3;
	int d = 4;
	int e = 5;
	int to_add = 1;
	sorted_list_iter_t iter;
	sorted_list_t *list = SortedListCreate(compare);
	REQUIRE(TRUE == SortedListIsSameIter(SortedListBegin(list), SortedListEnd(list)));
	REQUIRE(TRUE == SortedListIsEmpty(list));
	REQUIRE(0 == SortedListSize(list));
	SortedListInsert(list, (void *)&a);
	REQUIRE(1 == SortedListSize(list));
	REQUIRE(FALSE == SortedListIsEmpty(list));
	iter = SortedListInsert(list, (void *)&b);
	REQUIRE(2 == SortedListSize(list));
	REQUIRE(*(int *)SortedListGetData( SortedListBegin(list)) == a);
	REQUIRE(TRUE == SortedListIsSameIter(SortedListNext( SortedListBegin(list)), iter));
	REQUIRE(TRUE == SortedListIsSameIter(SortedListPrev(iter), SortedListBegin(list)));
	REQUIRE(TRUE == SortedListIsSameIter(SortedListPrev( SortedListEnd(list)), iter));
	SortedListPopFront(list);
	REQUIRE(1 == SortedListSize(list));
	REQUIRE(TRUE == SortedListIsSameIter(SortedListBegin(list), iter));
	iter = SortedListInsert(list, (void *)&a);
	REQUIRE(2 == SortedListSize(list));
	REQUIRE(TRUE == SortedListIsSameIter( SortedListBegin(list), iter));
	SortedListPopBack(list);
	REQUIRE(1 == SortedListSize(list));
	REQUIRE(TRUE == SortedListIsSameIter(SortedListPrev( SortedListEnd(list)), iter));
	iter = SortedListInsert(list, (void *)&b);
	REQUIRE(2 == SortedListSize(list));
	SortedListInsert(list, (void *)&c);
	REQUIRE(3 == SortedListSize(list));
	SortedListInsert(list, (void *)&d);
	REQUIRE(4 == SortedListSize(list));
	SortedListInsert(list, (void *)&e);
	REQUIRE(5 == SortedListSize(list));
	SortedListDestroy(list);

	list = SortedListCreate(compare);
	SortedListInsert(list, (void *)&a);
	SortedListInsert(list, (void *)&b);
	SortedListInsert(list, (void *)&c);
	SortedListInsert(list, (void *)&d);
	SortedListInsert(list, (void *)&e);
	SortedListForEach(SortedListBegin(list), SortedListEnd(list), UpDataByPram,(void *)&to_add);
	REQUIRE(2 == *(int *)SortedListGetData(SortedListBegin(list)));
	SortedListPopFront(list);
	REQUIRE(3 == *(int *)SortedListGetData(SortedListBegin(list)));
	SortedListPopFront(list);
	REQUIRE(4 == *(int *)SortedListGetData(SortedListBegin(list)));
	SortedListPopFront(list);
	REQUIRE(5 == *(int *)SortedListGetData(SortedListBegin(list)));
	SortedListPopFront(list);
	REQUIRE(6 == *(int *)SortedListGetData(SortedListBegin(list)));
	SortedListDestroy(list);

	return PASSED;
}
static test_status_t StageSixTest(void)
{
	int a = 1;
	int b = 2;
	int c = 3;
	int d = 4;
	int e = 5;
	int to_add = 1;
	sorted_list_iter_t iter;
	sorted_list_t *list = SortedListCreate(compare);
	SortedListInsert(list, (void *)&a);
	SortedListInsert(list, (void *)&b);
	iter = SortedListInsert(list, (void *)&c);
	SortedListInsert(list, (void *)&d);
	SortedListInsert(list, (void *)&e);
	SortedListForEach(SortedListBegin(list), SortedListEnd(list), UpDataByPram,(void *)&to_add);
	REQUIRE(SortedListIsSameIter(iter, SortedListFindIf(list, SortedListBegin(list), SortedListEnd(list), match4, (void *)&to_add )));
	SortedListDestroy(list);	

	return PASSED;
}
int match4(const void *data,const void *date_to_compare)
{
	(void)date_to_compare;
	if(*(int *)data == 4)
	{
		return 1;
	}
	return 0;
}
