#include "../utils/test.h"
#include <stdio.h>
#include "avl.h"

#define FALSE (0)
#define TRUE (1)
#define SUCCESS (1)

static test_status_t TestCreate(void);
static test_status_t TestInsertIsEmpty(void);
static test_status_t TestSizeHight(void);
static test_status_t TestForeach(void);
static test_status_t TestRemoveFind(void);
static test_status_t TestBalancInsert(void);
static test_status_t TestBalanceRemove(void);

int Comp(const void *data, const void *data_to_compare);

int main(void)
{
    RUNTEST(TestCreate);

    RUNTEST(TestInsertIsEmpty);
    RUNTEST(TestSizeHight); 
    RUNTEST(TestForeach);      
    RUNTEST(TestRemoveFind);    
    RUNTEST(TestBalancInsert);
    RUNTEST(TestBalanceRemove);
    return 0;
}

int Comp(const void *data, const void *data_to_compare)
{
    int int_data = (int)(size_t)data;
    int int_data_to_compare = (int)(size_t)data_to_compare;

    return int_data - int_data_to_compare;
}

int AVLPrintNodeData(const void *data, void *param)
{
    (void)param;
    printf("node data =  %d\n", *(int *)&data);
    return 0;
}

static test_status_t TestCreate(void)
{
    AVL_ty *avl = AVLCreate(Comp);
    REQUIRE(NULL != avl);

    AVLDestroy(avl);
    return PASSED;
}

static test_status_t TestInsertIsEmpty(void)
{
    size_t i = 0;
    AVL_ty *avl = AVLCreate(Comp);
    REQUIRE(TRUE == AVLIsEmpty(avl));
    for(i = 0; i < 10000; i += 4)
    {
        REQUIRE(SUCCESS == AVLInsert(avl, (void *)(i - 3)));
        REQUIRE(SUCCESS == AVLInsert(avl, (void *)i));
        REQUIRE(SUCCESS == AVLInsert(avl, (void *)(i + 3)));
    }
    REQUIRE(FALSE == AVLIsEmpty(avl));
    AVLDestroy(avl);
    return PASSED;
}

static test_status_t TestSizeHight(void)
{
    AVL_ty *avl = AVLCreate(Comp);
    REQUIRE(0 == AVLSize(avl));
    
    AVLInsert(avl, (void *)10);
    REQUIRE(1 == AVLSize(avl));
    REQUIRE(0 == AVLHeight(avl));
    AVLInsert(avl, (void *)5);
    REQUIRE(2 == AVLSize(avl));
    REQUIRE(1 == AVLHeight(avl));
    AVLInsert(avl, (void *)3);
    REQUIRE(3 == AVLSize(avl));
    REQUIRE(2 == AVLHeight(avl));
    AVLInsert(avl, (void *)4);
    REQUIRE(4 == AVLSize(avl));
    REQUIRE(3 == AVLHeight(avl));
    AVLInsert(avl, (void *)16);
    REQUIRE(3 == AVLHeight(avl));
    REQUIRE(5 == AVLSize(avl));
    AVLInsert(avl, (void *)14);
    REQUIRE(3 == AVLHeight(avl));
    REQUIRE(6 == AVLSize(avl));
    AVLInsert(avl, (void *)13);
    REQUIRE(3 == AVLHeight(avl));
    REQUIRE(7 == AVLSize(avl));
    AVLInsert(avl, (void *)15);
    REQUIRE(3 == AVLHeight(avl));
    REQUIRE(8 == AVLSize(avl));
    AVLInsert(avl, (void *)18);
    REQUIRE(3 == AVLHeight(avl));
    REQUIRE(9 == AVLSize(avl));
    AVLInsert(avl, (void *)-15);
    REQUIRE(3 == AVLHeight(avl));
    REQUIRE(10 == AVLSize(avl));
    AVLInsert(avl, (void *)12);
    REQUIRE(11 == AVLSize(avl));
   
    AVLDestroy(avl);
    return PASSED;
}

static test_status_t TestRemoveFind()
{

    AVL_ty *tree = AVLCreate(Comp);
    REQUIRE(tree != NULL);
    REQUIRE(SUCCESS == AVLInsert(tree, (void *)10));
    REQUIRE(SUCCESS == AVLInsert(tree, (void *)6));
    REQUIRE(SUCCESS == AVLInsert(tree, (void *)15));
    REQUIRE(SUCCESS == AVLInsert(tree, (void *)8));
    REQUIRE(SUCCESS == AVLInsert(tree, (void *)4));
    REQUIRE(SUCCESS == AVLInsert(tree, (void *)12));
    REQUIRE(SUCCESS == AVLInsert(tree, (void *)17));
    REQUIRE(SUCCESS == AVLInsert(tree, (void *)11));
    REQUIRE(8 == AVLSize(tree));

    REQUIRE((void *)12 == AVLFind(tree, (void *)12));
    AVLRemove(tree ,(void *)12);
    REQUIRE(7 == AVLSize(tree));
    REQUIRE((void *)10 == AVLFind(tree, (void *)10));
    AVLRemove(tree, (void *)10);
    REQUIRE(6 == AVLSize(tree));
    REQUIRE((void *)17 == AVLFind(tree, (void *)17));
    AVLRemove(tree, (void *)17);
    REQUIRE(5 == AVLSize(tree));
    REQUIRE(NULL == AVLFind(tree, (void *)17));
  
    AVLDestroy(tree);
    tree = NULL;

    return PASSED;
}

static test_status_t TestForeach(void)
{
    int i = 0;
    AVL_ty *avl = AVLCreate(Comp);
    REQUIRE(TRUE == AVLIsEmpty(avl));
    for(i = 0; i < 10; i += 4)
    {
        REQUIRE(SUCCESS == AVLInsert(avl, (void *)((size_t)i - 3)));
        REQUIRE(SUCCESS == AVLInsert(avl, (void *)(size_t)i));
        REQUIRE(SUCCESS == AVLInsert(avl, (void *)((size_t)i + 3)));
    }
     for(i = -1; i > -10; i -= 4)
    {
        REQUIRE(SUCCESS == AVLInsert(avl, (void *)((size_t)i - 3)));
        REQUIRE(SUCCESS == AVLInsert(avl, (void *)(size_t)i));
        REQUIRE(SUCCESS == AVLInsert(avl, (void *)((size_t)i + 3)));
    }
    REQUIRE(FALSE == AVLIsEmpty(avl));
    AVLForEach(avl, AVLPrintNodeData, NULL, 1);
    AVLForEach(avl, AVLPrintNodeData, NULL, 2);
    AVLForEach(avl, AVLPrintNodeData, NULL, 3);

    AVLDestroy(avl);
    return PASSED;
}

static test_status_t TestBalancInsert(void)
{
    AVL_ty *avl = AVLCreate(Comp);
    size_t i = 0;
    REQUIRE(TRUE == AVLIsEmpty(avl));
    for(i = 0; i < 10000; i += 4)
    {
        REQUIRE(SUCCESS == AVLInsertBalance(avl, (void *)(i - 3)));
        REQUIRE(SUCCESS == AVLInsertBalance(avl, (void *)i));
        REQUIRE(SUCCESS == AVLInsertBalance(avl, (void *)(i + 3)));
    }
    
    AVLDestroy(avl);

    return PASSED;
}

static test_status_t TestBalanceRemove(void)
{  
    AVL_ty *avl = AVLCreate(Comp);
    REQUIRE(avl != NULL);
    REQUIRE(SUCCESS == AVLInsertBalance(avl, (void *)10));
    REQUIRE(SUCCESS == AVLInsertBalance(avl, (void *)6));
    REQUIRE(SUCCESS == AVLInsertBalance(avl, (void *)15));
    REQUIRE(SUCCESS == AVLInsertBalance(avl, (void *)8));
    REQUIRE(SUCCESS == AVLInsertBalance(avl, (void *)4));
    REQUIRE(SUCCESS == AVLInsertBalance(avl, (void *)12));
    REQUIRE(SUCCESS == AVLInsertBalance(avl, (void *)17));
    REQUIRE(SUCCESS == AVLInsertBalance(avl, (void *)11));
    REQUIRE(8 == AVLSize(avl));

    print2D(avl);
    printf("---------------------------------------\n");
    REQUIRE((void *)12 == AVLFind(avl, (void *)12));
    AVLRemoveBalanc(avl ,(void *)12);
    REQUIRE(7 == AVLSize(avl));
    print2D(avl);
    printf("---------------------------------------\n");
    REQUIRE((void *)10 == AVLFind(avl, (void *)10));
    AVLRemoveBalanc(avl, (void *)10);  
    print2D(avl);
    printf("---------------------------------------\n");
    REQUIRE(6 == AVLSize(avl));
    REQUIRE((void *)17 == AVLFind(avl, (void *)17));
    AVLRemoveBalanc(avl, (void *)17);
    REQUIRE(5 == AVLSize(avl));
    print2D(avl);
    printf("---------------------------------------\n");
    REQUIRE((void *)11 == AVLFind(avl, (void *)11));
    AVLRemoveBalanc(avl, (void *)11);
    REQUIRE(4 == AVLSize(avl));
    print2D(avl);
    printf("---------------------------------------\n");
  
    AVLDestroy(avl);
    avl = NULL;

    return PASSED;
}














