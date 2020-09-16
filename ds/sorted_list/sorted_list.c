#include <stdlib.h>/*malloc, free*/
#include <assert.h>/*assert*/

#include "dlist.h" /* Dlist functions*/
#include "sorted_list.h"

/*------------------------MACRO---------------------------*/
#define ZERO (0)


/*----------FUNCTION DECLERATION---------------------*/
static sorted_list_iter_t InitSortListIter(const sorted_list_t *list, Dlist_iter_t iter);


static sorted_list_iter_t FindPlaceToInsert(sorted_list_t *list, sorted_list_iter_t begin, sorted_list_iter_t end, void *data);
/*-----------------------STRUCTS--------------------------*/

struct sorted_list
{
	Dlist_t *dlist;
	compare_func_t cmp;
};

/*--------------------------------------------------------*/

static sorted_list_iter_t InitSortListIter(const sorted_list_t *list, Dlist_iter_t iter)
{
	#ifdef NDEBUG
    	(void)list;
    	return (sorted_list_iter_t)iter;
    #else
     	sorted_list_iter_t  s_list_iter;
     	s_list_iter.internal_itr = iter;
     	s_list_iter.list = (sorted_list_t *)list;
     	return s_list_iter;
    #endif 	
}

sorted_list_t *SortedListCreate(compare_func_t sort_func)
{

	sorted_list_t *list = (sorted_list_t *)malloc(sizeof(sorted_list_t));
	if(NULL == list)
	{
		return NULL;
	}

	assert(NULL != sort_func);

	list->dlist = DlistCreate();
	if(list->dlist == NULL)
	{
		return NULL;
	}

	list->cmp = sort_func;
	return list;
}
/*--------------------------------------------------------*/

void SortedListDestroy(sorted_list_t *list)
{
	assert(NULL != list);
	DlistDestroy(list->dlist);
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
	return where;
}

sorted_list_iter_t SortedListFindIf(sorted_list_t *list, sorted_list_iter_t from, sorted_list_iter_t to,
					compare_func_t search_func, const void *data_to_compare)
{
	assert(NULL != list);
	while(!SortedListIsSameIter(from, to) && ZERO != search_func(SortedListGetData(from), data_to_compare))
	{
		from = SortedListNext(from);
	}
	return from;

}


static sorted_list_iter_t FindPlaceToInsert(sorted_list_t *list, sorted_list_iter_t begin, sorted_list_iter_t end, void *data)
{
	assert(NULL != list);
	while(!SortedListIsSameIter(begin, end) && ZERO <= list->cmp(SortedListGetData(begin), data))
	{
		begin = SortedListNext(begin);
	}
	return begin;

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

	where = FindPlaceToInsert(dest, SortedListBegin(dest), SortedListEnd(dest), SortedListGetData(src_from));
	
	while (!SortedListIsEmpty(src))
	{	
		src_to = FindPlaceToInsert(src, src_from, SortedListEnd(src), SortedListGetData(where));
		src_from.internal_itr = DlistSplice(where.internal_itr, src_from.internal_itr, src_to.internal_itr);
		where = FindPlaceToInsert(dest, SortedListBegin(dest), SortedListEnd(dest), SortedListGetData(src_from));
		
	}

	return dest;
}
