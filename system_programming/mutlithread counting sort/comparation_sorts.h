#ifndef __COMPARATION_SORTS_H__
#define __COMPARATION_SORTS_H__

#include <stddef.h> /* size_t */

/*DESCRIPTION: 
*sort the array by Bubble algorithm.
*@param
*	arr - array to be sorted.
*	length - length of the array.
*@return
* no return.
*/
void BubbleSort(size_t arr[], size_t size);

/*DESCRIPTION: 
*sort the array by Selection algorithm.
*@param
*	arr - array to be sorted.
*	length - length of the array.
*@return
* no return.
*/
void SelectionSort(size_t arr[], size_t size);

/*DESCRIPTION: 
*sort the array by Insertion algorithm.
*@param
*	arr - array to be sorted.
*	length - length of the array.
*@return
* no return.
*/
void InsertionSort(size_t arr[], size_t size);
/*DESCRIPTION: 
*sort the array by counting sort algorithm.
*@param
*	arr - array to be sorted.
*	length - length of the array.
*@return
* no return.
*/
void CountSort(size_t arr[], size_t size);


void RadixSort(size_t arr[], size_t size);

#endif /*__COMPARATION_SORTS_H__*/