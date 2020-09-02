#include <stdlib.h>/*malloc, free*/
#include "slist.h"
#define TRUE (1)
#define FALSE (0)


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
static Slist_iter_t CreateNode(void *value);
static Slist_iter_t TraversToEnd(Slist_iter_t iter);


static Slist_iter_t CreateNode(void *value)
{
	slist_node_t *new_node = (slist_node_t *)malloc(sizeof(slist_node_t));
	if(NULL == new_node)
	{
		return NULL;
	}
	new_node->value = value;
	return (Slist_iter_t)new_node;
}
Slist_iter_t SlistBegin(const Slist_t *list)
{

	return list->head;
}
Slist_iter_t SlistEnd(const Slist_t *list)
{

	return (Slist_iter_t)list->tail;
}
Slist_iter_t SlistNext(Slist_iter_t iter)
{
	slist_node_t *iter_node = (slist_node_t *)iter;
	return iter_node->next;
}
int SlistIsSameIter(Slist_iter_t one, Slist_iter_t two)
{

	if(one->value == two->value && one->next == two->next)
	{
		return TRUE;
	}
	return FALSE;
}
Slist_t *SlistCreate(void)
{
	Slist_t *list = NULL;
	Slist_iter_t dummy = NULL;
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
	Slist_iter_t iter_current = list->head;
	Slist_iter_t iter_next = iter_current->next;
	do
	{
		iter_next = iter_current->next;
		free(iter_current);
		iter_current = iter_next;
	}while (NULL != iter_next);
	free(list);
}
void *SlistGetData(const Slist_iter_t iter)
{

	return iter->value;
}
void SlistSetData(Slist_iter_t iter, void *data)
{

	iter->value = data;
}
static Slist_iter_t TraversToEnd(Slist_iter_t iter)
{
	while(NULL != iter->next)
	{
		iter = iter->next;
	}
	return iter;
}
Slist_iter_t SlistInsert(Slist_iter_t where, void *data)
{
	Slist_iter_t new_node = CreateNode(where->value);
	if(NULL == new_node)
	{
		return TraversToEnd(where);
	}
	if (NULL == where->next)
    {
        ((Slist_t *)where->value)->tail = new_node;
    
	}
	new_node->next = where->next;
	SlistSetData(where, data);
	where->next = new_node;
	return where;
}
Slist_iter_t SlistRemove(Slist_iter_t iter)
{
	Slist_iter_t next = NULL;
	if(NULL == iter->next)
	{
		return iter;
	}
	next = iter->next;
	iter->value = next->value;
	iter->next = next->next;
	free(next);
	if(NULL == iter->next){
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
	Slist_iter_t iter_begin = NULL;
	Slist_iter_t iter_End = NULL;
	iter_begin = SlistBegin(list);
	iter_End = SlistEnd(list);
	SlistForEach(iter_begin, iter_End, CountFunc, &count);
	return count;
}

Slist_iter_t SlistFind(Slist_iter_t from, Slist_iter_t to,const void *data_to_compare, is_match_func_t is_match_func)
{
	while(!SlistIsSameIter(from, to) && !is_match_func(from->value, data_to_compare))
	{
		from = from->next;
	}
	return from;
}
int SlistForEach(Slist_iter_t from, Slist_iter_t to, action_func_t action_func, void *param)
{
	int res = 0;
	while(!SlistIsSameIter(from, to))
	{
		res = action_func(from->value, param);
		from = from->next;
	}
	return res;
}

