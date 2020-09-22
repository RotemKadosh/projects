#include "task.h"
#include <stdlib.h>/*malloc, free*/
#include "uid.h"
#include <assert.h> /*assert*/


struct task
{
	UID_t uid;
	size_t time_interval;
	task_action_func_t action_func;
	void *param;
};
static void TaskSetUid(task_t *task, UID_t uid)
{
	assert(NULL != task);
	task->uid = uid;
}
UID_t TaskGetUid(task_t *task)
{
	assert(NULL != task);
	return task->uid;
}
static void TaskSetActionFunc(task_t *task, task_action_func_t action_func)
{
	assert(NULL != task);
	task->action_func = action_func;
}
static void TaskSetParam(task_t *task, void *param)
{
	assert(NULL != task);
	task->param = param;
}
static void *TaskGetParam(task_t *task)
{
	assert(NULL != task);
	return task->param;
}
static void TaskSetInterval(task_t *task, size_t interval)
{
	assert(NULL != task);
	task->time_interval = interval;
}
size_t TaskGetInterval(task_t *task)
{
	assert(NULL != task);
	return task->time_interval;
}

task_t *TaskCreate(task_action_func_t action_func ,void *param, size_t interval)
{

	task_t *task = (task_t *)malloc(sizeof(task_t));
	if(NULL == task)
	{
		return NULL;
	}
	TaskSetUid(task, UIDCreate());
	if(UIDIsSame(TaskGetUid(task), UIDGetBadUid()))
	{
		return NULL;
	}

	TaskSetActionFunc(task, action_func);
	TaskSetParam(task, param);
	TaskSetInterval(task, interval);
	return task;
}

void TaskDestroy(task_t *task)
{
	assert(NULL != task);
	free(task);
	task = NULL;
}

int TaskActivateFunc(task_t *task)
{
	assert(NULL != task);
	return task->action_func(TaskGetParam(task));
}
