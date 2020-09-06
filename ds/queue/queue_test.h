#include "../utils/test.h" /* Require, RUNTEST */
#include "queue.h"

static test_status_t TestQueueCreate();


int main()
{
	RUNTEST(TestQueueCreate);	
	return 0;
}

static test_status_t TestQueueCreate()
{
	Queue_t *queue = QueueCreate();
	REQUIRE(NULL != queue);
	SlistDestroy(queue);
	return PASSED;
}