#include <stdlib.h>
#include "bs.h"

int IterativeBinarySearch(int arr [], size_t size, int target)
{
    int ans = -1;
    size_t left = 0;
    size_t right = size - 1;
    size_t middle = 0;
    while (left <= right)
    {
        middle = (left + (right - left)) / 2;
        if (arr[middle] == target)
        {
            ans = middle;
            break;
        }
        else if (arr[middle] > target)
        {
            right = middle - 1;
        }
        else
        {
            left = middle + 1;
        }
    }
    return ans;
}

int RecursiveBinarySearch(int arr[], int left, int right, int target)
{
    int ans = -1;
    int middle = (left + (right - left)) / 2;
    if (right < left)
    {
        return ans;
    }
    if(arr[middle] == target)
    {
        ans = middle;
    }
    else if (arr[middle] < target)
    {
        ans = RecursiveBinarySearch(arr, middle + 1, right, target); 
    }
    else
    {
        ans = RecursiveBinarySearch(arr, left, middle -1, target);
    }
    return ans;
}

void *BinarySearchIterative(void *arr,  cmp_func_ty cmp_func, void *data,  size_t num_of_elements, size_t size_of_element)
{
    void *data_to_cmp = NULL;
    int cmp_stat = 0;
    size_t middle = 0;
    while (num_of_elements > 0 )
    {
        middle = num_of_elements / 2;
        data_to_cmp = (void *)((char *)arr + (middle * size_of_element));
        cmp_stat =cmp_func(data, data_to_cmp );
        if (0 == cmp_stat)
        {
            return data_to_cmp;
        }
        else 
        {
            if (0 < cmp_stat)
            {
              arr = (void *)((char *)arr + ((middle + 1)* size_of_element));
              num_of_elements = num_of_elements - middle - 1;
            }
            else
            {
                num_of_elements = middle;
            }  
        }
    }
    return NULL;
}



void *BinarySearchRecursive(void *arr,  cmp_func_ty cmp_func, void *data, 
                      size_t num_of_elements, size_t size_of_element)
{
    int middle = num_of_elements / 2;
    void *data_to_cmp = ((char *)arr + (middle * size_of_element));
    int cmp_stat = -2;
    
    if(num_of_elements <= 0)
    {
        return NULL;
    }
    
    cmp_stat = cmp_func(data, data_to_cmp);
    if(cmp_stat == 0)
    {
        return data_to_cmp;
    }
    else
    {
        if(cmp_stat > 0)
        {
            arr = ((char *)arr + ((middle + 1) * size_of_element));
            num_of_elements = (num_of_elements - middle -1);
        }
        else
        {
            num_of_elements = middle;
        }
        return BinarySearchRecursive(arr, cmp_func, data ,num_of_elements , size_of_element);
    }
    
    
    
}




     


     




