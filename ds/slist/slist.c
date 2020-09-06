#include <stdlib.h> /*malloc, free*/
#include <assert.h> /*assert*/
#include "slist.h"
#define TRUE (1)
#define FALSE (0)

/*approved by may*/

typedef struct slist_node
{
	void *value;
	Slist_iter_t next;
}slist_node_t;

struct slist
{
	Slist_iter_t head;
	Slist_iter_t tail;
};


static int CountFunc(void *data, void *param);
static slist_node_t *CreateNode(void *value);
static Slist_iter_t TraversToEnd(Slist_iter_t iter);


static Slist_iter_t CreateNode(void *value)
{	
	slist_node_t *new_node = (slist_node_t *)malloc(sizeof(slist_node_t));
	if(NULL == new_node)
	{
		return NULL;
	}
	new_node->value = value;
	return new_node;
}
Slist_iter_t SlistBegin(const Slist_t *list)
{
	assert(NULL != list);
	return list->head;
}
Slist_iter_t SlistEnd(const Slist_t *list)
{
	assert(NULL != list);
	return list->tail;
}
Slist_iter_t SlistNext(Slist_iter_t iter)
{	
	assert(NULL != iter);
	return iter->next;
}
int SlistIsSameIter(Slist_iter_t one, Slist_iter_t two)
{
	assert(NULL != one);
	assert(NULL != two);
	if(one->value == two->value && one->next == two->next)
	{
		return TRUE;
	}
	return FALSE;
}
Slist_t *SlistCreate(void)
{
	Slist_t *list = NULL;
	slist_node_t *dummy = NULL;
	list = (Slist_t *)malloc(sizeof(Slist_t));
	if (NULL == list)
	{
		return NULL;
	}

	dummy = CreateNode((void *)list);
	if(NULL == dummy)
	{
		free(list);
		return NULL;
	}

	list->head = dummy;
	list->tail = dummy;
	list->head->next = list->tail;
	list->tail->next = NULL;
	return list;
}

void SlistDestroy(Slist_t *list)
{
	Slist_iter_t iter_current = NULL;
	Slist_iter_t iter_next = NULL;

	assert(NULL != list);

	iter_current = list->head;
	do
	{
		iter_next = iter_current->next;
		free(iter_current);
		iter_current = iter_next;
	} while (NULL != iter_next);
	free(list);
}
void *SlistGetData(const Slist_iter_t iter)
{
	assert(NULL != iter);
	return iter->value;
}
void SlistSetData(Slist_iter_t iter, void *data)
{
	assert(NULL != iter);
	iter->value = data;
}
static Slist_iter_t TraversToEnd(Slist_iter_t iter)
{

	while (NULL != iter->next)
	{
		iter = iter->next;
	}
	return iter;
}
Slist_iter_t SlistInsert(Slist_iter_t where, void *data)
{
	Slist_iter_t new_node = NULL;
	assert(NULL != where);

	new_node = CreateNode(where->value);

	if (NULL == new_node)
	{
		return TraversToEnd(where);
	}
	if (NULL == where->next)
    {
        ((Slist_t *)where->value)->tail = new_node;
    
	}

	new_node->next = where->next;

	where->value = data;
	where->next = new_node;

	return where;
}
Slist_iter_t SlistRemove(Slist_iter_t iter)
{
	Slist_iter_t next = NULL;
	assert(NULL != iter);
	if (NULL == iter->next)
	{
		return iter;
	}

	next = iter->next;
	iter->value = next->value;
	iter->next = next->next;
	free(next);

	if (NULL == iter->next)
	{
 		((Slist_t *)iter->value)->tail = iter;
	}

	return iter;
}
static int CountFunc(void *data, void *param)
{
	(void)data;
	++*(int *)param;
	return 0;
}
size_t SlistCount(const Slist_t *list)
{

	size_t count = 0;

	assert(NULL != list);
	 
	SlistForEach(SlistBegin(list), SlistEnd(list), CountFunc, &count);

	return count;
}

Slist_iter_t SlistFind(Slist_iter_t from, Slist_iter_t to,const void *data_to_compare, is_match_func_t is_match_func)
{
	while (!SlistIsSameIter(from, to) && !is_match_func(from->value, data_to_compare))
	{
		from = from->next;
	}
	return from;
}
int SlistForEach(Slist_iter_t from, Slist_iter_t to, action_func_t action_func, void *param)
{
	int res = 0;
	while (!SlistIsSameIter(from, to))
	{
		res = action_func(from->value, param);
		from = from->next;
	}
	return res;
}

Slist_t *SlistAppend(Slist_t *first, Slist_t *last)
{
	void *address_of_first_list = first->tail->value;
	first->tail->next = last->head;
	SlistRemove(SlistEnd(first));;
	last->tail->value = address_of_first_list;
	first->tail = last->tail;
	free(last);
	return first;
}
