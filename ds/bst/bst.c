#include <stdlib.h>/*malloc free*/
#include <assert.h>/*assert*/
#include "bst.h"

#define TRUE (1)
#define FALSE (1)
#define DEFAULT_LEFT_CHILED (-1)
#define LEFT_C (-1)
#define RIGHT_C (1)

enum raltives
{
    PARENT, LEFT ,RIGHT, NUM_OF_RELATIVES
};
struct tree_node
{
    void *data;
    struct tree_node *relatives [NUM_OF_RELATIVES];
};

struct r_binary_search_tree
{
    BST_cmp_func_ty compare;
    void *params;
    bst_node_ty dummy_root;
};

/*----------service ---------------------*/
static int IsIterLeftChiled(BST_iter_ty iter);
static BST_iter_ty GetRoot(const BST_ty *tree)
{
    assert(NULL != tree);
    return tree->dummy_root.relatives[LEFT];
}

static void ConnectNodes(bst_node_ty *parent, bst_node_ty *chiled, int cmp_ret)
{
    assert(NULL != chiled);
    assert(NULL != parent);

    chiled->relatives[PARENT] = parent;
    if(cmp_ret < 0)
    {
        parent->relatives[LEFT] = chiled;
    }
    else
    {
        parent->relatives[RIGHT] = chiled;
    }
}

static void InitChildrens(void *relatives[])
{
    /* init all childrens - no metter the amount of childrens*/
    int i = 1;
    for(i = 1; i < NUM_OF_RELATIVES; i++)
    {
        relatives[i] = NULL;
    }
}

static bst_node_ty *CreateBstNode(void *data)
{
    bst_node_ty *new_node = malloc(sizeof(bst_node_ty));
    if(NULL != new_node)
    {
        new_node->data = data;
        InitChildrens((void **)new_node->relatives);
    }

    return new_node;
}

static int CountChildrens(const BST_iter_ty iter)
{
    int i = 1;
    int count = 0;
    for(i = 1; i < NUM_OF_RELATIVES; ++i)
    {
        if(NULL != iter->relatives[i])
        {
            ++count;
        }
    }
    return count;
}

static void RemoveOneChildNode(BST_iter_ty iter, int left_chiled_flag)
{
    if(NULL == iter->relatives[LEFT])
    {
        if(left_chiled_flag)
        {
            ConnectNodes(iter->relatives[PARENT],iter->relatives[RIGHT], LEFT_C);
        }
        else
        {
            ConnectNodes(iter->relatives[PARENT],iter->relatives[RIGHT], RIGHT_C);
        }
    }
    else
    {
         if(left_chiled_flag)
        {
            ConnectNodes(iter->relatives[PARENT],iter->relatives[LEFT], LEFT_C);
        }
        else
        {
            ConnectNodes(iter->relatives[PARENT],iter->relatives[LEFT], RIGHT_C);
        }
    }
    
}

static void RemoveTwoChildrenNode(BST_iter_ty iter, int left_chiled_flag)
{
    BST_iter_ty next_node = BSTIterNext(iter);
    int side = (left_chiled_flag) ? LEFT_C : RIGHT_C;

    ConnectNodes(next_node, iter->relatives[LEFT], LEFT_C);
    ConnectNodes(iter->relatives[PARENT], iter->relatives[RIGHT], side);
}

static void *DestroyNode(bst_node_ty *node)
{
    void *data = node->data;
    free(node);
    node = NULL;
    return data;
}

static int IsIterLeftChiled(BST_iter_ty iter)
{
    return BSTIsSameIter(iter, iter->relatives[PARENT]->relatives[LEFT]);
}

static BST_iter_ty TraversSide(BST_iter_ty iter, int side)
{
    while(NULL != iter->relatives[side])
    {
        iter = iter->relatives[side]; 
    }
    return iter;
}

static void ConnectNoChildrenNode(BST_iter_ty iter, int left_chiled_flag)
{
       if(left_chiled_flag)
        {
            iter->relatives[PARENT]->relatives[LEFT] = NULL;
        }
        else
        {
            iter->relatives[PARENT]->relatives[RIGHT] = NULL;
        }
}
/*---------------API------------------------------*/

BST_ty *BSTCreate(BST_cmp_func_ty compare, void *params)
{
    BST_ty *bst = malloc(sizeof(BST_ty));
    if(NULL != bst)
    { 
        bst->compare = compare;
        bst->params = params;
        InitChildrens((void **)bst->dummy_root.relatives);
        bst->dummy_root.relatives[PARENT] = NULL; 
    }
    return bst;
}

BST_iter_ty BSTIterNext(BST_iter_ty iter)
{
    assert(NULL != iter);

    if(NULL != iter->relatives[RIGHT])
    {
        iter = iter->relatives[RIGHT];
        iter = TraversSide(iter, LEFT); 
    }
    else
    {
        while(!IsIterLeftChiled(iter))
        {
            iter = iter->relatives[PARENT]; 
        }
        iter = iter->relatives[PARENT]; 
    }
    return iter;
   
}

BST_iter_ty BSTIterPrev(BST_iter_ty iter)
{
    assert(NULL != iter);

    if(NULL != iter->relatives[LEFT])
    {
        iter = iter->relatives[LEFT];
        iter = TraversSide(iter, RIGHT); 
    }
    else
    {
        while ((IsIterLeftChiled(iter)))
        {
            iter = iter->relatives[PARENT]; 
        }
        iter = iter->relatives[PARENT]; 
    }
    return iter;
}

int BSTIsSameIter(BST_iter_ty iter1, BST_iter_ty iter2)
{
    return(iter1 == iter2);
}

BST_iter_ty BSTBegin(const BST_ty *tree)
{   
    BST_iter_ty node_runner = NULL;
    assert(NULL != tree);
    node_runner = BSTEnd(tree);
    node_runner = TraversSide(node_runner, LEFT);
    return node_runner;
}

int BSTForEach(BST_iter_ty from, BST_iter_ty to, BST_action_func_ty operation, void  *param)
{
    int res = 0;
    BST_iter_ty runner = from;
    assert(NULL != from);
    while(!BSTIsSameIter(runner, to) && res == 0)
    {
        res = operation(BSTGetData(runner), param);
        runner = BSTIterNext(runner);
    }
    return res;
}

size_t BSTSize(const BST_ty *tree)
{
    BST_iter_ty iter = NULL;
    BST_iter_ty end = NULL;
    size_t count = 0;

    assert(NULL != tree);

    end = BSTEnd(tree);
    iter = BSTBegin(tree);

    while (!BSTIsSameIter(iter, end))
    {
        ++count;
        iter = BSTIterNext(iter);
    }
    return count;
}

void *BSTGetData(BST_iter_ty iter)
{
    assert(NULL != iter);
    return iter->data;
}

int BSTIsEmpty(const BST_ty *tree)
{
    assert(NULL != tree);
    return (NULL == GetRoot(tree));
}

BST_iter_ty BSTInsert(BST_ty *tree, void *data)
{
    BST_iter_ty iter = NULL;
    BST_iter_ty iter_prev = NULL;
    bst_node_ty *new_node = NULL;
    int cmp_ret = DEFAULT_LEFT_CHILED;
    assert(NULL != tree);
    assert(NULL != data);
    iter = GetRoot(tree);
    iter_prev = &tree->dummy_root;
    new_node = CreateBstNode(data);
    if(NULL == new_node)
    {
        return BSTEnd(tree);
    }
    while(NULL != iter)
    {
        cmp_ret = tree->compare(data, BSTGetData(iter), tree->params);
        assert(cmp_ret != 0);
        iter_prev = iter;
        if(cmp_ret > 0)
        {
            iter = iter->relatives[RIGHT];  
        }
        else if(cmp_ret < 0)
        {   
            iter = iter->relatives[LEFT];  
        }
    }
    ConnectNodes(iter_prev, new_node, cmp_ret);
    return (BST_iter_ty)new_node;
}

BST_iter_ty BSTSearch(BST_ty *tree, void *data_to_match)
{
    BST_iter_ty iter = GetRoot(tree);
    int cmp_ret = 1;

    assert(NULL != tree);
    assert(NULL != data_to_match);
    
    while(NULL != iter)
    {
        cmp_ret = tree->compare(data_to_match, BSTGetData(iter), tree->params);
        if(cmp_ret > 0)
        {
            iter = iter->relatives[RIGHT];    
        }
        else if(cmp_ret < 0)
        {   
            iter = iter->relatives[LEFT];  
        } 
        else if (0 == cmp_ret)
        {
            return iter;
        }
         
    }
    return BSTEnd(tree);
}

void *BSTRemove(BST_iter_ty iter)
{
    int left_chiled_flag = 0;
    assert(NULL != iter);
    left_chiled_flag = IsIterLeftChiled(iter);

    switch (CountChildrens(iter))
    {
    case 0:
        ConnectNoChildrenNode(iter, left_chiled_flag);
        break;
    case 1:
        RemoveOneChildNode(iter, left_chiled_flag);
        break;
    default:
        RemoveTwoChildrenNode(iter, left_chiled_flag);
        break;
    }
    return DestroyNode(iter);
    
}

void BSTDestroy(BST_ty *tree)
{
    BST_iter_ty root = NULL;
    BST_iter_ty left = NULL;
    BST_iter_ty right = NULL;
    assert (NULL != tree);
    root = GetRoot(tree);
    
    while(NULL != root)
    {
        left = root->relatives[LEFT];
        if(NULL == left)
        {
            right = root->relatives[RIGHT];
            DestroyNode(root);
            root = right;
        }
        else
        {
            {
                root->relatives[LEFT] = left->relatives[RIGHT];
                left->relatives[RIGHT] = root;
                root = left;
            }
        }
        
    }
    free(tree);
    tree = NULL;
}

BST_iter_ty BSTEnd(const BST_ty *tree)
{
    assert(tree);
    return (const BST_iter_ty)&tree->dummy_root;
}