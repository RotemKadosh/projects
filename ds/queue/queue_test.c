#include "../utils/test.h" /* Require, RUNTEST */
#include "queue.h"

static test_status_t TestQCreate();
static test_status_t TestQEnqueue();
static test_status_t TestQPeek();
static test_status_t TestQSize();
static test_status_t TestQDequeue();
static test_status_t TestQIsEmpty();
static test_status_t TestQAppend();

int main()
{
	RUNTEST(TestQCreate);
	RUNTEST(TestQEnqueue);	
	RUNTEST(TestQPeek);
	RUNTEST(TestQSize);
	RUNTEST(TestQDequeue);
	RUNTEST(TestQIsEmpty);
	RUNTEST(TestQAppend);
	return 0;
}

static test_status_t TestQCreate()
{
	Queue_t *queue = QCreate();
	REQUIRE(NULL != queue);
	QDestroy(queue);
	return PASSED;
}

static test_status_t TestQEnqueue()
{
	Queue_t *queue = QCreate();
	REQUIRE(0 == QEnqueue(queue, (void *)10));
	REQUIRE(0 == QEnqueue(queue, (void *)10));
	REQUIRE(0 == QEnqueue(queue, (void *)10));
	REQUIRE(0 == QEnqueue(queue, (void *)10));
	REQUIRE(0 == QEnqueue(queue, (void *)10));
	QDestroy(queue);
	return PASSED;
}
static test_status_t TestQPeek()
{
	Queue_t *queue = QCreate();
	REQUIRE(0 == QEnqueue(queue, (void *)-10));
	REQUIRE(0 == QEnqueue(queue, (void *)11));
	REQUIRE(-10 == (int)(long)QPeek(queue));
	QDestroy(queue);
	return PASSED;
}
static test_status_t TestQSize()
{
	Queue_t *queue = QCreate();
	REQUIRE(0 == QSize(queue));
	QEnqueue(queue, (void *)10);
	REQUIRE(1 == QSize(queue));
	QEnqueue(queue, (void *)10);
	REQUIRE(2 == QSize(queue));
	QEnqueue(queue, (void *)10);
	REQUIRE(3 == QSize(queue));
	QEnqueue(queue, (void *)10);
	REQUIRE(4 == QSize(queue));
	QDestroy(queue);
	return PASSED;
}
static test_status_t TestQDequeue()
{
	Queue_t *queue = QCreate();
	REQUIRE(0 == QSize(queue));
	QEnqueue(queue, (void *)10);
	REQUIRE(1 == QSize(queue));
	QEnqueue(queue, (void *)10);
	REQUIRE(2 == QSize(queue));
	QEnqueue(queue, (void *)10);
	REQUIRE(3 == QSize(queue));
	QEnqueue(queue, (void *)10);
	REQUIRE(4 == QSize(queue));

	QDequeue(queue);
	REQUIRE(3 == QSize(queue));
	QDequeue(queue);
	REQUIRE(2 == QSize(queue));
	QDequeue(queue);
	REQUIRE(1 == QSize(queue));
	QDequeue(queue);
	REQUIRE(0 == QSize(queue));

	QDestroy(queue);
	return PASSED;
}
static test_status_t TestQIsEmpty()
{
	Queue_t *queue = QCreate();
	REQUIRE(1 == QIsEmpty(queue));
	QEnqueue(queue, (void *)10);
	REQUIRE(0 == QIsEmpty(queue));
	QDequeue(queue);
	REQUIRE(1 == QIsEmpty(queue));
	QDestroy(queue);
	return PASSED;
}
static test_status_t TestQAppend()
{

	size_t combine = 0;
	
	Queue_t *first = QCreate();
	Queue_t *last = QCreate();

	QEnqueue(first, (void *)1);
	QEnqueue(first, (void *)2);
	QEnqueue(first, (void *)3);
	QEnqueue(first, (void *)4);
	QEnqueue(first, (void *)5);

	QEnqueue(last, (void *)1);
	QEnqueue(last, (void *)2);
	QEnqueue(last, (void *)3);
	QEnqueue(last, (void *)4);
	QEnqueue(last, (void *)5);

	combine = QSize(first) + QSize(last);

	QAppend(first, last);

	REQUIRE(QSize(first) == combine);
	QDequeue(first);
	REQUIRE(!(QSize(first) == combine));
	QDestroy(first);


	return PASSED;
}