#include "../utils/test.h" /*REQUIRE RUNTEST*/
#include "task.h"
#include "uid.h"	/* uid_t */

#define TRUE (1)
#define FALSE (0)


size_t TaskGetInterval(task_t *task);

static test_status_t StageThreeTest(void);
int actionfunc(void *param)
{
	static size_t counter = 0;
	if(counter == 10)
	{
		return TRUE;
	}
	(void)param;
	printf("%lu\n", counter++);
	return FALSE;
}

int main()
{
	RUNTEST(StageThreeTest);
	return 0; 
}

static test_status_t StageThreeTest(void)
{
	size_t num1 = 8;
	task_t *cre = TaskCreate(actionfunc, (void *)num1, (size_t)5);
	REQUIRE((size_t)5  == TaskGetInterval(cre));
	while (0 == TaskActivateFunc(cre)){}
	TaskDestroy(cre);
	return PASSED;
}

