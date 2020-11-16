#include <stddef.h> /* size_t */
#include <string.h> /*strcmp*/
#include <stdio.h> /* printf */
#include "bit_array.h"
#define NUM_OF_BITS (63) 

static void TestBitsArrToString();
static void TestBitsArrSetAll();
static void TestBitsArrResetAll();
static void TestBitsArrFlip();
static void TestBitsArrSetOn();
static void TestBitsArrSetOff();
static void TestBitsArrGetVal();
static void TestBitsArrSetBit();
static void TestBitsArrCountOn();
static void TestBitsArrCountOff();
static void TestBitsArrMirror();
static void TestBitsArrRotR();
static void TestBitsArrRotL();
static void TestBitsArrMirrorLut();
static void TestBitsArrCountOnLut();

size_t BitsArrCountOnLut(bit_array_t arr);
bit_array_t BitsArrMirrorLut(bit_array_t arr);


int main()
{
    /*
	TestBitsArrToString();
	TestBitsArrSetAll();
	TestBitsArrResetAll();
	TestBitsArrFlip();
	TestBitsArrSetOn();
	TestBitsArrSetOff();
	TestBitsArrGetVal();
	TestBitsArrSetBit();
	TestBitsArrCountOn();
	TestBitsArrCountOff();
	TestBitsArrMirror();
    TestBitsArrRotR();
    TestBitsArrRotL();
    TestBitsArrMirrorLut();
    TestBitsArrCountOnLut();
    */
    char *p = "lalala";
    char arr[10] = "lalala";
    ++p;

    memset()
 
	return 0;
}


static void TestBitsArrToString()
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
static void TestBitsArrSetAll()
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
static void TestBitsArrResetAll()
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
static void TestBitsArrFlip()
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
static void TestBitsArrSetOn()
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
static void TestBitsArrSetOff()
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
static void TestBitsArrGetVal()
{

    int test1 = 0, test2 = 0, test3 = 0, test4 = 0;

    test1 = (0 == BitsArrGetVal((bit_array_t)0 ,7));
    test2 = (1 == BitsArrGetVal((bit_array_t)7 ,2));
    test3 = (1 == BitsArrGetVal((bit_array_t)-1, 0));
    test4 = (1 == BitsArrGetVal((bit_array_t)2147483648, 31));

    if (test1 && test2 && test3 && test4)
    {
        printf("BitsArrGetVal passed the test\n");
    }
    else
    {
        printf("BitsArrGetVal failed\ntest1: %d\ntest2: %d\ntest3: %d\ntest4: %d\n", test1, test2, test3, test4);
    }
}
static void TestBitsArrSetBit()
{

    int test1 = 0, test2 = 0, test3 = 0, test4 = 0;

    char buffer1[65] = {0};
    char buffer2[65] = {0};
    char buffer3[65] = {0};
    char buffer4[65] = {0};


    test1 = (0 == strcmp("0000000000000000000000000000000000000000000000000000000000000000", BitsArrToString(BitsArrSetBit((bit_array_t)0, 7 ,0), buffer1) ));
    test2 = (0 == strcmp("0000000000000000000000000000000000000000000000000000000000000011", BitsArrToString(BitsArrSetBit((bit_array_t)7, 2 ,0), buffer2) ));
  	test3 = (0 == strcmp("1111111111111111111111111111111111111111111111111111111111111111", BitsArrToString(BitsArrSetBit((bit_array_t)-1, 0 ,1), buffer3) ));
    test4 = (0 == strcmp("0000000000000000000000000000000010000000000000000000000000000010", BitsArrToString(BitsArrSetBit((bit_array_t)2147483648, 1, 1), buffer4)));


    if (test1 && test2 && test3 && test4)
    {
        printf("BitsArrSetBit passed the test\n");
    }
    else
    {
        printf("BitsArrSetBit failed\ntest1: %d\ntest2: %d\ntest3: %d\ntest4: %d\n", test1, test2, test3, test4);
    }
}
static void TestBitsArrCountOn()
{

    int test1 = 0, test2 = 0, test3 = 0, test4 = 0;

    test1 = (0 == BitsArrCountOn((bit_array_t)0 ));
    test2 = (3 == BitsArrCountOn((bit_array_t)7 ));
    test3 = (64 == BitsArrCountOn((bit_array_t)-1));
    test4 = (1 == BitsArrCountOn((bit_array_t)2147483648));

    if (test1 && test2 && test3 && test4)
    {
        printf("BitsArrCountOn passed the test\n");
    }
    else
    {
        printf("BitsArrCountOn failed\ntest1: %d\ntest2: %d\ntest3: %d\ntest4: %d\n", test1, test2, test3, test4);
    }
}
static void TestBitsArrCountOff()
{

    int test1 = 0, test2 = 0, test3 = 0, test4 = 0;

    test1 = (64 == BitsArrCountOff((bit_array_t)0 ));
    test2 = (61 == BitsArrCountOff((bit_array_t)7 ));
    test3 = (0 == BitsArrCountOff((bit_array_t)-1));
    test4 = (63 == BitsArrCountOff((bit_array_t)2147483648));

    if (test1 && test2 && test3 && test4)
    {
        printf("BitsArrCountOff passed the test\n");
    }
    else
    {
        printf("BitsArrCountOff failed\ntest1: %d\ntest2: %d\ntest3: %d\ntest4: %d\n", test1, test2, test3, test4);
    }
}
static void TestBitsArrMirror()
{

    int test1 = 0, test2 = 0, test3 = 0, test4 = 0;

    char buffer1[65] = {0};
    char buffer2[65] = {0};
    char buffer3[65] = {0};
    char buffer4[65] = {0};



    test1 = (0 == strcmp("1000000000000000000000000000000000000000000000000000000000000000", BitsArrToString(BitsArrMirror(1), buffer1) ));
    test2 = (0 == strcmp("1110000000000000000000000000000000000000000000000000000000000000", BitsArrToString(BitsArrMirror(7), buffer2) ));
    test3 = (0 == strcmp("0110000000000000000000000000000000000000000000000000000000000000", BitsArrToString(BitsArrMirror(6), buffer3) ));
    test4 = (0 == strcmp("0000000000000001000000000000000000000000000000000000000000000000", BitsArrToString(BitsArrMirror(32768), buffer4)));

    if (test1 && test2 && test3 && test4)
    {
        printf("BitsArrMirror passed the test\n");
    }
    else
    {
        printf("BitsArrMirror failed\ntest1: %d\ntest2: %d\ntest3: %d\ntest4: %d\n", test1, test2, test3, test4);
    }
}
static void TestBitsArrRotR()
{

    int test1 = 0, test2 = 0, test3 = 0, test4 = 0;

    char buffer1[65] = {0};
    char buffer2[65] = {0};
    char buffer3[65] = {0};
    char buffer4[65] = {0};



    test1 = (0 == strcmp("1000000000000000000000000000000000000000000000000000000000000000", BitsArrToString(BitsArrRotR(1, 1), buffer1) ));
    test2 = (0 == strcmp("1110000000000000000000000000000000000000000000000000000000000000", BitsArrToString(BitsArrRotR(7, 3), buffer2) ));
    test3 = (0 == strcmp("0110000000000000000000000000000000000000000000000000000000000000", BitsArrToString(BitsArrRotR(6, 4), buffer3) ));
    test4 = (0 == strcmp("0000000000000001000000000000000000000000000000000000000000000000", BitsArrToString(BitsArrRotR(32768, 31), buffer4)));

    if (test1 && test2 && test3 && test4)
    {
        printf("BitsArrRotR passed the test\n");
    }
    else
    {
        printf("BitsArrRotR failed\ntest1: %d\ntest2: %d\ntest3: %d\ntest4: %d\n", test1, test2, test3, test4);
    }
}
static void TestBitsArrRotL()
{

    int test1 = 0, test2 = 0, test3 = 0, test4 = 0;

    char buffer1[65] = {0};
    char buffer2[65] = {0};
    char buffer3[65] = {0};
    char buffer4[65] = {0};



    test1 = (0 == strcmp("0000000000000000000000000000000000000000000000000000000000000010", BitsArrToString(BitsArrRotL(1, 1), buffer1) ));
    test2 = (0 == strcmp("0000000000000000000000000000000000000000000000000000000000111000", BitsArrToString(BitsArrRotL(7, 3), buffer2) ));
    test3 = (0 == strcmp("0000000000000000000000000000000000000000000000000000000001100000", BitsArrToString(BitsArrRotL(6, 4), buffer3) ));
    test4 = (0 == strcmp("1000000000000000000000000000000000000000000000000000000000000000", BitsArrToString(BitsArrRotL(32768, 48), buffer4)));

    if (test1 && test2 && test3 && test4)
    {
        printf("BitsArrRotL passed the test\n");
    }
    else
    {
        printf("BitsArrRotL failed\ntest1: %d\ntest2: %d\ntest3: %d\ntest4: %d\n", test1, test2, test3, test4);
    }
}
static void TestBitsArrMirrorLut()
{

    int test1 = 0, test2 = 0, test3 = 0, test4 = 0;

    char buffer1[65] = {0};
    char buffer2[65] = {0};
    char buffer3[65] = {0};
    char buffer4[65] = {0};



    test1 = (0 == strcmp("1000000000000000000000000000000000000000000000000000000000000000", BitsArrToString(BitsArrMirrorLut(1), buffer1) ));
    test2 = (0 == strcmp("1110000000000000000000000000000000000000000000000000000000000000", BitsArrToString(BitsArrMirrorLut(7), buffer2) ));
    test3 = (0 == strcmp("0110000000000000000000000000000000000000000000000000000000000000", BitsArrToString(BitsArrMirrorLut(6), buffer3) ));
    test4 = (0 == strcmp("0000000000000001000000000000000000000000000000000000000000000000", BitsArrToString(BitsArrMirrorLut(32768), buffer4)));

    if (test1 && test2 && test3 && test4)
    {
        printf("BitsArrMirrorLut passed the test\n");
    }
    else
    {
        printf("BitsArrMirrorLut failed\ntest1: %d\ntest2: %d\ntest3: %d\ntest4: %d\n", test1, test2, test3, test4);
    }
}
static void TestBitsArrCountOnLut()
{

    int test1 = 0, test2 = 0, test3 = 0, test4 = 0;

    test1 = (0 == BitsArrCountOnLut((bit_array_t)0 ));
    test2 = (3 == BitsArrCountOnLut((bit_array_t)7 ));
    test3 = (64 == BitsArrCountOnLut((bit_array_t)-1));
    test4 = (1 == BitsArrCountOnLut((bit_array_t)2147483648));

    if (test1 && test2 && test3 && test4)
    {
        printf("BitsArrCountOnLut passed the test\n");
    }
    else
    {
        printf("BitsArrCountOnLut failed\ntest1: %d\ntest2: %d\ntest3: %d\ntest4: %d\n", test1, test2, test3, test4);
    }
}