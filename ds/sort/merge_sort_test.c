#include <stdlib.h>
#include <time.h>
#include "../utils/test.h"
#include "merge.h"



test_status_t MergeSortTest(void);
test_status_t QSortTest(void);


int main()
{
    RUNTEST(MergeSortTest);
    RUNTEST(QSortTest);
    return 0; 
}


int cmpfunc(const void *a, const void *b)
{
   return (*(int *)a - *(int *)b);
}

test_status_t QSortTest(void)
{
    int i = 0;
    int arr[5000] = {0};
    int arr2[5000] = {0};
    clock_t start_sort, end_sort;
    clock_t start_qsort, end_qsort;
    srand(134);
    for (i = 0; i < 5000 ; ++i)
    {
        arr[i] = rand() ;
        arr2[i] = arr[i];
    }
    start_sort = clock();
    Qsort(arr, 5000,sizeof(int), &cmpfunc);
    end_sort = clock();

    start_qsort = clock();
    qsort(arr2, 5000, sizeof(int),&cmpfunc);
    end_qsort = clock();
    i = 0;
    while (i < 5000)
    {
        REQUIRE(arr[i] == arr2[i]);
        ++i;
    }
    REQUIRE(i == 5000);
    printf("clocks for Qsort = %d\n", (int)(end_sort - start_sort));
    printf("clocks for qsort = %d\n", (int)(end_qsort - start_qsort));
    return PASSED;
}

test_status_t MergeSortTest(void)
{
    int i = 0;
    int arr[5000] = {0};
    int arr2[5000] = {0};
    clock_t start_merge, end_merge;
    clock_t start_qsort, end_qsort;
    srand(134);
    for (i = 0; i < 5000 ; ++i)
    {
        arr[i] = (rand() % 10000) - 5000;
        arr2[i] = arr[i];
    }
    start_merge = clock();
    MergeSort(arr, 5000);
    end_merge = clock();

    start_qsort = clock();
    qsort(arr2, 5000, sizeof(int),&cmpfunc);
    end_qsort = clock();
    i = 0;
    while (i < 5000)
    {
        REQUIRE(arr[i] == arr2[i]);
        ++i;
    }
    REQUIRE(i == 5000);
    printf("clocks for merge sort = %d\n", (int)(end_merge - start_merge));
    printf("clocks for qsort = %d\n", (int)(end_qsort - start_qsort));

    return PASSED;
}




















