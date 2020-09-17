#include <stdlib.h> /*malloc, free*/
#include <assert.h> /*assert*/
#include "pqueue.h" 
#include "sorted_list.h"

struct pqueue
{
	sorted_list_t *list;
};

#define FAIL (1)
#define SUCCESS (0)
#define TRUE (1)

static sorted_list_t *GetList(const PQueue_t * pq)
{
	return pq->list;
}

static void SetList(PQueue_t * pq, sorted_list_t *list)
{
	pq->list = list;
}

PQueue_t *PQCreate(pq_compare_func_t compare_func)
{
	PQueue_t *pq = (PQueue_t *)malloc(sizeof(PQueue_t));
	if( NULL == pq)
	{
		return NULL;
	}
	SetList(pq, SortedListCreate(compare_func));
	if(NULL == GetList(pq))
	{
		free(pq);
		pq = NULL;
		return NULL;
	}
	return pq;
}

int PQIsEmpty(const PQueue_t *pqueue)
{
	assert(NULL != pqueue);
	return SortedListIsEmpty(GetList(pqueue));
}

int PQEnpqueue(PQueue_t *pqueue, void *data)
{
	assert(NULL != pqueue);
	return SortedListIsSameIter( SortedListEnd(GetList(pqueue)), SortedListInsert(GetList(pqueue),data));
}
void *PQDepqueue(PQueue_t *pqueue)
{	
	void *data = NULL;
	assert(NULL != pqueue);
	data = SortedListGetData(SortedListBegin(GetList(pqueue)));
	SortedListPopFront(GetList(pqueue));
	return data;
}

void *PQPeek(const PQueue_t *pqueue)
{
	assert(NULL != pqueue);
	return SortedListGetData(SortedListBegin(GetList(pqueue)));
}

size_t PQSize(const PQueue_t *pqueue)
{
	assert(NULL != pqueue);
	return SortedListSize(GetList(pqueue));
}
void PQDestroy(PQueue_t *pqueue)
{
	assert(NULL != pqueue);
	SortedListDestroy(GetList(pqueue));
	SetList(pqueue, NULL);
	free (pqueue);
	pqueue = NULL;
}
void PQClear(PQueue_t *pqueue)
{	
	sorted_list_t *list_to_destroy = NULL;
	assert(NULL != pqueue);
	list_to_destroy = SortedListCreate(NULL);
	SortedListMerge(list_to_destroy, GetList(pqueue));
	SortedListDestroy(list_to_destroy);
}
void *PQErase(PQueue_t *pqueue, pq_is_match_func_t is_match, void *data_to_compare)
{
	sorted_list_iter_t iter_to_erase;
	void *data = NULL;
	
	assert(NULL != pqueue);
	
	iter_to_erase = SortedListBegin(GetList(pqueue));

	while(!SortedListIsSameIter(iter_to_erase, SortedListEnd(GetList(pqueue)))
			 && TRUE != is_match(SortedListGetData(iter_to_erase), data_to_compare))
	{
		iter_to_erase = SortedListNext(iter_to_erase);
	}

	if(SortedListIsSameIter(iter_to_erase, SortedListEnd(GetList(pqueue))))
	{
		return NULL;
	}
	data = SortedListGetData(iter_to_erase);
	SortedListRemove(GetList(pqueue), iter_to_erase);
	return data;
}

