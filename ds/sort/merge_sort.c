#include <stdlib.h>
#include <string.h> /*memcpy*/
#define MALLOC_FAIL (1)

static int MergeSortRec(int *arr_to_sort, size_t left, size_t right);
static int Merge(int *arr_to_sort, size_t left, size_t pivot, size_t right);

static void SwapVoid(void *one, void *two, size_t size);

size_t partition(void *base, size_t low_idx, size_t high_idx, size_t size,int (*compar)(const void *, const void *));

int MergeSort(int *arr_to_sort, size_t size)
{

    return MergeSortRec(arr_to_sort, 0, size - 1);
}

static int MergeSortRec(int *arr_to_sort, size_t left, size_t right)
{
    int status = 0;
    size_t pivot = (left + right) / 2;
    if(left < right)
    {
        MergeSortRec(arr_to_sort, left, pivot);
        MergeSortRec(arr_to_sort, pivot + 1, right);
        status = Merge(arr_to_sort, left, pivot, right);
    }
    return status;
}

static int Merge(int *arr_to_sort, size_t left, size_t pivot, size_t right)
{
    size_t left_arr_idx = 0;
    size_t right_arr_idx = 0;
    size_t merge_idx = 0;
    size_t left_arr_size = pivot - left + 1;
    size_t right_arr_size = right - pivot;
    int *right_arr = NULL;
    int *left_arr = malloc(sizeof(int) * left_arr_size);
    if(left_arr != NULL)
    {
        right_arr = malloc(sizeof(int) * right_arr_size);
        if(NULL == right_arr)
        {
            free(left_arr);
            return MALLOC_FAIL;
        }
    }

    for (left_arr_idx = 0; left_arr_idx < left_arr_size; left_arr_idx++) 
    {
        left_arr[left_arr_idx] = arr_to_sort[left + left_arr_idx];
    }
    for (right_arr_idx = 0; right_arr_idx < right_arr_size; right_arr_idx++) 
    {
        right_arr[right_arr_idx] = arr_to_sort[pivot + right_arr_idx + 1];
    }

    left_arr_idx = right_arr_idx =  0;
    merge_idx = left;

    while(left_arr_idx < left_arr_size && right_arr_idx < right_arr_size)
    {
        if(left_arr[left_arr_idx] < right_arr[right_arr_idx])
        {
            arr_to_sort[merge_idx] = left_arr[left_arr_idx];
            ++left_arr_idx;
        }
        else
        {
            arr_to_sort[merge_idx] = right_arr[right_arr_idx];
            ++right_arr_idx;
        }
        ++merge_idx; 
    }
    while (left_arr_idx < left_arr_size)
    {
        arr_to_sort[merge_idx] = left_arr[left_arr_idx];
        ++left_arr_idx;
        ++merge_idx;
    }
      while (right_arr_idx < right_arr_size)
    {
        arr_to_sort[merge_idx] = right_arr[right_arr_idx];
        ++right_arr_idx;
        ++merge_idx;
    }
    free(left_arr);
    free(right_arr);
    return 0; 
}

void Qsort(void *base, size_t nmemb, size_t size,
                  int (*compar)(const void *, const void *))
{
    if(nmemb > 1)
    {
        size_t pivot_idx = 0;
        pivot_idx = partition(base, 0 , nmemb -1, size ,compar);
    
        Qsort(base, pivot_idx, size, compar);
        Qsort((void *)((char *)base + ((pivot_idx + 1) * size)) , (nmemb - pivot_idx -1) , size, compar);  
    }
   
}

size_t partition(void *base, size_t low_idx, size_t high_idx, size_t size,int (*compar)(const void *, const void *))
{
    void *pivot = NULL;
    void *to_comp = NULL;
    int i = 0;
    size_t j = 0;
    i = low_idx - 1;
    j = 0;
    
    pivot = ((char *)base + (high_idx * size));

    for(j = low_idx; j <= high_idx - 1; j++)
    {
        to_comp = ((char *)base + (j * size));
        if(0 > compar(to_comp, pivot))
        {
            ++i;
            SwapVoid((void **)((char *)base + (j * size)), (void **)((char *)base + (i * size)), size);
        }
    }
    SwapVoid((void **)((char *)base + ((i + 1) * size)), (void **)((char *)base + (high_idx * size)), size);
    return (i+1);
}





