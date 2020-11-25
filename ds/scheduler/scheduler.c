#include <stdlib.h>   			/*malloc, free*/
#include <time.h>				/*time_t*/
#include <assert.h>				/*assert*/
#include <unistd.h> 			/*sleep*/

#include "pqueue.h" 			/*pqueue_t*/
#include "uid.h" 				/*UID_t*/
#include "task.h" 				/*task_t*/

#include "scheduler.h"


#define SUCCESS (0)
#define FAIL (1)

#define STOP (1)
#define RUN (0)

typedef struct sched_task
{
	task_t *task;
	time_t time_to_execute;
}sched_task_t;


struct scheduler
{
	PQueue_t *container;
	int stop_flag;
};

/*-----------service funcs----------*/
static int SchedulerGetStopFlag(Scheduler_t * schd)
{
	return schd->stop_flag;
}
static void SchedulerSetInnerTask(sched_task_t *sc, task_t *task)
{
	sc->task = task;
}
static task_t * SchedulerGetInnerTask(const sched_task_t *sc)
{
	return sc->task ;
}

static void SchedulerSetContainer(Scheduler_t * schd, PQueue_t *pqueue)
{
	schd->container = pqueue;
}
static PQueue_t *SchedulerGetContainer(const Scheduler_t * schd)
{
	return schd->container;
}
static void SchedulerSetTimeToExec(sched_task_t* schd, time_t time_to_execute)
{
	schd->time_to_execute = time_to_execute;
}
static time_t SchedulerGetTimeToExec(const sched_task_t* schd)
{
	return schd->time_to_execute; 
}

static sched_task_t *SchedulerCreateSchdTask(task_action_func_t action_func ,void *param, size_t interval)
{
	sched_task_t *schd_task = (sched_task_t *)malloc(sizeof(sched_task_t));
	if(NULL == schd_task)
	{
		schd_task = NULL;
		return NULL;
	}
	SchedulerSetInnerTask(schd_task, TaskCreate(action_func, param, interval));
	if(NULL == SchedulerGetInnerTask(schd_task))
	{
		return NULL;
	}
	SchedulerSetTimeToExec(schd_task, time(NULL) + interval);
	return schd_task;
}
static void SchedulerDestroySchdTask(sched_task_t *task)
{
	TaskDestroy(SchedulerGetInnerTask(task));
	free(task);
	task = NULL;
}
static void SchedulerSetStopFlag(Scheduler_t *scheduler, int flag)
{
	scheduler->stop_flag = flag;
}

int CompareByTime(const void *data, const void *data_to_compare)
{
	time_t data_time = SchedulerGetTimeToExec((sched_task_t *)data);
	time_t data_to_compare_time = SchedulerGetTimeToExec((sched_task_t *)data_to_compare);
	return ((int)data_to_compare_time - (int)data_time);
}
int matchWraper(const void *s_task,const void *uid)
{
	return UIDIsSame(TaskGetUid(SchedulerGetInnerTask((sched_task_t *)s_task)) ,*(UID_t *)uid);
}
static void SleepUntilExecTime(sched_task_t *cuurent_task)
{

	double sleep_time = ((double)SchedulerGetTimeToExec(cuurent_task) - (double)time(NULL)); 
	while(0 < sleep_time)
	{
		sleep_time = sleep((unsigned int)sleep_time);
	}
}
static int ReSchedualTask(Scheduler_t *scheduler, sched_task_t *s_task)
{
	SchedulerSetTimeToExec(s_task, time(NULL) + TaskGetInterval(SchedulerGetInnerTask(s_task)));
	return PQEnpqueue(SchedulerGetContainer(scheduler),(void *)s_task);
}

/*-------------------------------------------*/

Scheduler_t *SchedulerCreate(void)
{
	Scheduler_t *scheduler = (Scheduler_t *)malloc(sizeof(Scheduler_t));
	if(NULL == scheduler)
	{
		return NULL;
	}
	SchedulerSetContainer(scheduler, PQCreate(CompareByTime));
	if(NULL == SchedulerGetContainer(scheduler))
	{
		free (scheduler);
		scheduler = NULL;
		return NULL;
	}
	SchedulerSetStopFlag(scheduler, RUN);
	return scheduler;
}
void SchedulerDestroy(Scheduler_t *scheduler)
{
	assert(NULL != scheduler);
	SchedulerClear(scheduler);
	PQDestroy(SchedulerGetContainer(scheduler));
	SchedulerSetContainer(scheduler, NULL);
	free (scheduler);
	scheduler = NULL;
}
int SchedulerIsEmpty(const Scheduler_t *scheduler)
{
	assert(NULL != scheduler);
	return PQIsEmpty(SchedulerGetContainer(scheduler));
}
size_t SchedulerSize(const Scheduler_t *scheduler)
{
	assert(NULL != scheduler);
	return PQSize(SchedulerGetContainer(scheduler));
}
UID_t SchedulerAdd(Scheduler_t *scheduler, sched_action_func_t action_func, void *param, size_t interval_in_sec)
{
	sched_task_t *schd_task_ptr = NULL;

	assert (NULL != action_func);
	assert(NULL != scheduler);

	schd_task_ptr = SchedulerCreateSchdTask(action_func ,param, interval_in_sec);
	
	if(NULL == schd_task_ptr)
	{
		return UIDGetBadUid();
	}
	if(SUCCESS != PQEnpqueue(SchedulerGetContainer(scheduler),(void *)schd_task_ptr))
	{
		SchedulerDestroySchdTask(schd_task_ptr);
		schd_task_ptr = NULL;
		return UIDGetBadUid();
	}
	return TaskGetUid(SchedulerGetInnerTask(schd_task_ptr));
}
int SchedulerRun(Scheduler_t *scheduler)
{
	sched_task_t *current_task = NULL;
	assert(NULL != scheduler);
	SchedulerSetStopFlag(scheduler, RUN);
	while (!SchedulerIsEmpty(scheduler) && STOP != SchedulerGetStopFlag(scheduler))
	{
		current_task = (sched_task_t *)PQDepqueue(SchedulerGetContainer(scheduler));
		SleepUntilExecTime(current_task);
		if (0 == TaskActivateFunc(SchedulerGetInnerTask(current_task)))
		{
			if (FAIL == ReSchedualTask(scheduler, current_task))
		 	{
		 		return ERROR;
		 	}
		}
		else
		{
			SchedulerDestroySchdTask(current_task);
			current_task = NULL;
		}
	}
	if (SchedulerIsEmpty(scheduler))
	{
		return FINISH_ALL_WORK;
	}
	return STOPPED;
}

void SchedulerPause(Scheduler_t *scheduler)
{
	assert(NULL != scheduler);
	SchedulerSetStopFlag(scheduler, STOP);
}
void SchedulerClear(Scheduler_t *scheduler)
{
	sched_task_t *task_ptr = NULL;
	assert(NULL != scheduler);
	while(!SchedulerIsEmpty(scheduler))
	{
		task_ptr = (sched_task_t *)PQDepqueue(SchedulerGetContainer(scheduler));
		SchedulerDestroySchdTask(task_ptr);
		task_ptr = NULL;
	}
}
int SchedulerRemove(Scheduler_t *scheduler, UID_t uid)
{
	sched_task_t *s_task = NULL;
	assert(NULL != scheduler);
 	s_task = (sched_task_t *)PQErase(SchedulerGetContainer(scheduler), matchWraper, &uid);
 	if(NULL == s_task)
	{
	 	return FAIL;
	}
 	SchedulerDestroySchdTask(s_task);
 	s_task = NULL;
 	return SUCCESS;
}