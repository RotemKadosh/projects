typedef struct r_binary_search_tree RBST_ty;
typedef struct tree_node rbst_node_ty;
typedef rbst_node_ty *RBST_iter_ty;
/* DESCRIPTION: 
 *compare two elements data;
 * 0 -if same
 * positive if data > data_to_compare
 * negative if data < data_to_compare
 */
typedef int(*RBST_cmp_func_ty)(const void *data, const void *data_to_compare, void *params);
/* DESCRIPTION: 
 * perform action on elements in BST
 * this action should not change the sorting criteria 
 * 0 on success, non-zero on faliure
 */
typedef int(*RBST_action_func_ty)(const void *data, void * param); 

/* DESCRIPTION: 
 *  create binary search tree,
 *  tree created by this function should be destroy using BDTDestroy function 
 *  
 *		@param
 *		compare - pointer to function to sort the tree by
 *
 * @return
 * pointer to created BST, 
 */
RBST_ty *RBSTCreate(RBST_cmp_func_ty compare, void *params);
/* DESCRIPTION: 
 * destroy BST and free all allocated memory
 * 
 *		@param
 *		pointer to BST to be destroyed
 *
 * @return
 * 
 */
void RBSTDestroy(RBST_ty *tree);
/* DESCRIPTION: 
 * find a element wich holds key and return pointer to this element.
 * BSTEnd in case of failure
 * 
 *		@param
 *		tree - pinter to BST to look in
 *      data_to_match - datato look for
 *
 * @return
 *  iterator to the element, iterator to BSTEnd if not found
 */
RBST_iter_ty RBSTFind(RBST_ty *tree, void *data_to_match);
/* DESCRIPTION: 
 * insert new element to the tree in right location.
 * duplicate values will inserted to larger subtree
 *  
 *		@param
 *		tree -	tree - pinter to BST to insert to
 *      data - data of new element 
 *
 * @return
 *  iterator to inserted element, iterator to BSTEnd in case of faliure
 */
RBST_iter_ty RBSTInsert(RBST_ty *tree, void *data);
/* DESCRIPTION: 
 * deletes element from the tree  
 * 
 *		@param
 *		iter - iterator to element to delete
 *      
 * @return
 *  data of the deleted element
 */
void *RBSTRemove(RBST_iter_ty iter);
/*DESCRIPTION:
* checks if there are any elements in the tree
* 
*	@param
* 	tree - pointer to the tree
*
*@return
* 1 if empty, 0 if not
*/
int RBSTIsEmpty(const RBST_ty *tree);

/*DESCRIPTION:
* gets the amounts of elements in the tree
*   
*	@param
* 	tree - pointer to the tree
*
*@return
*number of elements in the tree
*/
size_t RBSTSize(const RBST_ty *tree);
/*DESCRIPTION:
* activate operation function on each element in given range [from, to)
* operation should not change the compare critiria	
    @param
* 	tree - pointer to the tree
    operation - function to aactivate
    from -iter to element to start
    to - iter to element to end
    param - parameter to operation function
*
*@return
*0 on success, non-zero on faliure
*/
int RBSTForEach(RBST_iter_ty from, RBST_iter_ty to, RBST_action_func_ty operation, void  *param);

/* DESCRIPTION: 
 * return iterator first element by order  
 * begin on empty tree is undifined
 * 
 *		@param
 *		tree -pointer to tree
 *
 * @return
 *  iterator to first element by order
 */
RBST_iter_ty RBSTBegin(const RBST_ty *tree);
/* DESCRIPTION: 
 * return iterator last element by order  
 * this iterator should not be removed
 *		@param
 *		tree -pointer to tree
 *
 * @return
 *  iterator to last element by order
 */
RBST_iter_ty RBSTEnd(const RBST_ty *tree);
/* DESCRIPTION: 
 * return data of element pointed by iter  
 *  
 *		@param
 *		tree -pointer to tree
 *
 * @return
 *  data of element
 */

void *RBSTGetData(RBST_iter_ty iter);
/* DESCRIPTION: 
 * compare two iterators 
 * 
 * 	@param
 *		iter1
        iter2
 *
 * @return
 *  1 - if same, 0- if not 
 */

int RBSTIsSameIter(RBST_iter_ty iter1, RBST_iter_ty iter2);

