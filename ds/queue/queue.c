#include <stdlib.h>/* malloc, free*/
#include <assert.h>/* assert*/
#include "../slist/slist.h"  /*slist functions*/
#include "queue.h"
#define FAIL (-1)
#define SUCCESS (0)
/*approved by may*/

struct queue
{
	Slist_t *list;
};

Queue_t *QCreate(void)
{
	Queue_t *q = (Queue_t *)malloc(sizeof(Queue_t));
	if(NULL == q)
	{
		return NULL;
	}
	q->list = SlistCreate();
	if(NULL == q->list)
	{
		free(q);
		q = NULL;
	}
	return q;
}
int QEnqueue(Queue_t *queue, void *data)
{	
	Slist_iter_t ans = NULL;
	assert(NULL != queue);
	ans =  SlistInsert(SlistEnd(queue->list),data);
	if(SlistEnd(queue->list) == ans)
	{
		return FAIL;
	}

	return SUCCESS;
}
void *QPeek(const Queue_t *queue)
{
	assert(NULL != queue);
	return SlistGetData(SlistBegin(queue->list));;
}
void QDestroy(Queue_t *queue)
{
	assert(NULL != queue);
	SlistDestroy(queue->list);
	queue->list = NULL;
	free(queue);
	queue = NULL;
}
size_t QSize(const Queue_t *queue)
{
	assert(NULL != queue);
	return SlistCount(queue->list);
}
int QIsEmpty(const Queue_t *queue)
{
	assert(NULL != queue);
	return SlistIsSameIter(SlistBegin(queue->list), SlistEnd(queue->list));
}
void QDequeue(Queue_t *queue)
{
	assert(NULL != queue);
	SlistRemove(SlistBegin(queue->list));
}
void QAppend(Queue_t *dest, Queue_t *src)
{
	assert(NULL != dest);
	assert(NULL != src);
	SlistAppend(dest->list, src->list);
}