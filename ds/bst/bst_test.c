#include "../utils/test.h"
#include "bst.h"

#define FALSE (0)
#define TRUE (1)

static test_status_t TestCreate(void);
static test_status_t TestInsertIsEmpty(void);
static test_status_t TestBeginEnd(void);
static test_status_t TestRemoveSearch(void);
static test_status_t TestNextPrev(void);

static test_status_t TestSizeForeach(void);
int Comp(const void *data, const void *data_to_compare, void *params);

int main(void)
{
    RUNTEST(TestCreate);
    RUNTEST(TestInsertIsEmpty);
    RUNTEST(TestBeginEnd);
    RUNTEST(TestRemoveSearch);
    RUNTEST(TestNextPrev);
    RUNTEST(TestSizeForeach);

    return 0;
}

int Comp(const void *data, const void *data_to_compare, void *params)
{
    int int_data = (int)(size_t)data;
    int int_data_to_compare = (int)(size_t)data_to_compare;
    (void)params;

    return int_data - int_data_to_compare;
}

static test_status_t TestCreate(void)
{
    BST_ty *bst = BSTCreate(Comp, NULL);
    REQUIRE(NULL != bst);


    BSTDestroy(bst);
    return PASSED;
}
static test_status_t TestInsertIsEmpty(void)
{
    BST_ty *bst = BSTCreate(Comp, NULL);
    REQUIRE(TRUE == BSTIsEmpty(bst));
    REQUIRE(NULL != BSTInsert(bst, (void *)10));
    REQUIRE(NULL != BSTInsert(bst, (void *)5));
    REQUIRE(NULL != BSTInsert(bst, (void *)3));
    REQUIRE(NULL != BSTInsert(bst, (void *)4));
    REQUIRE(NULL != BSTInsert(bst, (void *)16));
    REQUIRE(NULL != BSTInsert(bst, (void *)14));
    REQUIRE(NULL != BSTInsert(bst, (void *)13));
    REQUIRE(NULL != BSTInsert(bst, (void *)15));
    REQUIRE(NULL != BSTInsert(bst, (void *)30));
    REQUIRE(FALSE == BSTIsEmpty(bst));
    BSTDestroy(bst);
    return PASSED;
}
static test_status_t TestBeginEnd(void)
{
    BST_ty *bst = BSTCreate(Comp, NULL);
    REQUIRE(TRUE == BSTIsEmpty(bst));
    REQUIRE(NULL != BSTInsert(bst, (void *)10));
    REQUIRE(BSTGetData(BSTBegin(bst)) == (void *)10);
    /*REQUIRE(BSTGetData(BSTEnd(bst)) == (void *)0);*/
    REQUIRE(NULL != BSTInsert(bst, (void *)5));
    REQUIRE(BSTGetData(BSTBegin(bst)) == (void *)5);
    REQUIRE(NULL != BSTInsert(bst, (void *)3));
    REQUIRE(BSTGetData(BSTBegin(bst)) == (void *)3);
    REQUIRE(NULL != BSTInsert(bst, (void *)4));
    REQUIRE(BSTGetData(BSTBegin(bst)) == (void *)3);
    REQUIRE(NULL != BSTInsert(bst, (void *)16));
    REQUIRE(BSTGetData(BSTBegin(bst)) == (void *)3);
    REQUIRE(NULL != BSTInsert(bst, (void *)14));
    REQUIRE(BSTGetData(BSTBegin(bst)) == (void *)3);
    REQUIRE(NULL != BSTInsert(bst, (void *)13));
    REQUIRE(BSTGetData(BSTBegin(bst)) == (void *)3);
    REQUIRE(NULL != BSTInsert(bst, (void *)15));
    REQUIRE(BSTGetData(BSTBegin(bst)) == (void *)3);
    REQUIRE(NULL != BSTInsert(bst, (void *)30));
    REQUIRE(BSTGetData(BSTBegin(bst)) == (void *)3);
    REQUIRE(FALSE == BSTIsEmpty(bst));
    BSTDestroy(bst);
    return PASSED;
}

static test_status_t TestRemoveSearch(void)
{
    BST_ty *bst = BSTCreate(Comp, NULL);
    BST_iter_ty iter = {NULL};
    BST_iter_ty iter1 = {NULL};
    BST_iter_ty iter2 = {NULL};
    BST_iter_ty iter3 = {NULL};
    BST_iter_ty iter4 = {NULL};
    BST_iter_ty iter5 = {NULL};
    BST_iter_ty iter6 = {NULL};
    BST_iter_ty iter7 = {NULL};

    REQUIRE(TRUE == BSTIsEmpty(bst));
    iter = BSTInsert(bst, (void *)10);
    REQUIRE((void *)10 == BSTRemove(iter));
    REQUIRE(TRUE == BSTIsEmpty(bst));

    BSTInsert(bst, (void *)5);
    BSTInsert(bst, (void *)3);
    BSTInsert(bst, (void *)4);
    BSTInsert(bst, (void *)16);
    BSTInsert(bst, (void *)14);
    BSTInsert(bst, (void *)13);
    BSTInsert(bst, (void *)15);
    BSTInsert(bst, (void *)30);
    REQUIRE(FALSE == BSTIsEmpty(bst));

    iter4 = BSTSearch(bst, (void *)14);
    REQUIRE((void *)14 == BSTRemove(iter4));
    iter2 = BSTSearch(bst, (void *)4);
    REQUIRE((void *)4 == BSTRemove(iter2));
    iter3 = BSTSearch(bst, (void *)16);
    REQUIRE((void *)16 == BSTRemove(iter3));
    iter5 = BSTSearch(bst, (void *)13);
    REQUIRE((void *)13 == BSTRemove(iter5));
    iter1 = BSTSearch(bst, (void *)3);
    REQUIRE((void *)3 == BSTRemove(iter1));
    iter6 = BSTSearch(bst, (void *)15);
    REQUIRE((void *)15 == BSTRemove(iter6));
    iter = BSTSearch(bst, (void *)5);
    REQUIRE((void *)5 == BSTRemove(iter));
    iter7 = BSTSearch(bst, (void *)30);
    REQUIRE((void *)30 == BSTRemove(iter7));
    REQUIRE(TRUE == BSTIsEmpty(bst));

    BSTDestroy(bst);

    return PASSED;
}

static test_status_t TestNextPrev(void)
{
    BST_ty *bst = BSTCreate(Comp, NULL);
    BST_iter_ty iter = {NULL};

    BSTInsert(bst, (void *)10);
    BSTInsert(bst, (void *)5);
    BSTInsert(bst, (void *)3);
    BSTInsert(bst, (void *)4);
    BSTInsert(bst, (void *)16);
    BSTInsert(bst, (void *)14);
    BSTInsert(bst, (void *)13);
    BSTInsert(bst, (void *)15);
    BSTInsert(bst, (void *)30);

    iter = BSTBegin(bst);
    REQUIRE((void *)3 == BSTGetData(iter));
    
    iter = BSTIterNext(iter);
    REQUIRE((void *)4 == BSTGetData(iter));

    iter = BSTIterNext(iter);
    REQUIRE((void *)5 == BSTGetData(iter));

    iter = BSTIterNext(iter);
    REQUIRE((void *)10 == BSTGetData(iter));

    iter = BSTIterNext(iter);
    REQUIRE((void *)13 == BSTGetData(iter));

    iter = BSTIterNext(iter);
    REQUIRE((void *)14 == BSTGetData(iter));

    iter = BSTIterNext(iter);
    REQUIRE((void *)15 == BSTGetData(iter));

    iter = BSTIterNext(iter);
    REQUIRE((void *)16 == BSTGetData(iter));

    iter = BSTIterNext(iter);
    REQUIRE((void *)30 == BSTGetData(iter));

    iter = BSTIterNext(iter);
    REQUIRE(BSTIsSameIter(iter, BSTEnd(bst)));

    BSTDestroy(bst);

    return PASSED;
}

static test_status_t TestSizeForeach(void)
{
    BST_ty *bst = BSTCreate(Comp, NULL);
    BST_iter_ty iter = {NULL};
    BST_iter_ty iter1 = {NULL};
    BST_iter_ty iter2 = {NULL};
    BST_iter_ty iter3 = {NULL};
    BST_iter_ty iter4 = {NULL};
    BST_iter_ty iter5 = {NULL};
    BST_iter_ty iter6 = {NULL};
    BST_iter_ty iter7 = {NULL};

    REQUIRE(0 == BSTSize(bst));
    BSTInsert(bst, (void *)10);
    REQUIRE(1 == BSTSize(bst));
    BSTInsert(bst, (void *)5);
    REQUIRE(2 == BSTSize(bst));
    BSTInsert(bst, (void *)3);
    REQUIRE(3 == BSTSize(bst));
    BSTInsert(bst, (void *)4);
    REQUIRE(4 == BSTSize(bst));
    BSTInsert(bst, (void *)16);
    REQUIRE(5 == BSTSize(bst));
    BSTInsert(bst, (void *)14);
    BSTInsert(bst, (void *)13);
    BSTInsert(bst, (void *)15);
    BSTInsert(bst, (void *)30);
    REQUIRE(9 == BSTSize(bst));


    iter = BSTSearch(bst, (void *)10);
    REQUIRE((void *)10 == BSTRemove(iter));
    iter4 = BSTSearch(bst, (void *)14);
    REQUIRE((void *)14 == BSTRemove(iter4));
    iter2 = BSTSearch(bst, (void *)4);
    REQUIRE((void *)4 == BSTRemove(iter2));
    iter3 = BSTSearch(bst, (void *)16);
    REQUIRE((void *)16 == BSTRemove(iter3));
    iter5 = BSTSearch(bst, (void *)13);
    REQUIRE((void *)13 == BSTRemove(iter5));
    iter1 = BSTSearch(bst, (void *)3);
    REQUIRE((void *)3 == BSTRemove(iter1));
    iter6 = BSTSearch(bst, (void *)15);
    REQUIRE((void *)15 == BSTRemove(iter6));

    iter = BSTSearch(bst, (void *)5);
    REQUIRE((void *)5 == BSTRemove(iter));
    iter7 = BSTSearch(bst, (void *)30);
    REQUIRE((void *)30 == BSTRemove(iter7));
    BSTDestroy(bst);
    return PASSED;
}