#include "test.h" /*require runtest*/

#include <time.h> /*clock_t, clock*/
#include <stdlib.h> /*srand, rand */

#include "comparation_sorts.h"
test_status_t BubbleSortTest(void);
int compar(const void *a,const void *b)
{
    return (*(int *)a - *(int *)b);
}

test_status_t BubbleSortTest()
{
    clock_t start = 0;
    clock_t end = 0;
    clock_t startq = 0;
    clock_t endq = 0;
    clock_t total = 0;
    clock_t total_qsort = 0;
    int a = 0;
    int i = 0;
    int arr[5000] = {0};
    int arrq[5000] = {0};
    srand(1234); 
    for(i = 0; i < 5000; i++)
    {
        a = (rand() % 10000) - 5000;
        arr[i] = a;
        arrq[i] = a;
    }
    start = clock();
    BubbleSort(arr, 5000);
    end = clock();
    total = (double)(end - start) / CLOCKS_PER_SEC;
    startq = clock();
    qsort(arrq, 5000, sizeof(int),compar);
    endq = clock();
    total_qsort = ((double)((double)(endq - startq) / CLOCKS_PER_SEC));
    i = 0;
    while (i < 5000)
    {
        REQUIRE(arr[i] == arrq[i]);
        i++;        
    }
    printf("clicks for bubble sort: %d\nclicks for qsort: %d\n",(int)(end - start), (int)(endq - startq));
    printf("secondes for bubble sort: %ld\nsecondes for qsort: %ld\n",total,total_qsort);
    
    return PASSED;
}
test_status_t SelectionSortTest()
{
    clock_t start = 0;
    clock_t end = 0;
    clock_t startq = 0;
    clock_t endq = 0;
    clock_t total = 0;
    clock_t total_qsort = 0;
    int a = 0;
    int i = 0;
    int arr[5000] = {0};
    int arrq[5000] = {0};
    srand(1234); 
    for(i = 0; i < 5000; i++)
    {
        a = (rand() % 10000) - 5000;
        arr[i] = a;
        arrq[i] = a;
    }
    start = clock();
    SelectionSort(arr, 5000);
    end = clock();
    total = (double)(end - start) / CLOCKS_PER_SEC;
    startq = clock();
    qsort(arrq, 5000, sizeof(int),compar);
    endq = clock();
    total_qsort = (double)(endq - startq) / CLOCKS_PER_SEC;
    i = 0;
    while (i < 5000)
    {
        REQUIRE(arr[i] == arrq[i]);
        
        i++;        
    }
    printf("clicks for SelectionSort: %d\nclicks for qsort: %d\n",(int)(end - start), (int)(endq - startq));
    printf("secondes for SelectionSort: %ld\nsecondes for qsort: %ld\n",total,total_qsort);
    
    return PASSED;
}
test_status_t InsertionSortTest()
{
    clock_t start = 0;
    clock_t end = 0;
    clock_t startq = 0;
    clock_t endq = 0;
    clock_t total = 0;
    clock_t total_qsort = 0;
    int a = 0;
    int i = 0;
    int arr[5000] = {0};
    int arrq[5000] = {0};
    srand(1234); 
    for(i = 0; i < 5000; i++)
    {
        a = rand();
        arr[i] = a;
        arrq[i] = a;
    }
    start = clock();
    InsertionSort(arr, 5000);
    end = clock();
    total = (double)(end - start) / CLOCKS_PER_SEC;
    startq = clock();
    qsort(arrq, 5000, sizeof(int),compar);
    endq = clock();
    total_qsort = (double)(endq - startq) / CLOCKS_PER_SEC;
    i = 0;
    while (i < 5000)
    {
        REQUIRE(arr[i] == arrq[i]);
        i++;        
    }
    printf("clicks for InsertionSort: %d\nclicks for qsort: %d\n",(int)(end - start), (int)(endq - startq));
    printf("secondes for InsertionSort: %ld\nsecondes for qsort: %ld\n",total,total_qsort);
    
    return PASSED;
}
test_status_t CountSortTest()
{
    clock_t start = 0;
    clock_t end = 0;
    clock_t startq = 0;
    clock_t endq = 0;
    clock_t total = 0;
    clock_t total_qsort = 0;
    int a = 0;
    int i = 0;
    int arr[5000] = {0};
    int arrq[5000] = {0};
    srand(1234); 
    for(i = 0; i < 5000; i++)
    {
        a = (rand() % 10000) - 5000;
        arr[i] = a;
        arrq[i] = a;
    }
    start = clock();
    CountSort(arr, 5000);
    end = clock();
    total = (double)(end - start) / CLOCKS_PER_SEC;
    startq = clock();
    qsort(arrq, 5000, sizeof(int),compar);
    endq = clock();
    total_qsort = (double)(endq - startq) / CLOCKS_PER_SEC;
    i = 0;
    while (i < 5000)
    {
        REQUIRE(arr[i] == arrq[i]);
        i++;        
    }
    printf("clicks for CountSort: %d\nclicks for qsort: %d\n",(int)(end - start), (int)(endq - startq));
    printf("secondes for CountSort: %ld\nsecondes for qsort: %ld\n",total,total_qsort);
    
    return PASSED;
}

test_status_t RadixSortTest()
{
    clock_t start = 0;
    clock_t end = 0;
    clock_t startq = 0;
    clock_t endq = 0;
    clock_t total = 0;
    clock_t total_qsort = 0;
    int a = 0;
    int i = 0;
    int arr[5000] = {0};
    int arrq[5000] = {0};
    srand(1234); 
    for(i = 0; i < 5000; i++)
    {
        a = (rand() % 10000) - 5000;
        arr[i] = a;
        arrq[i] = a;
    }
    start = clock();
    RadixSort(arr, 5000);
    end = clock();
    total = (double)(end - start) / CLOCKS_PER_SEC;
    startq = clock();
    qsort(arrq, 5000, sizeof(int),compar);
    endq = clock();
    total_qsort = (double)(endq - startq) / CLOCKS_PER_SEC;
    i = 0;
    while (i < 5000)
    {
        REQUIRE(arr[i] == arrq[i]);
        i++;        
    }
    printf("clicks for CountSort: %d\nclicks for qsort: %d\n",(int)(end - start), (int)(endq - startq));
    printf("secondes for CountSort: %ld\nsecondes for qsort: %ld\n",total,total_qsort);
    
    return PASSED;
}

int main(void)
{
    RUNTEST(BubbleSortTest);
    RUNTEST(SelectionSortTest);
    RUNTEST(InsertionSortTest);
    RUNTEST(CountSortTest);
    RUNTEST(RadixSortTest);
    return 0;
}