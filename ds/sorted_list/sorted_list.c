#include <stdlib.h>/*malloc, free*/
#include <assert.h>/*assert*/

#include "dlist.h" /* Dlist_t and all its functions*/
#include "sorted_list.h"

/*------------------------MACRO---------------------------*/



/*----------FUNCTION DECLERATION---------------------*/



/*-----------------------TYPEDEF--------------------------*/

/*-----------------------STRUCTS--------------------------*/

struct sorted_list
{
	Dlist_t *dlist;
	compare_func_t cmp;
};

/*--------------------------------------------------------*/
/*
static Dlist_iter_t GetDlistIter(sorted_list_iter_t iter) 
{
	#ifdef NDEBUG
    	return (Dlist_iter_t)iter;
    #else
    	return iter.internal_iter;
    #endif

}
*/
static sorted_list_iter_t InitSortListIter(const sorted_list_t *list, Dlist_iter_t iter)
{
	#ifdef NDEBUG
    	(void)list;
    	return (sorted_list_iter_t)iter;
    #else
     	sorted_list_iter_t  s_list_iter;
     	s_list_iter.internal_iter = iter;
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
	where = SortedListFind(list,SortedListBegin(list),SortedListEnd(list), data);
	where.internal_iter = DlistInsert(list->dlist, where.internal_iter, data);
	return where;
}

sorted_list_iter_t SortedListFind(sorted_list_t *list, sorted_list_iter_t from, sorted_list_iter_t to, const void *data_to_compare)
{
	sorted_list_iter_t where;
	assert(NULL != list);
	where = InitSortListIter(list, DlistFind(from.internal_iter, to.internal_iter , list->cmp, data_to_compare));
	return where;
}

sorted_list_iter_t SortedListRemove(sorted_list_t *list, sorted_list_iter_t iter)
{
	sorted_list_iter_t next;
	assert(NULL != list);
	next = InitSortListIter(list, DlistRemove(list->dlist, iter.internal_iter));
	return next;
}

int SortedListIsSameIter(sorted_list_iter_t one, sorted_list_iter_t two)
{
	return DlistIsSameIter(one.internal_iter, two.internal_iter);
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
	iter.internal_iter = DlistNext(iter.internal_iter);
	return iter;
}

sorted_list_iter_t SortedListPrev(sorted_list_iter_t iter)
{
	iter.internal_iter = DlistPrev(iter.internal_iter);
	return iter;
}


void *SortedListGetData(const sorted_list_iter_t iter)
{
	return DlistGetData(iter.internal_iter);
}

sorted_list_iter_t SortedListFindIf(sorted_list_t *list, sorted_list_iter_t from, sorted_list_iter_t to,
					compare_func_t search_func, const void *data_to_compare)
{
	
	assert(NULL != list);
	
	return InitSortListIter(list, DlistFind(from.internal_iter , to.internal_iter , search_func, data_to_compare));
}


int SortedListForEach(sorted_list_iter_t from, sorted_list_iter_t to, 
									action_func_t action_func, void *param)
{
	return DlistForEach(from.internal_iter, to.internal_iter, action_func, param);
}



