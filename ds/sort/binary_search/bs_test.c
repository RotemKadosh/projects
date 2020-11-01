#include <stdlib.h>
#include <stdio.h>
#include "../../utils/test.h"
#include "bs.h"

int cmpfunc (const void *data, const void *data_to_compare)
{
    return (*(int *)data - *(int *)data_to_compare);
}


test_status_t BinarySearchTest()
{
    int *return1 = NULL;
    int *return2 = NULL;
    
    int arr[] ={1, 5, 6, 7, 8, 11, 45, 51, 53, 67, 68, 100};
    int target = 51;
    int target2 = 52;
    return1 = BinarySearchRecursive(arr, cmpfunc, (void *)&target, 12, 4);
    return2 = BinarySearchRecursive(arr, cmpfunc, (void *)&target2, 12, 4);        

    REQUIRE(51 == *return1);
    REQUIRE(NULL == return2);

    target = 1;
    target2 = 100;
    return1 = BinarySearchRecursive(arr, cmpfunc, (void *)&target, 12, 4);
    return2 = BinarySearchRecursive(arr, cmpfunc, (void *)&target2, 12, 4);
    REQUIRE(1 == *return1);
    REQUIRE(100 == *return2);

    target = 100;
    target2 = -3;
    return1 = BinarySearchRecursive(arr, cmpfunc, (void *)&target, 12, 4);
    return2 = BinarySearchRecursive(arr, cmpfunc, (void *)&target2, 12, 4);
    REQUIRE(100 == *return1);
    REQUIRE(NULL == return2);

    return PASSED;
}


test_status_t ItBinarySearchTest()
{

    int arr[] ={1, 5, 6, 7, 8, 11, 45, 51, 53, 67, 68, 100};
    int target = 51;
    int target2 = 52;
    int *return1 = BinarySearchIterative(arr, cmpfunc, (void *)&target, 12, 4);
    int *return2 = BinarySearchIterative(arr, cmpfunc, (void *)&target2, 12, 4);        

    REQUIRE(51 == *return1);
    REQUIRE(NULL == return2);

    target = 5;
    target2 = 105;
    return1 = BinarySearchIterative(arr, cmpfunc, (void *)&target, 12, 4);
    return2 = BinarySearchIterative(arr, cmpfunc, (void *)&target2, 12, 4);
    REQUIRE(5 == *return1);
    REQUIRE(NULL == return2);

    target = 100;
    target2 = -3;
    return1 = BinarySearchIterative(arr, cmpfunc, (void *)&target, 12, 4);
    return2 = BinarySearchIterative(arr, cmpfunc, (void *)&target2, 12, 4);
    REQUIRE(100 == *return1);
    REQUIRE(NULL == return2);

    return PASSED;
}

int main()
{
    
    RUNTEST(BinarySearchTest);
    RUNTEST(ItBinarySearchTest);
    return 1;

}
