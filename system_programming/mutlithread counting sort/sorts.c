#include <assert.h> /* assert */
#include "comparation_sorts.h"
#include <stdio.h>
#include <stddef.h> /*size_t*/
#include <string.h>/*memcpy*/
#include <ctype.h> /*ssize_t*/
#include <stdlib.h>/*calloc, free*/
#define MAX(a,b) (((a)>(b))?(a):(b))

typedef size_t (*get_key_func_t)(size_t *data, size_t param);

static size_t GetMin(size_t arr[], size_t size, get_key_func_t GetKey, size_t param);
static size_t GetMax(size_t arr[], size_t size, get_key_func_t GetKey, size_t param);

static void CountSortByKey(size_t arr[], size_t size, get_key_func_t GetKey, size_t param);

static void InitCount(size_t arr[], size_t count[], size_t size, size_t min,
                                             get_key_func_t GetKey, size_t param);
static void SumCount(size_t count[], size_t range);
static void SetOutput(size_t arr[], size_t count[], size_t output[], size_t size,
                                     size_t min, get_key_func_t GetKey, size_t param);

static size_t CountGetKey(size_t *num, size_t param);
static size_t RadixGetKey(size_t *num, size_t param);
/*---------service functions----------*/

static void Swap(size_t *num1 , size_t *num2)
{
    size_t temp = *num1;
    *num1 = *num2;
    *num2 = temp;
}
static size_t CountGetKey(size_t *num, size_t param)
{
    assert(NULL != num);
    
    (void)param;
    return *num;
}

static size_t RadixGetKey(size_t *num, size_t param)
{
    assert(NULL != num);

    return (*num / param) % 10;
}

static void CountSortByKey(size_t arr[], size_t size, get_key_func_t GetKey,
                                                                     size_t param)
{
    size_t range = 0;
    size_t min = 0, max = 0;
    size_t *count = NULL;
    size_t *output = NULL;
   
    assert(NULL != arr);
    assert(NULL != GetKey);

    min = GetMin(arr, size, GetKey, param);
    max = GetMax(arr, size, GetKey, param);
    range = max - min + 1;

    count = (size_t *)calloc(range, sizeof(size_t));
    if(NULL == count)
    {
        printf("calloc failed");
        return;
    }

    output = (size_t *)malloc(size * sizeof(size_t));
    if(NULL == output)
    {
        free(count);
        count = NULL;
        printf("malloc failed");
        return;
    }
    InitCount(arr, count, size, min, GetKey, param);
    SumCount(count, range);
    SetOutput(arr, count, output, size, min, GetKey, param);
    memcpy(arr, output, size * sizeof(size_t));

    free(count);
    count = NULL;
    free(output);
    output = NULL;
}


static size_t GetMin(size_t arr[], size_t size, get_key_func_t GetKey, size_t param)
{
    size_t *runner = arr;
    size_t *end = arr + size -1;
    size_t val_after_key = 0;
    size_t min = 0;
    
    assert(NULL != arr);
    assert(NULL != GetKey);
    
    min = GetKey(arr, param);

    for (runner = arr; runner <= end; ++runner)
    {
        val_after_key = GetKey(runner, param);
        if (val_after_key < min)
        {
            min = val_after_key;
        } 
    }

    return min; 
}

static size_t GetMax(size_t arr[], size_t size, get_key_func_t GetKey, size_t param)
{
    size_t *runner = arr;
    size_t *end = arr + size -1;
    size_t val_after_key = 0;
    size_t max = 0;
    
    assert(NULL != arr);
    assert(NULL != GetKey);
    
    max = GetKey(arr, param);

    for (runner = arr; runner <= end; ++runner)
    {
        val_after_key = GetKey(runner, param);
        if (val_after_key > max)
        {
            max  = val_after_key;
        }
    }

    return max; 
}

static void InitCount(size_t arr[], size_t count[], size_t size, size_t min,
                                            get_key_func_t GetKey, size_t param)
{
    size_t *runner = arr;
    size_t *end = arr + size -1;

    assert(NULL != arr);
    assert(NULL != count);
    assert(NULL != GetKey);

    for (runner = arr; runner <= end; ++runner)
    {
        ++count[GetKey(runner, param) - min];
    }
}
 
static void SumCount(size_t count[], size_t range)
{
    size_t *runner = count;
    size_t *end = count + range -1;
    
    assert(NULL != count);

    --(*runner);
    
    for (runner = count + 1; runner <= end; ++runner) 
    {
        *runner += *(runner - 1);
    }
}

static void SetOutput(size_t arr[], size_t count[], size_t output[], size_t size,
                                    size_t min, get_key_func_t GetKey, size_t param)
{
    size_t *runner = NULL;
    size_t *end = arr + size -1;
    size_t val_after_key = 0;
    size_t count_val = 0;
    
    assert(NULL != arr);
    assert(NULL != count);
    assert(NULL != output);
    assert(NULL != GetKey);   

    for (runner = end; runner >= arr; --runner)
    { 
        val_after_key = GetKey(runner, param);
        count_val = count[val_after_key - min];
        output[count_val] = *runner; 
        --count[val_after_key - min];
    }
}

/*---------Sort functions----------*/

void BubbleSort(size_t arr[], size_t size)
{
    int sorted = 0;
    size_t start = 0;
    size_t runner = 0;
    for (start = 1; start < size  && sorted != 1 ; ++start)  
    {     
        sorted = 1;
        for (runner = 0; runner < size - start ; ++runner)  
        {
            if ((arr[runner]) > arr[runner + 1]) 
            {
                Swap(&arr[runner], &arr[runner + 1]);
                sorted = 0; 
            }
        }
    }
} 

void SelectionSort(size_t arr[], size_t size)
{
    size_t idx_of_next_min = 0;
    size_t runner = 0;
    size_t current_min_idx = 0;
    
    for(idx_of_next_min = 0; idx_of_next_min < size; ++idx_of_next_min)
    { 
        current_min_idx = idx_of_next_min;
        for(runner = idx_of_next_min ; runner < size; ++runner)
        {
            if(arr[runner] < arr[current_min_idx])
            {
                current_min_idx = runner;
            }
        }
        Swap(&arr[idx_of_next_min], &arr[current_min_idx]);
    }
}

void InsertionSort(size_t arr[], size_t size)
{
    size_t selection_idx = 0;
    size_t selection = 0;
    __ssize_t where = 0; 
    for (selection_idx = 1; selection_idx < size; selection_idx++) { 
        selection = arr[selection_idx]; 
        where = selection_idx - 1; 
        while ((long)where >= 0 && arr[where] > selection)
        { 
            arr[where + 1] = arr[where]; 
            where = where - 1; 
        } 
        arr[where + 1] = selection; 
    }
}

void CountSort(size_t arr[], size_t size)
{
    CountSortByKey(arr, size, CountGetKey, 0);
}

void RadixSort(size_t arr[], size_t size)
{
   int digit = 0;
   size_t max = 0;
   size_t min = 0;
   size_t longest_num = 0;

   assert(NULL != arr);

   max = GetMax(arr, size, CountGetKey, 0);
   min = GetMin(arr, size, CountGetKey, 0);
   longest_num = MAX(abs(max), abs(min));

   for (digit = 1; longest_num / digit > 0; digit *= 10)
   {
       CountSortByKey(arr, size, RadixGetKey, digit);
   }

}




