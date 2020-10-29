#include <stdlib.h> /*malloc free*/
#include "rbst.h"

#define MAX(a,b) (a > b) ? a : b

enum raltives
{
    PARENT, LEFT ,RIGHT, NUM_OF_RELATIVES
};
struct tree_node
{
    void *data;
    struct tree_node *relatives [NUM_OF_RELATIVES];
};

struct rec_self_balanced_binary_search_tree
{
    RBST_cmp_func_ty compare;
    void *params;
    rbst_node_ty dummy_root;
};
/*----------------declerations-------------------------------------------*/

/*--------------------SERVIC---------------------------*/

static RBST_iter_ty RBSTSearchRecurcive(RBST_ty *tree, RBST_iter_ty root , void *data_to_match);

static RBST_iter_ty RBSTInsertRecurcive(RBST_ty *tree, RBST_iter_ty root , rbst_node_ty *node_to_insert);

static RBST_iter_ty GetRoot(const RBST_ty *tree);

static size_t RBSTSizeRec(RBST_iter_ty root);

static size_t RBSTHightRec(RBST_iter_ty root);
/*------------------definitions-----------------------------------------------*/

/*--------------------SERVIC---------------------------*/

static RBST_iter_ty RBSTSearchRecurcive(RBST_ty *tree, RBST_iter_ty root , void *data_to_match)
{
    int cmp_ret = 0;
    if(NULL == root)
    {
        return NULL;
    }

    cmp_ret = tree->compare(data_to_match, RBSTGetData(root), tree->params);
    
    if(0 == cmp_ret)
    {
        return root;   
    }
    else if(cmp_ret < 0)
    {   
        return RBSTSearchRecurcive(tree,root->relatives[LEFT], data_to_match);  
    } 
    else if (cmp_ret > 0)
    {
        return RBSTSearchRecurcive(tree, root->relatives[RIGHT], data_to_match);
        
    }
}

static RBST_iter_ty RBSTInsertRecurcive(RBST_ty *tree, RBST_iter_ty root , rbst_node_ty *node_to_insert)
{
    int cmp_ret = 0;
    assert(NULL != root);
    assert(NULL != tree);

    cmp_ret = tree->compare(RBSTGetData((RBST_iter_ty)node_to_insert), RBSTGetData(root), tree->params);
    
    assert(0 != cmp_ret);

    if(cmp_ret > 0)
    {
        if(root->relatives[RIGHT] == NULL)
        {
            ConnectNodes(root->relatives[RIGHT],(RBST_iter_ty) node_to_insert);
            return (RBST_iter_ty) node_to_insert;
        }
        return RBSTInsertRecurcive(tree, root->relatives[RIGHT], node_to_insert);    
    }
    else if(cmp_ret < 0)
    {   
        if(root->relatives[LEFT] == NULL)
        {
            ConnectNodes(root->relatives[LEFT],(RBST_iter_ty) node_to_insert);
            return (RBST_iter_ty) node_to_insert;
        }
        return RBSTInsertRecurcive(tree,root->relatives[LEFT], node_to_insert);  
    } 
}

static RBST_iter_ty GetRoot(const RBST_ty *tree)
{
    assert(NULL != tree);
    return tree->dummy_root.relatives[LEFT];
}

static RBST_iter_ty RTraversSide(RBST_iter_ty iter, int side)
{
    if(NULL == iter->relatives[side])
    {
        return iter;
    }
    return RTraversSide(iter->relatives[side], side);

}

static size_t RBSTSizeRec(RBST_iter_ty root)
{
    RBST_iter_ty left = NULL;
    RBST_iter_ty right = NULL;
    size_t count = 0;
    assert(NULL != root);

    left = root->relatives[LEFT];
    right = root->relatives[RIGHT];

    if(NULL == left && NULL == right)
    {
        return 1;
    }
    else if (NULL == left)
    {
        return 1 + RBSTSizeRec(right);
    }
    else if (NULL == right)
    {
        return 1 + RBSTSizeRec(left);
    }
    return 1 + RBSTSizeRec(left) + RBSTSizeRec(right);
}

static size_t RBSTHightRec(RBST_iter_ty root)
{
    RBST_iter_ty left = NULL;
    RBST_iter_ty right = NULL;
    size_t count = 0;
    assert(NULL != root);

    left = root->relatives[LEFT];
    right = root->relatives[RIGHT];

    if(NULL == left && NULL == right)
    {
        return 1;
    }
    else if (NULL == left)
    {
        return 1 + RBSTSizeRec(right);
    }
    else if (NULL == right)
    {
        return 1 + RBSTSizeRec(left);
    }
    return 1 +MAX(RBSTSizeRec(left), RBSTSizeRec(right));
}

void RBSTDestroyRec(RBST_iter_ty root)
{
    RBST_iter_ty left = NULL;
    RBST_iter_ty right = NULL;
    
    assert(NULL != root);

    left = root->relatives[LEFT];
    right = root->relatives[RIGHT];

    DestroyNode(root);

    if (NULL != left)
    {
        root->relatives[LEFT] = NULL;
        RBSTDestroyRec(left);
        
    }
    if (NULL != right)
    {
        root->relatives[RIGHT] = NULL;
        RBSTDestroyRec(right);
    }
}


/*--------------------API---------------------------*/
RBST_ty *RBSTCreate(RBST_cmp_func_ty compare, void *params)
{
    RBST_ty *bst = malloc(sizeof(RBST_ty));
    if(NULL != bst)
    { 
        bst->compare = compare;
        bst->params = params;
        bst->dummy_root.relatives[PARENT] = NULL; 
        bst->dummy_root.relatives[LEFT] = NULL; 
        bst->dummy_root.relatives[RIGHT] = NULL; 
    }
    return bst;
}

RBST_iter_ty RBSTFind(RBST_ty *tree,  void *data_to_match)
{
    RBST_iter_ty iter = NULL;
    RBST_iter_ty ans = NULL;

    assert(tree != NULL);

    iter = GetRoot(tree);

    ans = RBSTSearchRecurcive(tree, iter, data_to_match);
    if(NULL == ans)
    {
        ans = RBSTEnd(tree);
    }
    return ans;      
}

int RBSTIsEmpty(const RBST_ty *tree)
{
    assert(NULL != tree);
    return (NULL == GetRoot(tree));
}

RBST_iter_ty RBSTInsert(RBST_ty *tree, void *data)
{
    rbst_node_ty *node_to_insert = NULL;
    RBST_iter_ty root = NULL;
    RBST_iter_ty ans = NULL;

    assert(tree != NULL);

    root = GetRoot(tree);

    node_to_insert = CreatNode(data_to_match);
    if(NULL == node_to_insert)
    {
       return RBSTEnd(tree); 
    }

    ans = RBSTInsertRecurcive(tree, root, node_to_insert);
    return ans;

}

RBST_iter_ty RBSTBegin(const RBST_ty *tree)
{
    RBST_iter_ty node_runner = NULL;

    assert(NULL != tree);

    node_runner = BSTEnd(tree);
    node_runner = RTraversSide(node_runner, LEFT);
    return node_runner;
}

RBST_iter_ty RBSTEnd(const RBST_ty *tree)
{
    assert(tree);
    return (const RBST_iter_ty)&tree->dummy_root;
}

void *RBSTGetData(RBST_iter_ty iter)
{
    assert(NULL != iter);
    return iter->data;
}

size_t RBSTSize(const RBST_ty *tree)
{
    
    RBST_iter_ty root = NULL;

    assert(NULL != tree);
  
    root = GetRoot(tree);
    return RBSTSizeRec(root);
}

size_t RBSTHight(const RBST_ty *tree)
{
    RBST_iter_ty root = NULL;

    assert(NULL != tree);
  
    root = GetRoot(tree);
    return RBSTHightRec(root);
}

void RBSTDestroy(RBST_ty *tree)
{
    RBST_iter_ty root = NULL;

    assert(NULL != tree);
  
    root = GetRoot(tree);
    RBSTDestroyRec(root);
}

int RBSTIsSameIter(RBST_iter_ty iter1, RBST_iter_ty iter2)
{
    return(iter1 == iter2);
}

void *RBSTRemove(RBST_iter_ty iter)
{
        void *data_to_return = NULL;
        RBST_iter_ty next = NULL;
        int is_iter_left_chiled = IsNodeLeftChiled
        assert(NULL != iter);

        data_to_return = RBSTGetData(iter);

        if(NULL == iter->relatives[LEFT] && NULL == iter->relatives[RIGHT])
        {
            DestroyNode(iter);

        }
        else if(NULL == iter->relatives[LEFT] && NULL != iter->relatives[RIGHT])
        {
            next = RTraversSide(iter->relatives[RIGHT], LEFT);
            ConnectNodes(iter->relatives[PARENT], next);
            DestroyNode
        }
}















