#include <assert.h> /* assert */
#include "comparation_sorts.h"

#include <stdio.h>

static void SwapInts(int *one, int *other);

void BubbleSort(int *arr, size_t length)
{
    size_t i = 0, j = 0;
    assert(NULL != arr);

    for (i = 0; i < length - 1; ++i)
    {
        for (j = 0; j < length - 1; ++j)
        {
            if (arr[j] > arr[j + 1])
            {
                SwapInts(arr + j, arr + j + 1);
            }
        }       
    }
}

void InsertionSort(int *arr, size_t length)
{
    size_t index = 1;
    size_t inner_index = 0;
    int cur_val = 0;

    assert(NULL != arr);

    for (index = 1; index < length; ++index)
    {
        cur_val = arr[index];
        for (inner_index = index; 0 < inner_index && cur_val < arr[inner_index - 1]; --inner_index)
        {
            arr[inner_index] = arr[inner_index - 1];
        }
        arr[inner_index] = cur_val;    
    }
}

void SelectionSort(int *arr, size_t length)
{
    size_t current_index = 0;
    size_t inner_index = 0;
    size_t min_index = 0;

    assert(NULL != arr);

    for (current_index = 0; current_index < length - 1; ++current_index)
    {
        for (min_index = current_index, inner_index = current_index + 1; inner_index < length;
                                                                 ++inner_index)
        {
            if (arr[inner_index] < arr[min_index])
            {
                min_index = inner_index;
            }
        }
        SwapInts(arr + min_index, arr + current_index);
    }
}

static void SwapInts(int *one, int *two)
{
    int holder = 0;

    assert(NULL != one);
    assert(NULL != two);

    holder = *one;
    *one = *two;
    *two = holder;
}