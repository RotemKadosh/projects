#include <stdlib.h> /*malloc free*/
#include <assert.h> /*assert*/
#include <stdio.h>
#include "avl.h"

#define MAX(a,b) ( (a) >= (b)) ? (a) : (b)
#define FAIL (0)
#define SUCCESS (1)
#define NON_ZERO (1)
#define TRUE (1)
#define FALSE (0)
/*------------------Structs & typedefs-----------------------------------------------*/
typedef enum relatives
{
    LEFT, RIGHT, NUM_OF_RELATIVES
} relatives;

struct rec_self_balanced_binary_search_tree
{
    AVL_cmp_func_ty compare;
    struct tree_node *root;
}; 

struct tree_node
{
    void *data;
    struct tree_node *relatives[NUM_OF_RELATIVES];
    size_t height; /* not for first phase */
};

typedef AVL_node_ty *(*remove_func_ty)(AVL_ty *tree, AVL_node_ty *root);

/*----------------declerations-------------------------------------------*/

/*--------------------SERVIC---------------------------*/
static AVL_node_ty *CreateNode(void *data);
static size_t AVLHightRec(AVL_node_ty *root);                                   /*recusive calc of height*/
static size_t AVLSizeRec(AVL_node_ty *root);                                    /*recusive calc of size*/
static int AVLInsertRecurcive(AVL_ty *tree, AVL_node_ty *root , AVL_node_ty *node_to_insert);
static void *AVLSearchRecurcive(AVL_ty *tree, AVL_node_ty *root , void *data_to_match);
static void AVLDestroyRec(AVL_node_ty *root);
static int PostOrderForEach(AVL_node_ty *root, AVL_action_func_ty operation, void *param );
static int InOrderForEach(AVL_node_ty *root, AVL_action_func_ty operation, void *param );
static int PreOrderForEach(AVL_node_ty *root, AVL_action_func_ty operation, void *param );
static void *DestroyNode(AVL_node_ty *node);
static void RemoveRoot(AVL_ty *tree);
static void RemoveNode(AVL_node_ty *parent, int side);
static AVL_node_ty *Next(AVL_node_ty *node);
static AVL_node_ty *TraversSide(AVL_node_ty *iter, int side);
static AVL_node_ty *FindParent(AVL_ty *tree, AVL_node_ty *root, void *key, int *side);
static size_t CountChildren(AVL_node_ty *node);
static AVL_node_ty *LeftRotate(AVL_node_ty *node);
static AVL_node_ty *RightRotate(AVL_node_ty *node);
void print2D(AVL_ty *tree);
static void print2DUtil(AVL_node_ty *root, int space);
static AVL_node_ty *AVLInsertBalRec(AVL_ty *tree, AVL_node_ty *root, AVL_node_ty *new_node);/*balance insert*/
static int GetNodeBalance(AVL_node_ty *node);
static void CopyContent(AVL_node_ty *from, AVL_node_ty *to);
static AVL_node_ty *BalanceTheTree(AVL_node_ty *node);
static AVL_node_ty *RemoveNodeByCopy(AVL_ty *tree, AVL_node_ty *root);
static AVL_node_ty *AVLRemoveBalRec(AVL_ty *tree, AVL_node_ty *root, void *data);
static size_t GetNodeH(AVL_node_ty *node); 
static AVL_node_ty *RemoveTwoChild(AVL_ty *tree, AVL_node_ty *root);
static AVL_node_ty *RemoveOneChild(AVL_ty *tree, AVL_node_ty *root);
static AVL_node_ty *RemoveLeaf(AVL_ty *tree, AVL_node_ty *root);                                      /*non recursive height*/   
/*------------------definitions-----------------------------------------------*/

/*--------------------API---------------------------*/


AVL_ty *AVLCreate(AVL_cmp_func_ty compare)
{
    AVL_ty *avl = malloc(sizeof(AVL_ty));
    if(NULL != avl)
    { 
        avl->compare = compare;

        avl->root = NULL; 
    }
    return avl;
}

void AVLDestroy(AVL_ty *tree)
{
    assert(NULL != tree);

    AVLDestroyRec(tree->root);
    free(tree);
    tree = NULL;
}

void *AVLFind(AVL_ty *tree, void *key)
{

    assert(tree != NULL);

    return AVLSearchRecurcive(tree, tree->root, key);
}

int AVLInsert(AVL_ty *tree, void *data)
{
    AVL_node_ty *node_to_insert = NULL;
    AVL_node_ty *root = NULL;


    assert(tree != NULL);

    root = tree->root;
    node_to_insert = CreateNode(data);
    if(NULL == node_to_insert)
    {
       return FAIL; 
    }
    if(NULL == root)
    {
        tree->root = node_to_insert;
        return SUCCESS;
    }

    AVLInsertRecurcive(tree, root, node_to_insert);
    return SUCCESS;
}

int AVLInsertBalance(AVL_ty *tree, void *data)
{
    AVL_node_ty *node_to_insert = NULL;
    AVL_node_ty *root = NULL;

    assert(tree != NULL);

    root = tree->root;
    node_to_insert = CreateNode(data);
    if(NULL == node_to_insert)
    {
       return FAIL; 
    }
    if(NULL == root)
    {
        tree->root = node_to_insert;
        return SUCCESS;
    }
    tree->root = AVLInsertBalRec(tree, tree->root, node_to_insert);
    return SUCCESS;
}

size_t AVLSize(const AVL_ty *tree)
{
    int count = 0;

    assert(NULL != tree);

    if(NULL != tree->root)
    {
        count = AVLSizeRec(tree->root);
    }
    return count;
}

size_t AVLHeight(const AVL_ty *tree)
{
    int count = 0;

    assert(NULL != tree);
    if(NULL != tree->root)
    {
        count = AVLHightRec(tree->root);
    }
    return count;
}

int AVLIsEmpty(const AVL_ty *tree)
{
    assert(NULL != tree);
    return (NULL == tree->root);
}

int AVLForEach(const AVL_ty *tree, AVL_action_func_ty operation, void *param, int travesal_type)
{
    assert(NULL != tree);
    assert(NULL !=operation);
    switch (travesal_type)
    {
    case 1:
        printf("pre order:\n");
        return PreOrderForEach(tree->root, operation, param);
    case 2:
         printf("in order:\n");
        return InOrderForEach(tree->root, operation, param);
    default:
        printf("post order:\n");
        return PostOrderForEach(tree->root, operation, param);
      
    }
}

void AVLRemove(AVL_ty *tree, void *data)
{
    int side = 0;
    AVL_node_ty *parent_of_node_to_remove = NULL;
    assert(NULL != tree);
    if(0 == tree->compare(tree->root->data, data))
    {
        RemoveRoot(tree);
        return;
    }
    parent_of_node_to_remove = FindParent(tree, tree->root, data, &side);
    if ( NULL != parent_of_node_to_remove)
    {
        RemoveNode(parent_of_node_to_remove, side);   
    }
}

void AVLRemoveBalanc(AVL_ty *tree, void *data)
{
    assert(NULL != tree);
    tree->root = AVLRemoveBalRec(tree, tree->root, data);
}


/*--------------------SERVIC---------------------------*/
static void RemoveRoot(AVL_ty *tree)
{
    AVL_node_ty *root = tree->root;
    size_t childrens = CountChildren(root);
    AVL_node_ty *next = NULL;
    switch (childrens)
    {
    case 0:
        tree->root = NULL;
        break;
    case 1:
        if(root->relatives[LEFT] == NULL)
        {
            tree->root = root->relatives[RIGHT];
        }
        else
        {
            tree->root = root->relatives[LEFT];
        }
        break;
    default:
            next = Next(root);
            next->relatives[LEFT] = root->relatives[LEFT];
            tree->root = root->relatives[RIGHT];
        break;
    }
    DestroyNode(root);
}

static size_t CountChildren(AVL_node_ty *node)
{
    size_t count = 0;
    if(node->relatives[LEFT] != NULL)
    {
        count++;
    }
    if(node->relatives[RIGHT] != NULL)
    {
        count++;
    }
    return count;
}

static void RemoveNode(AVL_node_ty *parent, int side)
{
    AVL_node_ty *node_to_remove = parent->relatives[side];
    AVL_node_ty *next = NULL;
    size_t childrens = CountChildren(node_to_remove);
    switch (childrens)
    {
    case 0:
        parent->relatives[side] = NULL;
        break;
    case 1:
        if(node_to_remove->relatives[LEFT] == NULL)
        {
            parent->relatives[side] = node_to_remove->relatives[RIGHT];
        }
        else
        {
            parent->relatives[side] = node_to_remove->relatives[LEFT]; 
        }
        break;
    default:
            next = Next(node_to_remove);
            next->relatives[LEFT] = node_to_remove->relatives[LEFT];
            parent->relatives[side] = node_to_remove->relatives[RIGHT];
        break;
    }
    DestroyNode(node_to_remove);
}

static AVL_node_ty *Next(AVL_node_ty *node)
{
    node = node->relatives[RIGHT];
    return TraversSide(node, LEFT);
}

static AVL_node_ty *TraversSide(AVL_node_ty *iter, int side)
{
    if(NULL == iter->relatives[side])
    {
        return iter;
    }
    return TraversSide(iter->relatives[side], side);

}

static AVL_node_ty *FindParent(AVL_ty *tree, AVL_node_ty *root, void *key, int *side)
{
    int cmp_ret_root = 0;
    
    if(NULL == root)
    {
        return NULL;
    }

    cmp_ret_root = tree->compare(key, root->data);
    
    if (cmp_ret_root < 0)
    {   
        if(0 == tree->compare(key, root->relatives[LEFT]->data))
        {
            *side = LEFT;
            return root;
        }
        return FindParent(tree,root->relatives[LEFT], key, side);  
    } 
    else if (cmp_ret_root > 0)
    {
        if(0 == tree->compare(key, root->relatives[RIGHT]->data))
        {
            *side = RIGHT;
            return root;
        }
        return FindParent(tree, root->relatives[RIGHT], key, side);
    }
    return root->data; 
}

static int PreOrderForEach(AVL_node_ty *root, AVL_action_func_ty operation, void *param )
{
    AVL_node_ty *left = NULL;
    AVL_node_ty *right = NULL;
    
    assert(NULL != root);

    left = root->relatives[LEFT];
    right = root->relatives[RIGHT];
    operation(root->data, param);

    if(NULL != left)
    {
        PreOrderForEach(left, operation, param);
    }
    if(NULL != right)
    {
        PreOrderForEach(right, operation, param);
    }
    return SUCCESS;

}

static int InOrderForEach(AVL_node_ty *root, AVL_action_func_ty operation, void *param )
{
    AVL_node_ty *left = NULL;
    AVL_node_ty *right = NULL;
   
    assert(NULL != root);

    left = root->relatives[LEFT];
    right = root->relatives[RIGHT];
    
    if(NULL != left)
    {
        InOrderForEach(left, operation, param);
    }
    
    operation(root->data, param);

    if(NULL != right)
    {
        InOrderForEach(right, operation, param);
    }
    return SUCCESS;

}

static int PostOrderForEach(AVL_node_ty *root, AVL_action_func_ty operation, void *param )
{
    AVL_node_ty *left = NULL;
    AVL_node_ty *right = NULL;
    int ans = 0;
    assert(NULL != root);

    left = root->relatives[LEFT];
    right = root->relatives[RIGHT];
    
    if (NULL != left)
    {
        ans = PostOrderForEach(left, operation, param);
    }
    if (NULL != right)
    {
        ans = PostOrderForEach(right, operation, param);
    }
    if (ans != NON_ZERO)
    {
        operation(root->data, param);
        ans = 0;
    }
    return ans;

}

static void AVLDestroyRec(AVL_node_ty *root)
{
    
    if(root == NULL)
    {
        return;
    }
    AVLDestroyRec(root->relatives[LEFT]);
    AVLDestroyRec(root->relatives[RIGHT]);
   
    DestroyNode(root);
}

static void *AVLSearchRecurcive(AVL_ty *tree, AVL_node_ty *root , void *data_to_match)
{
    int cmp_ret = 0;
    if(NULL == root)
    {
        return NULL;
    }

    cmp_ret = tree->compare(data_to_match, root->data);
    
    if (cmp_ret < 0)
    {   
        return AVLSearchRecurcive(tree,root->relatives[LEFT], data_to_match);  
    } 
    else if (cmp_ret > 0)
    {
        return AVLSearchRecurcive(tree, root->relatives[RIGHT], data_to_match);
    }
    return root->data; 
}

static int AVLInsertRecurcive(AVL_ty *tree, AVL_node_ty *root , AVL_node_ty *node_to_insert)
{
    int cmp_ret = 0;
    assert(NULL != tree);

    cmp_ret = tree->compare(node_to_insert->data, root->data);
    
    assert(0 != cmp_ret);

    if(cmp_ret > 0)
    {
        if(root->relatives[RIGHT] == NULL)
        {
            root->relatives[RIGHT] = node_to_insert;
            return SUCCESS;
        }
        return AVLInsertRecurcive(tree, root->relatives[RIGHT], node_to_insert);    
    }
    else if(cmp_ret < 0)
    {   
        if(root->relatives[LEFT] == NULL)
        {
            root->relatives[LEFT] = node_to_insert;
            return  SUCCESS;
        }
        return AVLInsertRecurcive(tree,root->relatives[LEFT], node_to_insert);  
    } 
    return FAIL;
}

static size_t AVLSizeRec(AVL_node_ty *root)
{

   if(NULL == root)
   {
       return 0;
   }
    return 1 + AVLSizeRec(root->relatives[RIGHT]) + AVLSizeRec(root->relatives[LEFT]);
}

static size_t AVLHightRec(AVL_node_ty *root)
{
    AVL_node_ty *left = NULL;
    AVL_node_ty *right = NULL;
    size_t count_left = 0;
    size_t count_right = 0;
    size_t max = 0;
    if(root == NULL)
    {
        return 0;
    }

    left = root->relatives[LEFT];
    right = root->relatives[RIGHT];

    if (NULL != left)
    {
        count_left += 1 + AVLHightRec(left) ;
    }
    if (NULL != right)
    {
         count_right += 1 + AVLHightRec(right);
    }
    max = MAX(count_left, count_right);
    return max;
}

static AVL_node_ty *CreateNode(void *data)
{
    AVL_node_ty *new_node = malloc(sizeof(AVL_node_ty));
    if(NULL != new_node)
    {
        new_node->data = data;
        new_node->relatives[RIGHT] = NULL;
        new_node->relatives[LEFT] = NULL;
        new_node->height = 1;
    
    }
    return new_node;
}

static void *DestroyNode(AVL_node_ty *node)
{
    void *data = node->data;
    free(node);
    node = NULL;
    return data;
}

static void print2DUtil(AVL_node_ty *root, int space)
{
    int i = 0;

    if (root == NULL)
    {
        return;
    }

    space += 10;

    print2DUtil(root->relatives[RIGHT], space);

    printf("\n");

    for (i = 10; i < space; ++i)
    {
        printf(" ");
    }
    printf("%d\n", (int)(size_t)root->data);

    print2DUtil(root->relatives[LEFT], space);

}

void print2D(AVL_ty *tree)
{
    static int count = 0;
    printf("call num : %d\n", count++);
    printf("--------------------------------\n");
    print2DUtil(tree->root, 0);

}

static AVL_node_ty *AVLInsertBalRec(AVL_ty *tree, AVL_node_ty *root, AVL_node_ty *new_node)
{
    int compare_return_status = 10;
    int max_height = 0;

    assert(NULL != new_node);

    if (NULL == root)
    {
        return new_node;
    }
    
    compare_return_status = tree->compare(new_node->data, root->data);

    assert(0 != compare_return_status);

    if (0 < compare_return_status)
    {
        root->relatives[RIGHT] = AVLInsertBalRec(tree, root->relatives[RIGHT], new_node);
          
    }
    else if (0 > compare_return_status)
    {
        root->relatives[LEFT] = AVLInsertBalRec(tree, root->relatives[LEFT], new_node);    
    }
    max_height =  MAX(GetNodeH(root->relatives[LEFT]), GetNodeH(root->relatives[RIGHT]));
    root->height = 1 + max_height;
    
    return BalanceTheTree(root);
}

static int GetNodeBalance(AVL_node_ty *node)
{
    assert(NULL != node);
    return GetNodeH(node->relatives[LEFT]) - GetNodeH(node->relatives[RIGHT]);
}

static size_t GetNodeH(AVL_node_ty *node)
{
    size_t h = 0;
    if(NULL != node)
    {
        h = node->height;
    }
    return h;
}

static AVL_node_ty *RightRotate(AVL_node_ty *node)
{
    AVL_node_ty *left = node->relatives[LEFT];
    AVL_node_ty *left_sub_right = left->relatives[RIGHT];

    left->relatives[RIGHT] = node;
    node->relatives[LEFT] = left_sub_right;
    
    node->height = 1 + MAX(GetNodeH(node->relatives[LEFT]), GetNodeH(node->relatives[RIGHT]));
    left->height = 1 + MAX(GetNodeH(left->relatives[LEFT]), GetNodeH(left->relatives[RIGHT]));

    return left;
}

static AVL_node_ty *LeftRotate(AVL_node_ty *node)
{
    size_t max_r = 0;
    size_t max_l = 0;
    AVL_node_ty *right = node->relatives[RIGHT];
    AVL_node_ty *right_sub_left = right->relatives[LEFT];

    right->relatives[LEFT] = node;
    node->relatives[RIGHT] = right_sub_left;
    max_r = MAX(GetNodeH(node->relatives[LEFT]), GetNodeH(node->relatives[RIGHT]));
    max_l =  MAX(GetNodeH(right->relatives[LEFT]), GetNodeH(right->relatives[RIGHT]));
    node->height = 1 + max_r;
    right->height = 1 + max_l;

    return right;
}

static AVL_node_ty *AVLRemoveBalRec(AVL_ty *tree, AVL_node_ty *root, void *data)
{
    int compare_return_status = 1;

    size_t max_height = 0;

    if(NULL == root)
    {
        return NULL;
    }

    compare_return_status = tree->compare(data, root->data);
    if (0 < compare_return_status)
    {
        root->relatives[RIGHT] = AVLRemoveBalRec(tree, root->relatives[RIGHT], data);
    }
    else if (0 > compare_return_status)
    {
        root->relatives[LEFT] = AVLRemoveBalRec(tree, root->relatives[LEFT], data);
    }
    else
    {
      root = RemoveNodeByCopy(tree, root);  
      if(NULL == root)
      {
          return NULL;
      }
    }  
    max_height =  MAX(GetNodeH(root->relatives[LEFT]), GetNodeH(root->relatives[RIGHT]));
    root->height = 1 + max_height;
    return BalanceTheTree(root);
    
  
}

static AVL_node_ty *RemoveLeaf(AVL_ty *tree, AVL_node_ty *root)
{
    (void)tree;
    DestroyNode(root);
    root = NULL;
    return root;
}

static AVL_node_ty *RemoveOneChild(AVL_ty *tree, AVL_node_ty *root)
{
    (void)tree;
    if(NULL == root->relatives[RIGHT])
    {
        CopyContent(root->relatives[LEFT], root);
        DestroyNode(root->relatives[LEFT]);
        root->relatives[LEFT] = NULL;
    }
    else 
    {
        CopyContent(root->relatives[RIGHT], root);
        DestroyNode(root->relatives[RIGHT]);
        root->relatives[RIGHT] = NULL;
    }
    return root;
}

static AVL_node_ty *RemoveTwoChild(AVL_ty *tree, AVL_node_ty *root)
{
    AVL_node_ty *next = NULL;
    next = TraversSide(root->relatives[RIGHT], LEFT);
    CopyContent(next, root);
    root->relatives[RIGHT] = AVLRemoveBalRec(tree, root->relatives[RIGHT], next->data);
    return root;

}

static AVL_node_ty *RemoveNodeByCopy(AVL_ty *tree, AVL_node_ty *root)
{
    static remove_func_ty remove_func_lut [3] ={RemoveLeaf, RemoveOneChild, RemoveTwoChild};

    size_t num_of_childrens = CountChildren(root);
    root = remove_func_lut[num_of_childrens](tree, root);
    return root;

}

static AVL_node_ty *BalanceTheTree(AVL_node_ty *node)
{
    int balance = GetNodeBalance(node);
    AVL_node_ty *left = node->relatives[LEFT];
    AVL_node_ty *right = node->relatives[RIGHT];


    if (1 < balance)
    {
       
        if(1 <= GetNodeBalance(left))
        {
            return RightRotate(node);
        }
        node->relatives[LEFT] = LeftRotate(node->relatives[LEFT]);
        return RightRotate(node);  
    }
    if (-1 > balance )
    {

        if (-1 >= GetNodeBalance(right))
        {
            return LeftRotate(node);
        }
        node->relatives[RIGHT] = RightRotate(node->relatives[RIGHT]);
        return LeftRotate(node);
        
    }
    return node;
}

static void CopyContent(AVL_node_ty *from, AVL_node_ty *to)
{
   to->data = from->data;
   to->height = from->height;
}