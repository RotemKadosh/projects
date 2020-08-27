#include <stdio.h> /* printf */

#include "stack.h"


void TestStackOpertions();

int main()
{
	TestStackOpertions();
	return 0;
}




void TestStackOpertions()
{	
	int test1 = 0, test2 = 0, test3 = 0, test4 = 0, test5 = 0, test6 = 0, test7 = 0;
	float element1 = 8.4;
	char element4 = 'c';
	char element4Com = 0;
	stack_t *stack = StackCreate( 20 );
	if(NULL == stack)
	{
		return;
	}
	else
	{
		test1 = 1;
	}
	
	StackPush(stack,(void *)(size_t)element1);

	test2 = (1 == StackSize(stack));
	if (test2)
	{
		test3 = 1;
	}
	StackPop(stack);
	test4 = (0 == StackSize(stack));

	test5 = (1 == StackIsEmpty(stack));

	StackPush(stack, (void *)(size_t)element4);
	element4Com = (char)(size_t)StackPeek(stack);
	test6 = (element4Com == element4);

	test7 = (20 == StackCapacity(stack));

	StackDestroy(stack);

	if (test1 && test2 && test3 && test4 && test5 && test6 && test7)
	{
		printf("Stack operations works\n");
	}
	else
	{
		printf("Stack operations faild.\ntest1(StackCreate): %d\ntest2(StackPush): %d\ntest3(stackSize): %dtest4(StackPop): %d\ntest5(StackIsEmpty):%d\ntest6(StackPeek): %d\ntest7(StackCapacity): %d\n",test1, test2, test3, test4, test5, test6, test7);
	}
}

