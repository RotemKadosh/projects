/*recursions*/
#include "../../ds/utils/test.h"
#include <string.h>
#include <stdio.h> 
#include <stdlib.h>
#include "recursion.h"
#include "../../ds/stack/stack.h"
#define TRUE (1)
#define FALSE (0)



int fibonachi(int index);
int recurs_fibb(int num1, int num2, int index);
int Strlen(const char *str);
int StrCmp(const char *str1, const char *str2);
node_ty *FlipList(node_ty *node);
int *GetMinToTop(stack_t *stack);
static int StrS(const char *s1, const char *s2);


int fibonachi(int index)
{
    if(index == 1)
    {
        return 0;
    }
    if(index == 2)
    {
        return 1;
    }
    return fibonachi(index - 2) + fibonachi(index -1) ;
}

int Strlen(const char *str)
{
    if(*str == '\0')
    {
        return 0;
    }
    return 1 + Strlen(++str); 
}

int StrCmp(const char *str1, const char *str2)
{
    if(*str1 == '\0' || *str2 == '\0')
    {
        return (*str1 > *str2)? 1 : (*str1 == *str2)? 0:-1;
    }
    if(*str1 - *str2 > 0 )
    {
        return 1;
    }
    if(*str1 - *str2 < 0)
    {
        return -1;
    }
    return StrCmp(++str1 , ++str2); 
}

char *Strcpy(char *dest, const char *src)
{
    if(*src == '\0')
    {
        *dest = *src;
        return dest;
    }
    *dest = *src;
    return Strcpy(++dest , ++src) - 1; 
}

char *Strcat(char *dest, const char *src)
{
    if(*dest == '\0')
    {
        return Strcpy(dest, src);
    }
    Strcat(++dest, src);
    return dest - 1;
}

static int StrS(const char *s1, const char *s2)
{
    if(*s2 == '\0')
    {
        return TRUE;
    }
    if(*s1 != *s2)
    {
        return FALSE;
    }
    return StrS(s1 + 1, s2 + 1);
}

const char *Strstr( const char *hystack, const char *needle)
{
    if(StrS(hystack, needle))
    {
       return hystack;
    }
    else if ('\0' == *hystack)
    {
       return NULL;
    }
  
   return Strstr( hystack + 1, needle);
}

node_ty *FlipList(node_ty *node)
{ 
    node_ty* rest = NULL;
    if (node == NULL || node->next == NULL) 
    {
        return node;
    }
    rest = FlipList(node->next); 
    node->next->next = node; 
    node->next = NULL; 

    return rest; 
} 
    
stack_t *SortStack(stack_t *stack, size_t size)
{   
    int num = 0;
    if(size == 0)
    {
        return stack;
    }
    num = *(int *)GetMinToTop(stack);
    StackPush(stack, &num);
    return SortStack(stack, --size);
}

int *GetMinToTop(stack_t *stack)
{   
    int *next = NULL;
    int *num = StackPeek(stack);
    int is_num_max_flage = 0;
    StackPop(stack);
    if(StackSize(stack) == 0)
    {
        return num;
    }
    next = GetMinToTop(stack);
    is_num_max_flage = (*num > *next) ? 1 : 0;
    if(is_num_max_flage)
    {
        StackPush(stack, num);
        return next;
    }
    StackPush(stack, next);
    return num;
}


