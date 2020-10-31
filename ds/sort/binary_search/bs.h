#ifndef __BS_H__
#define __BS_H__



typedef int (*cmp_func_ty)(const void *data, const void *data_to_compare);

void *BinarySearchIterative(void *arr,  cmp_func_ty cmp_func, void *data,
                            size_t num_of_elements, size_t size_of_element);


void *BinarySearchRecursive(void *arr,  cmp_func_ty cmp_func, void *data, 
                           size_t num_of_elements, size_t size_of_element);


#endif




