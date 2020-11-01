#include <stdlib.h> /*malloc, free*/
#include <assert.h> /*assert*/
#include "pqueue.h" 
#include "../heap/heap.h"

struct pqueue
{
	Heap_ty *heap;
};

PQueue_t *PQCreate(pq_compare_func_t compare_func)
{
	PQueue_t *pq = (PQueue_t *)malloc(sizeof(PQueue_t));
	if( NULL == pq)
	{
		return NULL;
	}
	pq->heap = HeapCreate(compare_func);
	if(NULL == pq->heap)
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
	return HeapIsEmpty(pqueue->heap);
}

void *PQPeek(const PQueue_t *pqueue)
{
	assert(NULL != pqueue);
	return HeapPeek(pqueue->heap);
}

size_t PQSize(const PQueue_t *pqueue)
{
	assert(NULL != pqueue);
	return HeapSize(pqueue->heap);
}

void PQDestroy(PQueue_t *pqueue)
{
	assert(NULL != pqueue);
	HeapDestroy(pqueue->heap);
	pqueue->heap = NULL;
	free (pqueue);
	pqueue = NULL;
}

void *PQDepqueue(PQueue_t *pqueue)
{	
	void *data = NULL;
	assert(NULL != pqueue);

	data = HeapPeek(pqueue->heap);
	HeapPop(pqueue->heap);
	return data;
}

int PQEnpqueue(PQueue_t *pqueue, void *data)
{
	int ans = 0;
    
    assert(NULL != pqueue);

    ans = HeapPush(pqueue->heap, data);
    return ans;
}

void PQClear(PQueue_t *pqueue)
{
    while(!PQIsEmpty( pqueue))
    {
        PQDepqueue(pqueue);
    }
}

void *PQErase(PQueue_t *pqueue, pq_is_match_func_t is_match, void *data_to_compare)
{
    return HeapRemove(pqueue->heap, is_match, data_to_compare);
}

