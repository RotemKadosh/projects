#include "../utils/test.h" /* Require, RUNTEST */
#include <stdio.h>/*printf*/
#include "bst.h"

static test_status_t TestOne();
int main()
{
    RUNTEST(TestOne);
    return 0;
}




int inCmp(const void *data, const void *data_to_compare, void *params)
{
    *(int *)params = 0;
    return *(int *)data - *(int *)data_to_compare;
}

int actionprint(const void *data, void *param)
{

    printf("%d\n", *(int *)data);
    return 0;
}

static test_status_t TestOne()
{
    int params = 0;
    int num1 = 1;
    int num2 = -1;
    int num3 = 4;
    int num4 = 2;
    int num5 = 10;
    int num6 = 3;
    int num7 = 6;
    int num8 = 8;
    int num9 = 11;
    int *g = NULL;
    BST_iter_ty iter1;
    BST_iter_ty iter2;
    BST_ty *bst = BSTCreate(inCmp, (void *)&params);
    REQUIRE(NULL != bst);
    REQUIRE(0 == BSTSize(bst));
    REQUIRE(BSTIsEmpty(bst));
    BSTInsert(bst,(void *)&num1);
    REQUIRE(1 == BSTSize(bst));
    REQUIRE(!BSTIsSameIter(BSTBegin(bst), BSTEnd(bst)));
    REQUIRE(!BSTIsEmpty(bst));
    BSTInsert(bst,(void *)&num2);
    REQUIRE(2 == BSTSize(bst));
    BSTInsert(bst,(void *)&num3);
    REQUIRE(3 == BSTSize(bst));
    iter2 = BSTInsert(bst,(void *)&num4);
    REQUIRE(4 == BSTSize(bst));
    BSTInsert(bst,(void *)&num5);
    REQUIRE(5 == BSTSize(bst));
    BSTInsert(bst,(void *)&num6);
    REQUIRE(6 == BSTSize(bst));
    BSTInsert(bst,(void *)&num7);
    REQUIRE(7 == BSTSize(bst));
    BSTInsert(bst,(void *)&num8);
    REQUIRE(8 == BSTSize(bst));
    BSTInsert(bst,(void *)&num9);
    REQUIRE(9 == BSTSize(bst));
    BSTForEach(BSTBegin(bst),BSTEnd(bst),actionprint, NULL);
    iter1 = BSTSearch(bst,(void *)&num4);
    REQUIRE(BSTIsSameIter(iter1,iter2));
    iter1 = BSTSearch(bst,(void *)&params);
    REQUIRE(BSTIsSameIter(iter1,BSTEnd(bst)));

    iter1 = BSTSearch(bst,(void *)&num4);
    REQUIRE(BSTIsSameIter(iter1,iter2));
    g = (int *)BSTGetData(iter1);
    REQUIRE(*g == num4);
    g = BSTRemove(iter1);
    REQUIRE(*g == num4);
    iter2 = BSTBegin(bst);
    REQUIRE(-1 == *(int *)BSTGetData(iter2));
    iter2 = BSTIterNext(iter2);
    REQUIRE(1 == *(int *)BSTGetData(iter2));
    iter2 = BSTIterNext(iter2);
    REQUIRE(3 == *(int *)BSTGetData(iter2));
    iter2 = BSTIterNext(iter2);
    REQUIRE(4 == *(int *)BSTGetData(iter2));
    iter2 = BSTIterNext(iter2);
    REQUIRE(6 == *(int *)BSTGetData(iter2));
    iter2 = BSTIterNext(iter2);
    REQUIRE(8 == *(int *)BSTGetData(iter2));
    iter2 = BSTIterNext(iter2);
    REQUIRE(10 == *(int *)BSTGetData(iter2));
    iter2 = BSTIterNext(iter2);
    REQUIRE(11 == *(int *)BSTGetData(iter2));
    iter2 = BSTIterPrev(iter2);
    REQUIRE(10 == *(int *)BSTGetData(iter2));
    iter2 = BSTIterPrev(iter2);
    REQUIRE(8 == *(int *)BSTGetData(iter2));
    iter2 = BSTIterPrev(iter2);
    REQUIRE(6 == *(int *)BSTGetData(iter2));
    iter2 = BSTIterPrev(iter2);
    REQUIRE(4 == *(int *)BSTGetData(iter2));
    BSTDestroy(bst);
    return PASSED;
}