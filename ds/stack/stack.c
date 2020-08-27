#include <stdlib.h> /*malloc, free*/
#include <assert.h> /* assert */
#include "stack.h"
struct stack
{
  int top;
  size_t capacity;
  void **stack_elements;
};

stack_t *StackCreate(size_t capacity)
{
	stack_t *stack = NULL;
	assert(0 < capacity);
	stack = (stack_t *)malloc(sizeof(stack_t));

	if(NULL == stack)
	{
		return NULL;
	}

	stack->top = -1;
	stack->capacity = capacity;

	stack->stack_elements = malloc(sizeof(void *) * capacity);
	if(NULL == stack->stack_elements)
	{
		return NULL;
	}

	return stack;
}
void StackDestroy(stack_t *stack)
{
	free(stack->stack_elements);
	stack->stack_elements = NULL;
	free(stack);
	stack = NULL;
}
void StackPop(stack_t *stack)
{
	assert(NULL != stack);
	--(stack->top);
}
void StackPush(stack_t *stack , void *element)
{	
	assert(NULL != stack);
	assert(NULL != stack->stack_elements);
	stack->stack_elements[stack->top + 1] = element;
	++stack->top;
}
void *StackPeek(const stack_t *stack)
{
	assert(NULL != stack);
	assert(NULL != stack->stack_elements);
	return stack->stack_elements[stack->top];
}
size_t StackSize(const stack_t *stack)
{	
	assert(NULL != stack);
	return stack->top + 1;
}

int StackIsEmpty(const stack_t *stack)
{
	assert(NULL != stack);
	return (-1 >= stack->top);
}
size_t StackCapacity(const stack_t *stack)
{
	assert(NULL != stack);
	return stack->capacity;
}
