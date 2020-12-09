#include <stdio.h>
#include <assert.h>
#include "../ds/stack/stack.h"


void SortIn(stack_t *stack, int element);
void SortExt(stack_t *stack)
{   
    int temp = 0;

    assert(NULL != stack);

    if(!StackIsEmpty(stack))
    {
        temp =(int)StackPeek(stack);
        StackPop(stack);
        SortExt(stack);
        SortIn(stack, temp);
    }
}
void SortIn(stack_t *stack, int element)
{
    int temp = 0;

    assert(NULL != stack);

    if(StackIsEmpty(stack) || element > (int)StackPeek(stack))
    {
        StackPush(stack, element);
    }
    else
    {
        temp = StackPeek(stack);
        StackPop(stack);
        SortIn(stack,element);
        StackPush(stack, temp);
    }
    
}

int main(int argc, char **argv)
{
    stack_t *st = StackCreate(10);
    StackPush(st, 3);
    StackPush(st, 2);
    StackPush(st, 1);
    StackPush(st, 4);
    StackPush(st, 7);
    StackPush(st, 6);
    StackPush(st, 5);
    StackPush(st, 10);
    StackPush(st, 9);
    StackPush(st, 8);

    SortExt(st);

    while(!StackIsEmpty(st))
    {
        printf("%d\n", (int)StackPeek(st));
        StackPop(st);
    }

}