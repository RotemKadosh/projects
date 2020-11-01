
#ifndef __RECURSION_H__
#define __RECURSION_H__

#include "../../ds/stack/stack.h"

typedef struct node
{
    int data;
    struct node *next;
} node_ty;

int fibonachi(int index);
int Strlen(const char *str);
int StrCmp(const char *str1, const char *str2);
char *Strcpy(char *dest, const char *src);
char *Strcat(char *dest, const char *src);
const char *Strstr( const char *hystack, const char *needle);
node_ty *FlipList(node_ty *node);
stack_t *SortStack(stack_t *stack, size_t size);
#endif /* __RECURSION_H__*/