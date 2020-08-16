#include <stdio.h> /*ptintf */
#include <assert.h> /*assert*/
#include "ws6.h"

#define TRUE (1)
#define FALSE (0) 

void TestPow2();
void TestIsPow();
void TestIsPowLoop();

void TestAddOneLoop();
void TestPrint3BitsOn();

void TestByteMirrorLoop();
void TestIs2And6BitsOn();
void TestIs2Or6BitsOn();

int main()
{
	TestPow2();
	TestIsPow();
	TestIsPowLoop();
	TestAddOneLoop();
	TestPrint3BitsOn();
	TestByteMirrorLoop();
	TestIs2And6BitsOn();
	TestIs2Or6BitsOn();
	return 0;
}
void TestPow2()
{
	int test1 = 0, test2 = 0, test3 = 0, test4 = 0;
	test1 = (96 == Pow2(3, 5));
	test2 = (5 == Pow2(5, 0));
	test3 = (0 == Pow2(0, 0));
	test4 = (200 == Pow2(100, 1));

	if(test1 && test2 && test3 && test4)
	{
		printf("Pow2 passed\n");
	}
	else 
	{
		printf("Pow2 failed, test1: %d, test2: %d, test3: %d, test4: %d\n",test1 ,test2 ,test3 ,test4 );
	}
}
void TestIsPow()
{
	int test1 = 0, test2 = 0, test3 = 0, test4 = 0;
	test1 = (TRUE == IsPow(4));
	test2 = (TRUE == IsPow(32));
	test3 = (FALSE == IsPow(7));
	test4 = (FALSE == IsPow(0));

	if(test1 && test2 && test3 && test4)
	{
		printf("IsPow passed\n");
	}
	else 
	{
		printf("IsPow failed, test1: %d, test2: %d, test3: %d, test4: %d\n",test1 ,test2 ,test3 ,test4 );
	}
}
void TestIsPowLoop()
{
	int test1 = 0, test2 = 0, test3 = 0, test4 = 0;
	test1 = (TRUE == IsPowLoop(4));
	test2 = (TRUE == IsPowLoop(32));
	test3 = (FALSE == IsPowLoop(7));
	test4 = (FALSE == IsPowLoop(0));

	if(test1 && test2 && test3 && test4)
	{
		printf("IsPowLoop passed\n");
	}
	else 
	{
		printf("IsPowLoop failed, test1: %d, test2: %d, test3: %d, test4: %d\n",test1 ,test2 ,test3 ,test4 );
	}
}
void TestAddOneLoop()
{
	int test1 = 0, test2 = 0, test3 = 0, test4 = 0;
	test1 = (5 == AddOneLoop(4));
	test2 = (33 == AddOneLoop(32));
	test3 = (-6 == AddOneLoop(-7));
	test4 = (1 == AddOneLoop(0));

	if(test1 && test2 && test3 && test4)
	{
		printf("AddOneLoop passed\n");
	}
	else 
	{
		printf("AddOneLoop failed, test1: %d, test2: %d, test3: %d, test4: %d\n",test1 ,test2 ,test3 ,test4 );
	}
}
void TestPrint3BitsOn()
{
	unsigned int arr[] = { 7, 8, 9, 10, 11, 13, 19, 21, 22};
	Print3BitsOn(arr, (size_t)9);
}
void TestByteMirrorLoop()
{
	int test1 = 0, test2 = 0, test3 = 0, test4 = 0;
	test1 = (134 == (int)ByteMirrorLoop((unsigned char)'a'));
	test2 = (130 == (int)ByteMirrorLoop((unsigned char)'A'));
	test3 = (172 == (int)ByteMirrorLoop((unsigned char)'5'));
	test4 = (4 == (int)ByteMirrorLoop((unsigned char)' '));

	if(test1 && test2 && test3 && test4)
	{
		printf("ByteMirrorLoop passed\n");
	}
	else 
	{
		printf("ByteMirrorLoop failed, test1: %d, test2: %d, test3: %d, test4: %d\n",test1 ,test2 ,test3 ,test4 );
	}
}
void TestIs2And6BitsOn()
{
	int test1 = 0, test2 = 0, test3 = 0, test4 = 0;
	test1 = (TRUE == Is2And6BitsOn(63));
	test2 = (TRUE == Is2And6BitsOn(55));
	test3 = (FALSE == Is2And6BitsOn(7));
	test4 = (FALSE == Is2And6BitsOn(0));

	if(test1 && test2 && test3 && test4)
	{
		printf("Is2And6BitsOn passed\n");
	}
	else 
	{
		printf("Is2And6BitsOn failed, test1: %d, test2: %d, test3: %d, test4: %d\n",test1 ,test2 ,test3 ,test4 );
	}
}
void TestIs2Or6BitsOn()
{
	int test1 = 0, test2 = 0, test3 = 0, test4 = 0;
	test1 = (TRUE == Is2Or6BitsOn(36));
	test2 = (TRUE == Is2Or6BitsOn(2));
	test3 = (FALSE == Is2Or6BitsOn(5));
	test4 = (FALSE == Is2Or6BitsOn(0));

	if(test1 && test2 && test3 && test4)
	{
		printf("Is2Or6BitsOn passed\n");
	}
	else 
	{
		printf("Is2Or6BitsOn failed, test1: %d, test2: %d, test3: %d, test4: %d\n",test1 ,test2 ,test3 ,test4 );
	}
}