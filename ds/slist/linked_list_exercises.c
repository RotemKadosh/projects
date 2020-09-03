#include <stdlib.h>
#include <stdio.h>
#include "../utils/test.h"
typedef struct node
{
    void *data;
    struct node *next;
} node_t;


node_t *Flip(node_t *head);

int HasLoop(const node_t *head);

node_t *FindIntersection(node_t *head_1, node_t *head_2);

node_t *Flip(node_t *head)
{
	node_t *prev = NULL;
	node_t *curr = head;
	node_t *next = NULL;
	while (NULL != curr)
	{
		next = curr->next;
		curr->next = prev;
		
		prev = curr;
		curr = next;
	}
	head = prev;
	return head;
}
static void PrintIntList(node_t *head)
{
	while(head->next != NULL)
	{
		printf("%lu ->",(size_t)head->data);
		head = head->next;
	}
	printf("%lu\n",(size_t)head->data);
}	
	
int HasLoop(const node_t *head)
{
	const node_t *slow_runner = head;
	const node_t *fast_runner = head;
	while (NULL != fast_runner->next && NULL != fast_runner->next->next)
	{
		slow_runner = slow_runner->next;
		fast_runner = fast_runner->next->next;
		if(slow_runner == fast_runner)
		{
			return 1;
		}
	
	}
	return 0;
} 
static size_t CountNodes(node_t *head)
{
	size_t count = 0;
	do
	{
		++count;
		head = head->next;
	} while (head != NULL);
	return count;
}

static node_t *MoveForward(node_t *node, size_t steps)
{
	while (0 < steps--)
	{	
		node = node->next;
	}
	return node;
}

node_t *FindIntersection(node_t *head_1, node_t *head_2)
{
	size_t c1 = CountNodes(head_1);
	size_t c2 = CountNodes(head_2);
	if(c1 > c2)
	{
		head_1 = MoveForward(head_1 , c1 -c2);
	}
	else
	{
		head_2 = MoveForward(head_2 , c2 - c1);
	}
	while(head_1 != head_2 && NULL != head_1)
	{
		head_1 = head_1->next;
		head_2 = head_2->next;
	}
	return head_1;
}

static test_status_t TestHasLoop()
{
	
	node_t *node1 = (node_t *)malloc(sizeof(node_t));
	node_t *node2 = (node_t *)malloc(sizeof(node_t));
	node_t *node3 = (node_t *)malloc(sizeof(node_t));
	node_t *node4 = (node_t *)malloc(sizeof(node_t));
	node_t *node5 = (node_t *)malloc(sizeof(node_t));
	node_t *node6 = (node_t *)malloc(sizeof(node_t));

	node1->data = (void *)1;
	node2->data = (void *)2;
	node3->data = (void *)3;
	node4->data = (void *)4;
	node5->data = (void *)5;
	node6->data = (void *)6;

	node1->next = node2;
	node2->next = node3;
	node3->next = node4;
	node4->next = node5;
	node5->next = node6;
	node6->next = NULL;

	REQUIRE(0 == HasLoop(node1));

	node1->next = node2;
	node2->next = node3;
	node3->next = node4;
	node4->next = node5;
	node5->next = node6;
	node6->next = node1;
	REQUIRE(1 == HasLoop(node1));

	node1->next = node2;
	node2->next = node3;
	node3->next = node4;
	node4->next = node5;
	node5->next = node4;
	node6->next = node1;
	REQUIRE(1 == HasLoop(node1));

	free(node1);
	free(node2);
	free(node3);
	free(node4);
	free(node5);
	free(node6);

	return PASSED;
}
static test_status_t TestFindIntersection()
{
	
	node_t *node1 = (node_t *)malloc(sizeof(node_t));
	node_t *node2 = (node_t *)malloc(sizeof(node_t));
	node_t *node3 = (node_t *)malloc(sizeof(node_t));
	node_t *node4 = (node_t *)malloc(sizeof(node_t));
	node_t *node5 = (node_t *)malloc(sizeof(node_t));
	node_t *node6 = (node_t *)malloc(sizeof(node_t));

	node1->data = (void *)1;
	node2->data = (void *)2;
	node3->data = (void *)3;
	node4->data = (void *)4;
	node5->data = (void *)5;
	node6->data = (void *)6;

	node1->next = node2;
	node2->next = node3;
	node3->next = NULL;

	node4->next = node5;
	node5->next = node6;
	node6->next = node1;

	REQUIRE(node1 == FindIntersection(node1 , node4));

	node1->next = node2;
	node2->next = node3;
	node3->next = node4;
	node4->next = node5;

	node5->next = node6;
	node6->next = NULL;
	REQUIRE(node5 == FindIntersection(node1 , node5));

	node1->next = node6;

	node2->next = node3;
	node3->next = node4;
	node4->next = node5;
	node5->next = NULL;
	node6->next = NULL;
	REQUIRE(NULL == FindIntersection(node1 , node2));

	free(node1);
	free(node2);
	free(node3);
	free(node4);
	free(node5);
	free(node6);

	return PASSED;
}
static test_status_t TestReverseList()
{
	node_t *node1 = (node_t *)malloc(sizeof(node_t));
	node_t *node2 = (node_t *)malloc(sizeof(node_t));
	node_t *node3 = (node_t *)malloc(sizeof(node_t));
	node_t *node4 = (node_t *)malloc(sizeof(node_t));
	node_t *node5 = (node_t *)malloc(sizeof(node_t));
	node_t *node6 = (node_t *)malloc(sizeof(node_t));

	node1->data = (void *)1;
	node2->data = (void *)2;
	node3->data = (void *)3;
	node4->data = (void *)4;
	node5->data = (void *)5;
	node6->data = (void *)6;

	node1->next = node2;
	node2->next = node3;
	node3->next = node4;
	node4->next = node5;
	node5->next = node6;
	node6->next = NULL;
	PrintIntList(node1);
	node1 = Flip(node1);
	PrintIntList(node1);
	return PASSED;
}




int main()
{
	RUNTEST(TestHasLoop);
	RUNTEST(TestFindIntersection);
	RUNTEST(TestReverseList);

	return 0;
}