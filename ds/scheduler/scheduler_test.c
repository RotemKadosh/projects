#include "../utils/test.h" /*REQUIRE RUNTEST*/
#include "../task/task.h"
#include "../uid/uid.h"	/* uid_t */
#include "scheduler.h"

#define TRUE (1)
#define FALSE (0)
#define RUN_ONCE (1)
#define RUN_AGAIN (0)

static test_status_t StageOneTest(void);
static test_status_t StageTwoTest(void);
static test_status_t StageThreeTest(void);
static test_status_t StageTthreeTest(void);

int SchedulerPauseWrapper(void *data);
int multiplyUntil100(void *data);
int AddOneUntil20(void *data);

int main()
{
	RUNTEST(StageOneTest);
	RUNTEST(StageTwoTest);
	RUNTEST(StageThreeTest);
	RUNTEST(StageTthreeTest);
	return 0; 
}

int actionfunc(void *param)
{
	static size_t counter = 0;
	if(counter == 10)
	{
		return RUN_ONCE;
	}
	(void)param;
	counter++;
	return RUN_AGAIN;
}


int action(void *param)
{
	(void)param;
	return RUN_ONCE;
}

int action2(void *param)
{
	if(10 > *(int *)param)
	{
		*(int *)param += 2;
		return RUN_AGAIN;
	}
	return RUN_ONCE;
}

int action3(void *param)
{
	(void)param;
	return RUN_AGAIN;
}
int PauseWraper(void *scheduler)
{
	SchedulerPause((Scheduler_t *)scheduler);
	return RUN_ONCE;
}
int AddingTask(void *scheduler)
{
	SchedulerAdd((Scheduler_t *)scheduler, actionfunc, (void *)5, (size_t)5);
	return RUN_ONCE;
}
static test_status_t StageOneTest(void)
{
	Scheduler_t *scheduler = SchedulerCreate();
	REQUIRE(TRUE == SchedulerIsEmpty(scheduler));
	REQUIRE(FALSE == UIDIsSame(UIDGetBadUid(),SchedulerAdd(scheduler, actionfunc, (void *)5, (size_t)5)));
	REQUIRE(FALSE == UIDIsSame(UIDGetBadUid(),SchedulerAdd(scheduler, actionfunc, (void *)5, (size_t)5)));
	REQUIRE(FALSE == UIDIsSame(UIDGetBadUid(),SchedulerAdd(scheduler, actionfunc, (void *)5, (size_t)5)));
	REQUIRE(FALSE == UIDIsSame(UIDGetBadUid(),SchedulerAdd(scheduler, actionfunc, (void *)5, (size_t)5)));
	REQUIRE(FALSE == UIDIsSame(UIDGetBadUid(),SchedulerAdd(scheduler, actionfunc, (void *)5, (size_t)5)));
	REQUIRE(5 == SchedulerSize(scheduler));
	SchedulerDestroy(scheduler);	
	return PASSED;
}
static test_status_t StageTwoTest(void)
{
	int a = 5;
	int b = 6;
	int c = 7;
	int d = 8;
	int e = 9;
	Scheduler_t *scheduler = SchedulerCreate();
	REQUIRE(TRUE == SchedulerIsEmpty(scheduler));
	REQUIRE(FALSE == UIDIsSame(UIDGetBadUid(),SchedulerAdd(scheduler, action, (void *)&a, (size_t)1)));
	REQUIRE(FALSE == UIDIsSame(UIDGetBadUid(),SchedulerAdd(scheduler, action, (void *)&b, (size_t)1)));
	REQUIRE(FALSE == UIDIsSame(UIDGetBadUid(),SchedulerAdd(scheduler, action, (void *)&c, (size_t)1)));
	REQUIRE(FALSE == UIDIsSame(UIDGetBadUid(),SchedulerAdd(scheduler, action, (void *)&d, (size_t)1)));
	REQUIRE(FALSE == UIDIsSame(UIDGetBadUid(),SchedulerAdd(scheduler, action, (void *)&e, (size_t)1)));
	REQUIRE(5 == SchedulerSize(scheduler));
	REQUIRE(FINISH_ALL_WORK == SchedulerRun(scheduler));
	SchedulerDestroy(scheduler);

	scheduler = SchedulerCreate();
	REQUIRE(TRUE == SchedulerIsEmpty(scheduler));
	REQUIRE(FALSE == UIDIsSame(UIDGetBadUid(),SchedulerAdd(scheduler, action2, (void *)&a, (size_t)1)));
	REQUIRE(FALSE == UIDIsSame(UIDGetBadUid(),SchedulerAdd(scheduler, action2, (void *)&b, (size_t)0)));
	REQUIRE(FALSE == UIDIsSame(UIDGetBadUid(),SchedulerAdd(scheduler, action2, (void *)&c, (size_t)1)));
	REQUIRE(FALSE == UIDIsSame(UIDGetBadUid(),SchedulerAdd(scheduler, action2, (void *)&d, (size_t)1)));
	REQUIRE(FALSE == UIDIsSame(UIDGetBadUid(),SchedulerAdd(scheduler, action2, (void *)&e, (size_t)1)));
	REQUIRE(5 == SchedulerSize(scheduler));
	REQUIRE(FINISH_ALL_WORK == SchedulerRun(scheduler));
	REQUIRE(11 == a );
	REQUIRE(10 == b );
	REQUIRE(11 == c );
	REQUIRE(10 == d );
	REQUIRE(11 == e );
	SchedulerDestroy(scheduler);		
	return PASSED;
}

static test_status_t StageThreeTest(void)
{
	int a = 5;
	int b = 6;
	int c = 7;
	int d = 8;
	int e = 9;
	UID_t uid1 = {0};
	UID_t uid2 = {0};
	UID_t uid3 = {0};
	UID_t uid4 = {0};
	UID_t uid5 = {0};
	UID_t uid6 = {0};
	Scheduler_t *scheduler = SchedulerCreate();
	REQUIRE(TRUE == SchedulerIsEmpty(scheduler));
	uid1 = SchedulerAdd(scheduler, action, (void *)&a, (size_t)1);
	uid2 = SchedulerAdd(scheduler, action, (void *)&b, (size_t)3);
	uid3 = SchedulerAdd(scheduler, action, (void *)&c, (size_t)2);
	uid4 = SchedulerAdd(scheduler, action, (void *)&d, (size_t)3);
	uid5 = SchedulerAdd(scheduler, action, (void *)&e, (size_t)2);
	REQUIRE(5 == SchedulerSize(scheduler));
	REQUIRE(0 == SchedulerRemove(scheduler, uid4));
	REQUIRE(4 == SchedulerSize(scheduler));
	REQUIRE(0 == SchedulerRemove(scheduler, uid3));
	REQUIRE(3 == SchedulerSize(scheduler));
	REQUIRE(0 == SchedulerRemove(scheduler, uid2));
	REQUIRE(2 == SchedulerSize(scheduler));
	REQUIRE(0 == SchedulerRemove(scheduler, uid5));
	REQUIRE(1 == SchedulerSize(scheduler));
	REQUIRE(0 == SchedulerRemove(scheduler, uid1));
	REQUIRE(0 == SchedulerSize(scheduler));
	REQUIRE(TRUE == SchedulerIsEmpty(scheduler));
	uid1 = SchedulerAdd(scheduler, action3, (void *)&a, (size_t)6);
	uid2 = SchedulerAdd(scheduler, action3, (void *)&b, (size_t)6);
	uid3 = SchedulerAdd(scheduler, PauseWraper,(void *)scheduler, (size_t)10);
	uid4 = SchedulerAdd(scheduler, action3, (void *)&d, (size_t)6);
	uid5 = SchedulerAdd(scheduler, action3, (void *)&e, (size_t)6);
	uid6 = SchedulerAdd(scheduler, AddingTask, scheduler, (size_t)6);
	REQUIRE(STOPPED == SchedulerRun(scheduler));
	SchedulerClear(scheduler);
	REQUIRE(TRUE == SchedulerIsEmpty(scheduler));
	SchedulerDestroy(scheduler);


	return PASSED;
}

static test_status_t StageTthreeTest(void)
{
	int param = 18, param2 = 25;
	size_t interval = 5, interval2 = 10, interval_to_pause = 15;
	UID_t uid1, uid2;

	Scheduler_t *Scheduler = SchedulerCreate();
	REQUIRE(NULL != Scheduler);
	REQUIRE(0 == SchedulerSize(Scheduler));
	uid1 = SchedulerAdd(Scheduler, AddOneUntil20,(void *)&param, interval);
	REQUIRE(0 == UIDIsSame(uid1, UIDGetBadUid()));
	uid2 = SchedulerAdd(Scheduler, multiplyUntil100,(void *)&param2, interval2);
	REQUIRE(0 == UIDIsSame(uid2, UIDGetBadUid()));
	REQUIRE(2 == SchedulerSize(Scheduler));
	REQUIRE(0 == SchedulerRemove(Scheduler ,uid2));
	REQUIRE(1 == SchedulerSize(Scheduler));
	REQUIRE(1 == SchedulerRemove(Scheduler ,UIDGetBadUid()));
	REQUIRE(1 == SchedulerSize(Scheduler));
	uid2 = SchedulerAdd(Scheduler, multiplyUntil100,(void *)&param2, interval2);
	SchedulerClear(Scheduler);
	REQUIRE(0 == SchedulerSize(Scheduler));
	REQUIRE(FINISH_ALL_WORK == SchedulerRun(Scheduler));
	uid1 = SchedulerAdd(Scheduler, AddOneUntil20,(void *)&param, interval);
	uid2 = SchedulerAdd(Scheduler, multiplyUntil100,(void *)&param2, interval2);
	SchedulerAdd(Scheduler, SchedulerPauseWrapper,(void *)Scheduler, interval_to_pause);
	REQUIRE(STOPPED == SchedulerRun(Scheduler));
	REQUIRE(1 == SchedulerSize(Scheduler));
	REQUIRE(FINISH_ALL_WORK == SchedulerRun(Scheduler));

	SchedulerDestroy(Scheduler);

	return PASSED;
}


int AddOneUntil20(void *data)
{
	++*(int *)data;
	if (*(int *)data < 20)
	{
		return 0;	
	}
	return 1;
}

int multiplyUntil100(void *data)
{
	*(int *)data *= 2;
	if (*(int *)data < 100)
	{
		return 0;	
	}
	return 1;
}

int SchedulerPauseWrapper(void *data)
{
	Scheduler_t *Scheduler = (Scheduler_t *)data;
	SchedulerPause(Scheduler);
	return 1;
}
