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
static test_status_t StageSevenTest(void);

int main()
{
	RUNTEST(StageOneTest);
	
	RUNTEST(StageTwoTest);
	
	RUNTEST(StageThreeTest);
	
	RUNTEST(StageFourTest);
	
	RUNTEST(StageFiveTest);
	
	RUNTEST(StageSixTest);

	RUNTEST(StageSevenTest);
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
{/*create, isSameiter, getData, begin, end, insert*/
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
{/*create, isSameiter, getData, begin, end, insert*/
/*destroy prev next isempty*/
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
{/*create, isSameiter, getData, begin, end, insert*/
/*destroy prev next isempty*/
/*popfront popback*/
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
{/*create, isSameiter, getData, begin, end, insert*/
/*destroy prev next isempty*/
/*popfront popback*/
/*remove*/
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
/*create, isSameiter, getData, begin, end, insert*/
/*destroy prev next isempty*/
/*popfront popback*/
/*remove*/
/*SIZE FOREACH*/
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
{/*create, isSameiter, getData, begin, end, insert*/
/*destroy prev next isempty*/
/*popfront popback*/
/*remove*/
/*SIZE FOREACH*/
/*FIND*/


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
	a = 1;
	b = 2;
	c = 3;
	d = 4;
	e = 5;
	to_add = 1;
	list = SortedListCreate(compare);
	SortedListInsert(list, (void *)&a);
	SortedListInsert(list, (void *)&b);
	iter = SortedListInsert(list, (void *)&c);
	SortedListInsert(list, (void *)&d);
	SortedListInsert(list, (void *)&e);
	SortedListForEach(SortedListBegin(list), SortedListEnd(list), UpDataByPram,(void *)&to_add);
	REQUIRE(SortedListIsSameIter(iter, SortedListFind(list, SortedListBegin(list), SortedListEnd(list),(void *)&c)));
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
static test_status_t StageSevenTest(void)
{/*create, isSameiter, getData, begin, end, insert*/
/*destroy prev next isempty*/
/*popfront popback*/
/*remove*/
/*SIZE FOREACH*/
/*FIND*/
/*MERGE*/
	int a = 1;
	int a1 = 1;
	int b = 2;
	int c = 10;
	int d = 11;
	int e = 5;
	int f = 6;
	int g = 12;
	int h = 7;
	sorted_list_iter_t runner;
	sorted_list_t *dest = SortedListCreate(compare);
	sorted_list_t *src = SortedListCreate(compare);
	SortedListInsert(dest, (void *)&a);
	SortedListInsert(dest, (void *)&b);
	SortedListInsert(dest, (void *)&c);
	SortedListInsert(dest, (void *)&d);
	SortedListInsert(dest, (void *)&e);

	SortedListInsert(src, (void *)&a1);				/*dest: 1->2->5->10->11*/
	SortedListInsert(src, (void *)&f);				/*src: 1->6->7->12*/
	SortedListInsert(src, (void *)&g);				/*after merge*/
	SortedListInsert(src, (void *)&h);	
													/*dest: 1->2->5->6->7->10->11->12*/
	SortedListMerge(dest, src);						/*src: empty*/
	runner = SortedListBegin(dest);
	REQUIRE(1 == *(int *)SortedListGetData(runner));
	runner = SortedListNext(runner);		
	REQUIRE(1 == *(int *)SortedListGetData(runner));
	runner = SortedListNext(runner);
	REQUIRE(2 == *(int *)SortedListGetData(runner));
	runner = SortedListNext(runner);	
	REQUIRE(5 == *(int *)SortedListGetData(runner));
	runner = SortedListNext(runner);	
	REQUIRE(6 == *(int *)SortedListGetData(runner));
	runner = SortedListNext(runner);	
	REQUIRE(7 == *(int *)SortedListGetData(runner));
	runner = SortedListNext(runner);
	REQUIRE(10 == *(int *)SortedListGetData(runner));
	runner = SortedListNext(runner);
	REQUIRE(11 == *(int *)SortedListGetData(runner));
	runner = SortedListNext(runner);
	REQUIRE(12 == *(int *)SortedListGetData(runner));
	runner = SortedListNext(runner);
	REQUIRE(TRUE == SortedListIsSameIter(runner, SortedListEnd(dest)));
	REQUIRE(TRUE == SortedListIsEmpty(src));
	SortedListDestroy(src);
	SortedListDestroy(dest);
	
	dest = SortedListCreate(compare);
	src = SortedListCreate(compare);
	SortedListInsert(dest, (void *)&a);
	SortedListInsert(dest, (void *)&b);
	SortedListInsert(dest, (void *)&c);
	SortedListInsert(dest, (void *)&d);
	SortedListInsert(dest, (void *)&e);

	SortedListMerge(dest, src);	
	runner = SortedListBegin(dest);
	REQUIRE(1 == *(int *)SortedListGetData(runner));
	runner = SortedListNext(runner);		
	REQUIRE(2 == *(int *)SortedListGetData(runner));
	runner = SortedListNext(runner);
	REQUIRE(5 == *(int *)SortedListGetData(runner));
	runner = SortedListNext(runner);	
	REQUIRE(10 == *(int *)SortedListGetData(runner));
	runner = SortedListNext(runner);	
	REQUIRE(11 == *(int *)SortedListGetData(runner));
	runner = SortedListNext(runner);
	REQUIRE(TRUE == SortedListIsSameIter(runner, SortedListEnd(dest)));
	REQUIRE(TRUE == SortedListIsEmpty(src));

	SortedListDestroy(src);
	SortedListDestroy(dest);


	dest = SortedListCreate(compare);
	src = SortedListCreate(compare);
	SortedListInsert(src, (void *)&a);
	SortedListInsert(src, (void *)&b);
	SortedListInsert(src, (void *)&c);
	SortedListInsert(src, (void *)&d);
	SortedListInsert(src, (void *)&e);

	SortedListMerge(dest, src);	
	runner = SortedListBegin(dest);
	REQUIRE(1 == *(int *)SortedListGetData(runner));
	runner = SortedListNext(runner);		
	REQUIRE(2 == *(int *)SortedListGetData(runner));
	runner = SortedListNext(runner);
	REQUIRE(5 == *(int *)SortedListGetData(runner));
	runner = SortedListNext(runner);	
	REQUIRE(10 == *(int *)SortedListGetData(runner));
	runner = SortedListNext(runner);	
	REQUIRE(11 == *(int *)SortedListGetData(runner));
	runner = SortedListNext(runner);
	REQUIRE(TRUE == SortedListIsSameIter(runner, SortedListEnd(dest)));
	REQUIRE(TRUE == SortedListIsEmpty(src));

	SortedListDestroy(src);
	SortedListDestroy(dest);
	return PASSED;
}