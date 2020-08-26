#include <stddef.h> /* size_t */
#include <string.h> /*strcmp*/
#include <stdio.h> /* printf */
#include "bit_array.h"

#define ALL_ONE_MASK (0xFFFFFFFFFFFFFFFF)
#define ALL_ZERO_MASK (0x0000000000000000) 
#define ALL_ZERO_STRING ("0000000000000000000000000000000000000000000000000000000000000000")
#define ALL_ONE_STRING ("1111111111111111111111111111111111111111111111111111111111111111")
#define NUM_OF_BITS (63) 

void TestBitsArrToString();
void TestBitsArrSetAll();
void TestBitsArrResetAll();
void TestBitsArrFlip();
void TestBitsArrSetOn();
void TestBitsArrSetOff();

int main()
{
	TestBitsArrToString();
	TestBitsArrSetAll();
	TestBitsArrResetAll();
	TestBitsArrFlip();
	TestBitsArrSetOn();
	TestBitsArrSetOff();
	return 0;
}


void TestBitsArrToString()
{

    int test1 = 0, test2 = 0, test3 = 0, test4 = 0;

    char buffer1[65] = {0};
    char buffer2[65] = {0};
    char buffer3[65] = {0};
    char buffer4[65] = {0};


    test1 = (0 == strcmp("1111111111111111111111111111111111111111111111111111111110000001", BitsArrToString(-127, buffer1)));
    test2 = (0 == strcmp("0000000000000000000000000000000000000000000000000000000000000111", BitsArrToString(7, buffer2)));
    test3 = (0 == strcmp("1111111111111111111111111111111111111111111111111111111111111111", BitsArrToString(-1, buffer3)));
    test4 = (0 == strcmp("0000000000000000000000000000000010000000000000000000000000000000", BitsArrToString(2147483648, buffer4)));



    if (test1 && test2 && test3 && test4)
    {
        printf("BitsArrToString passed the test\n");
    }
    else
    {
        printf("BitsArrToString failed\ntest1: %d\ntest2: %d\ntest3: %d\ntest4: %d\n", test1, test2, test3, test4);
    }
}

void TestBitsArrSetAll()
{
	int test1 = 0, test2 = 0, test3 = 0, test4 = 0;

	bit_array_t arr1 = 893771;
	bit_array_t arr2 = 0;
	bit_array_t arr3 = 1;
	bit_array_t arr4 = 318798137;

	test1 = ((bit_array_t)-1 == BitsArrSetAll(arr1));
	test2 = ((bit_array_t)-1 == BitsArrSetAll(arr2));
	test3 = ((bit_array_t)-1 == BitsArrSetAll(arr3));
	test4 = ((bit_array_t)-1 == BitsArrSetAll(arr4));

  	if (test1 && test2 && test3 && test4)
    {
        printf("BitsArrSetAll passed the test\n");
    }
    else
    {
        printf("BitsArrSetAll failed\ntest1: %d\ntest2: %d\ntest3: %d\ntest4: %d\n", test1, test2, test3, test4);
    }

}
void TestBitsArrResetAll()
{
	int test1 = 0, test2 = 0, test3 = 0, test4 = 0;

	bit_array_t arr1 = 893771;
	bit_array_t arr2 = 0;
	bit_array_t arr3 = 1;
	bit_array_t arr4 = 318798137;

	test1 = (0 == BitsArrResetAll(arr1));
	test2 = (0 == BitsArrResetAll(arr2));
	test3 = (0 == BitsArrResetAll(arr3));
	test4 = (0 == BitsArrResetAll(arr4));

  	if (test1 && test2 && test3 && test4)
    {
        printf("BitsArrResetAll passed the test\n");
    }
    else
    {
        printf("BitsArrResetAll failed\ntest1: %d\ntest2: %d\ntest3: %d\ntest4: %d\n", test1, test2, test3, test4);
    }
}
void TestBitsArrFlip()
{

    int test1 = 0, test2 = 0, test3 = 0, test4 = 0;

    char buffer1[65] = {0};
    char buffer2[65] = {0};
    char buffer3[65] = {0};
    char buffer4[65] = {0};


    test1 = (0 == strcmp("1111111111111111111111111111111111111111111111111111111111111111", BitsArrToString(BitsArrFlip(0), buffer1) ));
    test2 = (0 == strcmp("1111111111111111111111111111111111111111111111111111111111111000", BitsArrToString(BitsArrFlip(7), buffer2) ));
    test3 = (0 == strcmp("0000000000000000000000000000000000000000000000000000000000000000", BitsArrToString(BitsArrFlip(-1), buffer3) ));
    test4 = (0 == strcmp("1111111111111111111111111111111101111111111111111111111111111111", BitsArrToString(BitsArrFlip(2147483648), buffer4)));



    if (test1 && test2 && test3 && test4)
    {
        printf("BitsArrFlip passed the test\n");
    }
    else
    {
        printf("BitsArrFlip failed\ntest1: %d\ntest2: %d\ntest3: %d\ntest4: %d\n", test1, test2, test3, test4);
    }
}
void TestBitsArrSetOn()
{

    int test1 = 0, test2 = 0, test3 = 0, test4 = 0;

    char buffer1[65] = {0};
    char buffer2[65] = {0};
    char buffer3[65] = {0};
    char buffer4[65] = {0};


    test1 = (0 == strcmp("0000000000000000000000000000000000000000000000000000000010000000", BitsArrToString(BitsArrSetOn((bit_array_t)0 , 7), buffer1) ));
    test2 = (0 == strcmp("1000000000000000000000000000000000000000000000000000000000000000", BitsArrToString(BitsArrSetOn((bit_array_t)0 , 63), buffer2) ));
    test3 = (0 == strcmp("1111111111111111111111111111111111111111111111111111111111111111", BitsArrToString(BitsArrSetOn((bit_array_t)-1, 0), buffer3) ));
    test4 = (0 == strcmp("0000000000000000000000000000000010000000000000000000000000000010", BitsArrToString(BitsArrSetOn((bit_array_t)2147483648, 1), buffer4)));



    if (test1 && test2 && test3 && test4)
    {
        printf("BitsArrSetOn passed the test\n");
    }
    else
    {
        printf("BitsArrSetOn failed\ntest1: %d\ntest2: %d\ntest3: %d\ntest4: %d\n", test1, test2, test3, test4);
    }
}
void TestBitsArrSetOff()
{

    int test1 = 0, test2 = 0, test3 = 0, test4 = 0;

    char buffer1[65] = {0};
    char buffer2[65] = {0};
    char buffer3[65] = {0};
    char buffer4[65] = {0};


    test1 = (0 == strcmp("0000000000000000000000000000000000000000000000000000000000000000", BitsArrToString(BitsArrSetOff((bit_array_t)0 ,7), buffer1) ));
    test2 = (0 == strcmp("0000000000000000000000000000000000000000000000000000000000000011", BitsArrToString(BitsArrSetOff((bit_array_t)7 ,2), buffer2) ));
    test3 = (0 == strcmp("1111111111111111111111111111111111111111111111111111111111111110", BitsArrToString(BitsArrSetOff((bit_array_t)-1, 0), buffer3) ));
    test4 = (0 == strcmp("0000000000000000000000000000000000000000000000000000000000000000", BitsArrToString(BitsArrSetOff((bit_array_t)2147483648, 31), buffer4)));

    if (test1 && test2 && test3 && test4)
    {
        printf("BitsArrSetOff passed the test\n");
    }
    else
    {
        printf("BitsArrSetOff failed\ntest1: %d\ntest2: %d\ntest3: %d\ntest4: %d\n", test1, test2, test3, test4);
    }
}