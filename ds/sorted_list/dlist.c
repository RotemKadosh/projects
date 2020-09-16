#include <stdlib.h>/*malloc, free*/
#include <assert.h>/*assert*/
#include "dlist.h"
/*approved by moshe*/

#define SUCCESS (0)
#define FAIL (-1)
#define FALSE (0)

typedef struct dlist_node dlist_node_t;

static dlist_node_t *CreateNode(void *value);
static void ConectNodes(Dlist_iter_t first, Dlist_iter_t second);

struct dlist_node
{
	void *value;
	dlist_node_t *next;
	dlist_node_t *prev;

};

struct dlist
{
	dlist_node_t head_dummy;
	dlist_node_t tail_dummy;
};

static dlist_node_t *CreateNode(void *value)
{	
	dlist_node_t *new_node = (dlist_node_t *)malloc(sizeof(dlist_node_t));
	if(NULL == new_node)
	{
		return NULL;
	}
	new_node->value = value;
	new_node->next = NULL;
	new_node->prev = NULL;
	return new_node;
}
Dlist_t *DlistCreate(void)
{
	Dlist_t *list = NULL;
	list = (Dlist_t *)malloc(sizeof(Dlist_t));
	if (NULL == list)
	{
		return NULL;
	}
	DlistSetData(&list->tail_dummy, (void *)list);
	DlistSetData(&list->head_dummy, (void *)list);

	list->head_dummy.prev = NULL;
	ConectNodes(&list->head_dummy, &list->tail_dummy);
	list->tail_dummy.next = NULL;

	return list;
}
void DlistDestroy(Dlist_t *list)
{
	Dlist_iter_t iter_current = NULL;
	Dlist_iter_t iter_next = NULL;

	assert(NULL != list);

	iter_current =DlistNext(&list->head_dummy);
	while (NULL != iter_current->next)
	{
		iter_next =DlistNext(iter_current);
		free(iter_current);
		iter_current = NULL;
		iter_current = iter_next;
	} 

	free(list);
	list = NULL;
}
Dlist_iter_t DlistBegin(const Dlist_t *list)
{
	assert(NULL != list);
	return list->head_dummy.next;
}
Dlist_iter_t DlistEnd(const Dlist_t *list)
{
	assert(NULL != list);
	return list->tail_dummy.prev->next;
}
int DlistIsSameIter(Dlist_iter_t one, Dlist_iter_t two)
{
	return (one == two);
}
void *DlistGetData(const Dlist_iter_t iter)
{
	assert(NULL != iter);
	return iter->value;
}
Dlist_iter_t DlistInsert(Dlist_t *list, Dlist_iter_t where, void *data)
{
	Dlist_iter_t new_node = NULL;
	assert(NULL != where);
	assert(NULL != list);
	new_node = CreateNode(data);
	if (NULL == new_node)
	{
		return DlistEnd(list);
	}
	ConectNodes(DlistPrev(where), new_node);
	ConectNodes(new_node, where);
	return new_node;
}
int DlistIsEmpty(const Dlist_t *list)
{
	assert(NULL != list);
	return DlistIsSameIter(DlistBegin(list), DlistEnd(list));
}
Dlist_iter_t DlistNext(Dlist_iter_t iter)
{
	assert(NULL != iter);
	return iter->next;
}
Dlist_iter_t DlistPrev(Dlist_iter_t iter)
{
	assert(NULL != iter);
	assert(NULL != iter->prev);
	return iter->prev;
}
void DlistSetData(Dlist_iter_t iter, void *data)
{
	assert(NULL != iter);
	iter->value = data;
}
Dlist_iter_t DlistRemove(Dlist_t *list, Dlist_iter_t iter)
{
	dlist_node_t *next = NULL;
	assert(NULL != iter);
	assert(NULL != iter->next);

	ConectNodes(DlistPrev(iter), DlistNext(iter));
	next = iter->next;
	free(iter);
	iter = NULL;
	(void) list;
	return (Dlist_iter_t)next;
}

Dlist_iter_t DlistPushFront(Dlist_t *list, void *data)
{
	assert(NULL != list);
	return DlistInsert(list, DlistBegin(list), data);
}

Dlist_iter_t DlistPushBack(Dlist_t *list, void *data)
{
	assert(NULL != list);
	return DlistInsert(list, DlistEnd(list), data);
}

void DlistPopFront(Dlist_t *list)
{
	assert(NULL != list);
	DlistRemove(list, DlistBegin(list));
}

void DlistPopBack(Dlist_t *list)
{
	assert(NULL != list);
	DlistRemove(list, DlistPrev(DlistEnd(list)));
}
size_t DlistSize(const Dlist_t *list)
{
	Dlist_iter_t runner = NULL;
	size_t count = 0;
	assert(NULL != list);
	runner = DlistBegin(list);
	while(!DlistIsSameIter(runner, DlistEnd(list)))
	{
		++count;
		runner = runner->next;
	}
	return count;
}

int DlistForEach(Dlist_iter_t from, Dlist_iter_t to, action_func_t action_func, void *param)
{
	Dlist_iter_t runner = from;
	int action_status = SUCCESS;
	assert(NULL != from);
	assert(NULL != action_func);

	while(!DlistIsSameIter(runner, to) && SUCCESS == action_status)
	{
		action_status = action_func(runner->value, param);
		runner = runner->next;
	}
	return action_status;
}

Dlist_iter_t DlistFind(Dlist_iter_t from, Dlist_iter_t to, is_match_func_t is_match_func, const void *data_to_compare)
{
	Dlist_iter_t runner = from;
	assert(NULL != from);

	while (!DlistIsSameIter(runner, to) && (!is_match_func(DlistGetData(runner), data_to_compare)))
	{
		runner = DlistNext(runner);
	}
	return runner;
}

int DlistMultiFind(Dlist_t *dest, Dlist_iter_t from, Dlist_iter_t to, is_match_func_t is_match_func, const void *data_to_compare)
{
	Dlist_iter_t runner = from;
	assert(NULL != from);
	assert(NULL != to);
	assert(NULL != dest);
	while (!DlistIsSameIter(runner, to))
	{
		if(is_match_func(DlistGetData(runner), data_to_compare))
		{
			if(NULL == DlistPushBack(dest, DlistGetData(runner)))
			{
				return FAIL;
			}
		}
		runner = DlistNext(runner);
	}
	return SUCCESS;
}

Dlist_iter_t DlistSplice(Dlist_iter_t where, Dlist_iter_t src_from, Dlist_iter_t src_to)
{
	dlist_node_t *form_prev = NULL;
	assert(NULL != src_from);
	assert(NULL != src_to);
	assert(NULL != where);
	if(!DlistIsSameIter(src_from, src_to))
	{
		form_prev = DlistPrev(src_from);
		/*attaching to new list*/
		ConectNodes(DlistPrev(where), src_from);
		ConectNodes(DlistPrev(src_to), where);
		/*cut out from old list*/
		ConectNodes(form_prev, src_to);
		return	DlistPrev(DlistPrev(where));
	}
	else
	{
		return NULL;
	}
}
static void ConectNodes(dlist_node_t *first, dlist_node_t *second)
{
	assert(NULL != first);
	assert(NULL != second);
	first->next = second;
	second->prev = first;
}