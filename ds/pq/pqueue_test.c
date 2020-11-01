#include "../utils/test.h" /*REQUIRE RUNTEST*/
#include "../heap/heap.h"
#include "pqueue.h" 


#define TRUE (1)
#define FALSE (0)

int compare(const void *data,const void *date_to_compare);
int MatchInt(const void *data, const void *data_to_compare);
static test_status_t StageOneTest(void);
static test_status_t StageTwoTest(void);
static test_status_t StageThreeTest(void);

int main()
{
	RUNTEST(StageOneTest);
	
	RUNTEST(StageTwoTest);
	
	RUNTEST(StageThreeTest);

	
	return 0; 
}


static test_status_t StageOneTest(void)
{
	int num1 = 1;
	int num2 = 5;
	int num3 = 5;
	int num4 = 7;
	int num5 = 3;
	int num6 = 2;
	PQueue_t *pq = PQCreate(compare);
	REQUIRE(TRUE == PQIsEmpty(pq));
	PQEnpqueue(pq, (void *)&num1);
	REQUIRE(FALSE == PQIsEmpty(pq));
	REQUIRE(0 == PQEnpqueue(pq, (void *)&num2));
	REQUIRE(0 == PQEnpqueue(pq, (void *)&num3));
	REQUIRE(0 == PQEnpqueue(pq, (void *)&num4));
	REQUIRE(0 == PQEnpqueue(pq, (void *)&num5));
	REQUIRE(0 == PQEnpqueue(pq, (void *)&num6));

	REQUIRE(1 == *(int *)PQDepqueue(pq));
	REQUIRE(2 == *(int *)PQDepqueue(pq));
	REQUIRE(3 == *(int *)PQDepqueue(pq));
	REQUIRE(5 == *(int *)PQDepqueue(pq));
	REQUIRE(5 == *(int *)PQDepqueue(pq));
	REQUIRE(7 == *(int *)PQDepqueue(pq));

	REQUIRE(TRUE == PQIsEmpty(pq));
	PQDestroy(pq);
	return PASSED;

}
static test_status_t StageTwoTest(void)
{
	int num1 = 1;
	int num2 = 5;
	int num3 = 5;
	int num4 = 7;
	int num5 = 3;
	int num6 = 2;
	PQueue_t *pq = PQCreate(compare);
	REQUIRE(TRUE == PQIsEmpty(pq));
	PQEnpqueue(pq, (void *)&num1);
	REQUIRE(1 == PQSize(pq));
	REQUIRE(FALSE == PQIsEmpty(pq));
	REQUIRE(0 == PQEnpqueue(pq, (void *)&num2));
	REQUIRE(2 == PQSize(pq));
	REQUIRE(0 == PQEnpqueue(pq, (void *)&num3));
	REQUIRE(3 == PQSize(pq));
	REQUIRE(0 == PQEnpqueue(pq, (void *)&num4));
	REQUIRE(4 == PQSize(pq));
	REQUIRE(0 == PQEnpqueue(pq, (void *)&num5));
	REQUIRE(5 == PQSize(pq));
	REQUIRE(0 == PQEnpqueue(pq, (void *)&num6));

	REQUIRE(6 == PQSize(pq));
	REQUIRE(1 == *(int *)PQPeek(pq));
	REQUIRE(1 == *(int *)PQDepqueue(pq));
	REQUIRE(2 == *(int *)PQPeek(pq));
	REQUIRE(2 == *(int *)PQDepqueue(pq));
	REQUIRE(3 == *(int *)PQPeek(pq));
	REQUIRE(3 == *(int *)PQDepqueue(pq));
	REQUIRE(5 == *(int *)PQPeek(pq));
	REQUIRE(5 == *(int *)PQDepqueue(pq));
	REQUIRE(5 == *(int *)PQPeek(pq));
	REQUIRE(5 == *(int *)PQDepqueue(pq));
	REQUIRE(7 == *(int *)PQPeek(pq));
	REQUIRE(7 == *(int *)PQDepqueue(pq));
	REQUIRE(0 == PQSize(pq));
	REQUIRE(TRUE == PQIsEmpty(pq));
	PQDestroy(pq);
	return PASSED;

}
int MatchInt(const void *data, const void *data_to_compare)
{

	return *(int *)data == *(int *)data_to_compare;
}
static test_status_t StageThreeTest(void)
{
	int num1 = 1;
	int num2 = 5;
	int num3 = 5;
	int num4 = 7;
	int num5 = 3;
	int num6 = 2;
	int num_not_to_find = 9;
	PQueue_t *pq = PQCreate(compare);
	REQUIRE(TRUE == PQIsEmpty(pq));
	PQEnpqueue(pq, (void *)&num1);
	REQUIRE(1 == PQSize(pq));
	REQUIRE(FALSE == PQIsEmpty(pq));
	REQUIRE(0 == PQEnpqueue(pq, (void *)&num2));
	REQUIRE(2 == PQSize(pq));
	REQUIRE(0 == PQEnpqueue(pq, (void *)&num3));
	REQUIRE(3 == PQSize(pq));
	REQUIRE(0 == PQEnpqueue(pq, (void *)&num4));
	REQUIRE(4 == PQSize(pq));
	REQUIRE(0 == PQEnpqueue(pq, (void *)&num5));
	REQUIRE(5 == PQSize(pq));
	REQUIRE(0 == PQEnpqueue(pq, (void *)&num6));
	REQUIRE(num4 == *(int *)PQErase(pq, MatchInt,(void *)&num4));
	REQUIRE(5 == PQSize(pq));
	REQUIRE(NULL == PQErase(pq, MatchInt, (void *)&num_not_to_find));
	PQClear(pq);

	REQUIRE(TRUE == PQIsEmpty(pq));
	PQDestroy(pq);
	return PASSED;
}

int compare(const void *data,const void *date_to_compare)
{
	return ( *(int *)date_to_compare - *(int *)data);
}
