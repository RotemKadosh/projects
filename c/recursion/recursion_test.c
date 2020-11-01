#include "../../ds/utils/test.h"
#include "../../ds/stack/stack.h"
#include "recursion.h"
#include <string.h>
#include <stdio.h> 
#include <stdlib.h>



static test_status_t TestFib(void);
static test_status_t TestStrlen(void);
static test_status_t TestStrCmp(void);
static test_status_t TestStrcpy(void);
static test_status_t TestStrcat(void);
static test_status_t TestStrstr(void);
static test_status_t TestFlipList(void);
static test_status_t TestSortStack(void);
static test_status_t TestOverFlow(void);
int infrec(int count);
int main()
{
    RUNTEST(TestFib);
    RUNTEST(TestStrlen);
    RUNTEST(TestStrCmp);
    RUNTEST(TestStrcpy);
    RUNTEST(TestStrcat);
    RUNTEST(TestStrstr);
    RUNTEST(TestFlipList);
    RUNTEST(TestSortStack);
    RUNTEST(TestOverFlow);
    return 0;
    
}

static test_status_t TestFib(void)
{
    REQUIRE(21 == fibonachi(9));
    REQUIRE(13 == fibonachi(8));
    REQUIRE(8 == fibonachi(7));
    REQUIRE(5 == fibonachi(6));
    REQUIRE(3 == fibonachi(5));

    return PASSED;
}

static test_status_t TestStrlen(void)
{
    REQUIRE(strlen("absc") == Strlen("absc"));
    REQUIRE(strlen("1234567891012") == Strlen("1234567891012"));
    REQUIRE(strlen("12345678") == Strlen("12345678"));
    REQUIRE(strlen("12345") == Strlen("12345"));
    REQUIRE(strlen("123") == Strlen("123"));

    return PASSED;
}

static test_status_t TestStrCmp(void)
{
    REQUIRE(strcmp("absc", "absc") == StrCmp("absc", "absc"));
    REQUIRE(strcmp("1234567891012", "12212") == StrCmp("1234567891012", "12212"));
    REQUIRE(strcmp("12345678", " 12345678") == StrCmp("12345678", " 12345678"));
    REQUIRE(strcmp("12345678", "12345678") == StrCmp("12345678", "12345678"));
    REQUIRE(strcmp("12345678", "") == StrCmp("12345678", ""));

    return PASSED;
}

static test_status_t TestStrcpy(void)
{
    char dest[6] = {0};
    const char *src = "hello";
    Strcpy(dest, src); 
    REQUIRE(strcmp(dest, src) == 0);
    return PASSED;
}

static test_status_t TestStrcat(void)
{
    char dest1[13] = "hello\0";
    char dest2[13] = "hello\0";
    const char *src = "hello";
    
    
    REQUIRE(strcmp(Strcat(dest1, src) , strcat(dest2, src) ) == 0);
    return PASSED;
}

static test_status_t TestStrstr(void)
{
    const char *haystack1 = "Hellohel";
    const char *needle1 = "hel";
    const char *haystack2 = "hellohel";
    const char *needle2 = "hel";
    const char *haystack3 = "hellohel";
    const char *needle3 = "heh";
    const char *haystack4 = "";
    const char *needle4 = "";

    REQUIRE(0 == strcmp(strstr(haystack1,needle1), Strstr(haystack1,needle1)));
    REQUIRE(0 == strcmp(strstr(haystack2, needle2), Strstr(haystack2, needle2)));
    REQUIRE(NULL ==  Strstr(haystack3, needle3));
    REQUIRE(haystack4 == Strstr(haystack4, needle4));

    return PASSED;
}

static test_status_t TestFlipList(void)
{
    node_ty *head_ref = NULL;
    node_ty *node1 = (node_ty*)malloc(sizeof(node_ty));
    node_ty *node2 = (node_ty*)malloc(sizeof(node_ty));
    node_ty *node3 = (node_ty*)malloc(sizeof(node_ty));
    node_ty *node4 = (node_ty*)malloc(sizeof(node_ty));
    node_ty *node5 = (node_ty*)malloc(sizeof(node_ty));

    node1->data = 1;
    node2->data = 2;
    node3->data = 3;
    node4->data = 4;
    node5->data = 5;

    node1->next = node2;
    node2->next = node3;
    node3->next= node4;
    node4->next = node5;
    node5->next = NULL;

    head_ref = FlipList(node1);
    REQUIRE(head_ref->data == 5);
    head_ref = head_ref->next;
    REQUIRE(head_ref->data == 4);
    head_ref = head_ref->next;
    REQUIRE(head_ref->data == 3);
    head_ref = head_ref->next;
    REQUIRE(head_ref->data == 2);
    head_ref = head_ref->next;
    REQUIRE(head_ref->data == 1);
    free(node1);
    free(node2);
    free(node3);
    free(node4);
    free(node5);


    return PASSED;
}

static test_status_t TestSortStack(void)
{
    int num1 = 1;
    int num2 = 6;
    int num3 = 5;
    int num4 = 2;
    int num5 = 4;
    int num6 = 3;
    int num11 =0;
    int num12 =0;
    int num13 =0;
    int num14 =0;
    int num15 =0;
    int num16 =0;
    stack_t *stack = StackCreate(6);
    StackPush(stack, (void *)&num1);
    StackPush(stack, (void *)&num2);
    StackPush(stack, (void *)&num3);
    StackPush(stack, (void *)&num4);
    StackPush(stack, (void *)&num5);
    StackPush(stack, (void *)&num6);
    SortStack(stack, 6);
    num11 = *(int *)StackPeek(stack);
    StackPop(stack);
    num12 = *(int *)StackPeek(stack);
    StackPop(stack);
    num13 = *(int *)StackPeek(stack);
    StackPop(stack);
    num14 = *(int *)StackPeek(stack);
    StackPop(stack);
    num15 = *(int *)StackPeek(stack);
    StackPop(stack);
    num16 = *(int *)StackPeek(stack);
    StackPop(stack);
    
    REQUIRE(num11 == 1);
    REQUIRE(num12 == 2);
    REQUIRE(num13 == 3);
    REQUIRE(num14 == 4);
    REQUIRE(num15 == 5);
    REQUIRE(num16 == 6);
    StackDestroy(stack);
    return PASSED;
}

static test_status_t TestOverFlow(void)
{
    static int count = 1;
    infrec(count);
    return PASSED;
}

int infrec(int count)
{
     printf("%d\n" ,count++);
     return infrec(count);
}