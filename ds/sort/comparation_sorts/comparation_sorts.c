#include <stddef.h> /*size_t*/
#include <ctype.h> /*ssize_t*/
#include <stdlib.h>/*malloc, free*/

typedef int (*GetKey_t)(int arr[], int runner, int exp);
static void Swap(int *num1 , int *num2);

/*---------service functions----------*/

static void Swap(int *num1 , int *num2)
{
    int temp = *num1;
    *num1 = *num2;
    *num2 = temp;
}
static int GetMax(int *arr , size_t size, GetKey_t getkey, int exp)
{
    int max = 0;
    size_t runner = 1;
    for(runner = 1; runner < size; ++runner)
    {
        if(getkey(arr, runner, exp) > getkey(arr, max, exp))
        {
            max = runner;
        }
    }
    return (getkey(arr, max, exp));
}
static int GetMin(int *arr , size_t size, GetKey_t getkey, int exp)
{
    int min = 0;
    size_t runner = 1;
    for(runner = 1; runner < size; ++runner)
    {
        if(getkey(arr, runner, exp) < getkey(arr, min, exp))
        {
            min = runner;
        }
    }
    return getkey(arr, min, exp);
}
static void InitCount(int *count ,int *arr ,size_t size,GetKey_t getkey, int exp ,int min)
{
    size_t runner = 0;
    for (runner = 0; runner < size; ++runner) 
        {
            count[ getkey(arr, runner, exp) - min ]++; 
        }
}
static void AccumCount(int *count, size_t range)
{
    size_t runner = 0;
    for (runner = 1; runner < range; ++runner)
    { 
        count[runner] += count[runner - 1]; 
    }
}
static void SetOutInOrder(int *arr, size_t size, int min,int *count, int *out, GetKey_t getkey, int exp)
{
    int runner = 0;
    for (runner = size - 1; runner >= 0; --runner) 
    { 
        out[count[getkey(arr, runner, exp) - min] - 1] = arr[runner]; 
        --count[getkey(arr, runner, exp) - min]; 
    } 
}
static void CopyOutToArr(int *arr, size_t size, int *out)
{
    size_t runner = 0;
    for (runner = 0; runner < size; ++runner)
    {
        arr[runner] = out[runner]; 
    } 
}
static int CountSortGetKey(int *arr, int runner, int exp)
{
    (void)exp;
    return arr[runner];
}
static int RadixGetKey(int *arr, int runner, int exp)
{
    return (arr[runner]/exp) % 10;
}
static void CountSortByKey(int *arr , size_t size , GetKey_t getkey, int exp) 
{ 
  
    int max = GetMax(arr, size, getkey, exp); 
    int min = GetMin(arr, size, getkey, exp); 
    
    size_t range = max - min + 1;

    int *count = calloc(range, sizeof(int) );
    int *out = calloc(size ,sizeof(int)); 
    if(count == NULL || out == NULL)
    {
        return;
    }

    InitCount(count, arr, size, getkey, exp, min);
    AccumCount(count, range);
    SetOutInOrder(arr, size, min, count, out, getkey, exp);
    CopyOutToArr(arr, size, out);
   
    free(count);
    free(out);
} 

/*---------Sort functions----------*/

void BubbleSort(int arr[], size_t size)
{
    size_t start = 0;
    size_t runner = 0;
    for (start = 0; start < size - 1; ++start)  
    {     
        for (runner = 0; runner < size - start - 1; ++runner)  
        {
            if (arr[runner] > arr[runner+1]) 
            {
                Swap(&arr[runner], &arr[runner + 1]); 
            }
        }
    }
} 

void SelectionSort(int arr[], size_t size)
{
    size_t idx_of_next_min = 0;
    size_t runner = 0;
    size_t current_min_idx = 0;
    
    for(idx_of_next_min = 0; idx_of_next_min < size; ++idx_of_next_min)
    { 
        current_min_idx = idx_of_next_min;
        for(runner = idx_of_next_min; runner < size; ++runner)
        {
            if(arr[runner] < arr[current_min_idx])
            {
                current_min_idx = runner;
            }
        }
        Swap(&arr[idx_of_next_min], &arr[current_min_idx]);
    }
}

void InsertionSort(int arr[], size_t size)
{
    size_t selection_idx = 0;
    int selection = 0;
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

void CountSort (int *arr , size_t size)
{
    CountSortByKey(arr, size, CountSortGetKey, 0);
}
 
void RadixSort(int arr[], size_t size)
{
    int max = GetMax(arr, size, CountSortGetKey, 0);
    int exp = 1;
    for (exp = 1; max / exp > 0; exp *= 10)
    {
        CountSortByKey(arr, size, RadixGetKey ,exp);
    }     
}