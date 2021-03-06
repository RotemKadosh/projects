#include <stdlib.h>/*malloc, free*/
#include <assert.h>/*assert*/

#include "dlist.h" /* Dlist functions*/
#include "sorted_list.h"

/*------------------------MACRO---------------------------*/
#define ZERO (0)


/*----------FUNCTION DECLERATION---------------------*/
static sorted_list_iter_t InitSortListIter(const sorted_list_t *list, Dlist_iter_t iter);


static sorted_list_iter_t FindPlaceToInsert(sorted_list_t *list, sorted_list_iter_t from, sorted_list_iter_t to, void *data);
/*-----------------------STRUCTS--------------------------*/

struct sorted_list
{
	Dlist_t *dlist;
	compare_func_t cmp;
};

/*--------------------------------------------------------*/

static sorted_list_iter_t InitSortListIter(const sorted_list_t *list, Dlist_iter_t iter)
{
	sorted_list_iter_t  s_list_iter;
	s_list_iter.internal_itr = iter;
	(void)list;
	#ifndef NDEBUG
     	s_list_iter.list = (sorted_list_t *)list;
    #endif 	
	return s_list_iter;
}

sorted_list_t *SortedListCreate(compare_func_t sort_func)
{

	sorted_list_t *list = (sorted_list_t *)malloc(sizeof(sorted_list_t));
	if(NULL == list)
	{
		return NULL;
	}
	list->dlist = DlistCreate();
	if(list->dlist == NULL)
	{	
		free(list);
		return NULL;
	}

	list->cmp = sort_func;
	return list;
}


void SortedListDestroy(sorted_list_t *list)
{
	assert(NULL != list);
	DlistDestroy(list->dlist);
	list->dlist = NULL;
	free(list);
	list = NULL;
}

sorted_list_iter_t SortedListBegin(const sorted_list_t *list)
{ 	
	sorted_list_iter_t iter;
	assert(NULL != list);
	iter = InitSortListIter(list, DlistBegin(list->dlist));
	return iter;
}


sorted_list_iter_t SortedListEnd(const sorted_list_t *list)
{
	sorted_list_iter_t iter;
	assert(NULL != list);
	iter = InitSortListIter(list, DlistEnd(list->dlist));
	return iter;
}

int SortedListIsEmpty(const sorted_list_t *list)
{
	assert (NULL != list);
	return DlistIsEmpty(list->dlist);
}

size_t SortedListSize(const sorted_list_t *list)
{
	assert (NULL != list);
	return DlistSize(list->dlist);
}

sorted_list_iter_t SortedListInsert(sorted_list_t *list, void *data)
{
	sorted_list_iter_t where;
	assert(NULL != list);
	where = FindPlaceToInsert(list, SortedListBegin(list), SortedListEnd(list), data);
	where.internal_itr = DlistInsert(list->dlist, where.internal_itr, data);
	if(NULL == where.internal_itr)
	{
		return SortedListEnd(list);
	}
	return where;
}
static sorted_list_iter_t FindPlaceToInsert(sorted_list_t *list, sorted_list_iter_t from, sorted_list_iter_t to, void *data)
{
	assert(NULL != list);
	while(!SortedListIsSameIter(from, to) && ZERO <= list->cmp(SortedListGetData(from), data))
	{
		from = SortedListNext(from);
	}
	return from;
}

sorted_list_iter_t SortedListFindIf(sorted_list_t *list, sorted_list_iter_t from, sorted_list_iter_t to,
					compare_func_t search_func, const void *data_to_compare)
{
	assert(NULL != list);
	while(!SortedListIsSameIter(from, to) && ZERO != search_func(SortedListGetData(from), data_to_compare))
	{
		from = SortedListNext(from);
	}
	(void)list;
	return from;
}




sorted_list_iter_t SortedListFind(sorted_list_t *list, sorted_list_iter_t from, sorted_list_iter_t to, const void *data_to_compare)
{
	assert(NULL != list);
	while(!SortedListIsSameIter(from, to) && ZERO != list->cmp(SortedListGetData(from), data_to_compare))
	{
		from = SortedListNext(from);
	}
	return from;
}

sorted_list_iter_t SortedListRemove(sorted_list_t *list, sorted_list_iter_t iter)
{
	sorted_list_iter_t next;
	assert(NULL != list);
	next = InitSortListIter(list, DlistRemove(list->dlist, iter.internal_itr));
	return next;
}

int SortedListIsSameIter(sorted_list_iter_t one, sorted_list_iter_t two)
{
	return DlistIsSameIter(one.internal_itr, two.internal_itr);
}


void SortedListPopFront(sorted_list_t *list)
{
	assert(NULL != list);
	DlistPopFront(list->dlist);
}


void SortedListPopBack(sorted_list_t *list)
{
	assert(NULL != list);
	DlistPopBack(list->dlist);
}


sorted_list_iter_t SortedListNext(sorted_list_iter_t iter)
{

	iter.internal_itr = DlistNext(iter.internal_itr);
	return iter;
}

sorted_list_iter_t SortedListPrev(sorted_list_iter_t iter)
{

	iter.internal_itr = DlistPrev(iter.internal_itr);
	return iter;
}


void *SortedListGetData(const sorted_list_iter_t iter)
{

	return DlistGetData(iter.internal_itr);
}



int SortedListForEach(sorted_list_iter_t from, sorted_list_iter_t to, 
									action_func_t action_func, void *param)
{

	return DlistForEach(from.internal_itr, to.internal_itr, action_func, param);
}


sorted_list_t *SortedListMerge(sorted_list_t *dest, sorted_list_t *src)
{
	sorted_list_iter_t src_from;
	sorted_list_iter_t src_to;
	sorted_list_iter_t where;
	assert(NULL != dest);
	assert(NULL != src);
	src_from = SortedListBegin(src);
	src_to = SortedListBegin(src);
	where = SortedListBegin(dest);
	if(SortedListIsEmpty(dest))
	{
		src_to = SortedListEnd(src);
		DlistSplice(where.internal_itr, src_from.internal_itr, src_to.internal_itr);
	}
	while (!SortedListIsEmpty(src) &&  !SortedListIsSameIter(where,SortedListEnd(dest)))
	{	
		where = FindPlaceToInsert(dest, where, SortedListEnd(dest), SortedListGetData(src_from));
		src_to = FindPlaceToInsert(src, src_from, SortedListEnd(src), SortedListGetData(where));
		DlistSplice(where.internal_itr, src_from.internal_itr, src_to.internal_itr);
		src_from = src_to;
	}
	if (!SortedListIsEmpty(src))
    {
        DlistSplice(where.internal_itr, src_from.internal_itr, 
            SortedListEnd(src).internal_itr);
    }
	return dest;
}


