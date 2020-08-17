#include <stdio.h> /*ptintf */
#include <assert.h> /*assert*/
#include "ws6.h"

#define TRUE (1)
#define FALSE (0) 

void TestPow2();
void TestIsPow();
void TestIsPowLoop();
void TestAddOne();
void TestAddOneLoop();
void TestPrint3BitsOn();
void TestByteMirror();
void TestByteMirrorLoop();
void TestIs2And6BitsOn();
void TestIs2Or6BitsOn();
void TestSwap3And5Bits();
void TestFindClosestDivisibleBy16();
void TestSwapWithOnly2Var();
void TestCountSetBits();
void TestCountSetBitsLoop();
void PrintFloatAnalize();

int main()
{
	TestPow2();
	TestIsPow();
	TestIsPowLoop();
	TestAddOne();
	TestAddOneLoop();
	TestPrint3BitsOn();
	TestByteMirror();
	TestByteMirrorLoop();
	TestIs2And6BitsOn();
	TestIs2Or6BitsOn();
	TestSwap3And5Bits();
	TestFindClosestDivisibleBy16();
	TestSwapWithOnly2Var();
	TestCountSetBits();
	TestCountSetBitsLoop();
	PrintFloatAnalize();

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
void TestAddOne()
{
	int test1 = 0, test2 = 0, test3 = 0, test4 = 0;
	test1 = (5 == AddOne(4));
	test2 = (33 == AddOne(32));
	test3 = (-6 == AddOne(-7));
	test4 = (1 == AddOne(0));

	if(test1 && test2 && test3 && test4)
	{
		printf("AddOne passed\n");
	}
	else 
	{
		printf("AddOne failed, test1: %d, test2: %d, test3: %d, test4: %d\n",test1 ,test2 ,test3 ,test4 );
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
void TestByteMirror()
{
	int test1 = 0, test2 = 0, test3 = 0, test4 = 0;
	test1 = (134 == (int)ByteMirror(((unsigned char)'a')));
	test2 = (130 == (int)ByteMirror(((unsigned char)'A')));
	test3 = (172 == (int)ByteMirror(((unsigned char)'5')));
	test4 = (4   == (int)ByteMirror(((unsigned char)' ')));
	if(test1 && test2 && test3 && test4)
	{
		printf("ByteMirror passed\n");
	}
	else 
	{
		printf("ByteMirror failed, test1: %d, test2: %d, test3: %d, test4: %d\n",test1 ,test2 ,test3 ,test4 );
	}	
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
void TestSwap3And5Bits()
{
	int test1 = 0, test2 = 0, test3 = 0, test4 = 0;
	test1 = (52 == (int)Swap3And5Bits((unsigned char)'4'));
	test2 = (56 == (int)Swap3And5Bits((unsigned char)','));
	test3 = (91 == (int)Swap3And5Bits((unsigned char)'O'));
	test4 = (78 == (int)Swap3And5Bits((unsigned char)'Z'));

	if(test1 && test2 && test3 && test4)
	{
		printf("Swap3And5Bits passed\n");
	}
	else 
	{
		printf("Swap3And5Bits failed, test1: %d, test2: %d, test3: %d, test4: %d\n",test1 ,test2 ,test3 ,test4 );
	}
}
void TestFindClosestDivisibleBy16()
{
	int test1 = 0, test2 = 0, test3 = 0, test4 = 0;
	test1 = (32 == (int)FindClosestDivisibleBy16(33));
	test2 = (16 == (int)FindClosestDivisibleBy16(22));
	test3 = (16 == (int)FindClosestDivisibleBy16(17));
	test4 = (9600 == (int)FindClosestDivisibleBy16(9601));

	if(test1 && test2 && test3 && test4)
	{
		printf("FindClosestDivisibleBy16 passed\n");
	}
	else 
	{
		printf("FindClosestDivisibleBy16 failed, test1: %d, test2: %d, test3: %d, test4: %d\n",test1 ,test2 ,test3 ,test4 );
	}
}

void TestSwapWithOnly2Var()
{
	int a, b, c, d, e, f;
	int test1, test2, test3;
	a = 4, b = 3, c = 2, d = 1, e = 5, f = 9 ;
	SwapWithOnly2Var(&a, &d);
	SwapWithOnly2Var(&b, &c);
	SwapWithOnly2Var(&e, &f);
	test1=(2 == b && 3 == c);
	test2=(1 == a && 4 == d);
	test3=(9 == e && 5 == f);
	if (test1 && test2 && test3)
	{
		printf("SwapWithOnly2Var passed \n");
	}
	else
	{
		printf("swap SwapWithOnly2Var!, test1=%d, test2=%d, test3=%d\n",test1,test2,test3);
	}
}
void TestCountSetBits()
{
	int test1 = 0, test2 = 0, test3 = 0, test4 = 0;
	test1 = (2 == CountSetBits(36));
	test2 = (1 == CountSetBits(2));
	test3 = (6 == CountSetBits(-7));
	test4 = (5 == CountSetBits(-8));

	if(test1 && test2 && test3 && test4)
	{
		printf("CountSetBits passed\n");
	}
	else 
	{
		printf("CountSetBits failed, test1: %d, test2: %d, test3: %d, test4: %d\n",test1 ,test2 ,test3 ,test4 );
	}
}
void TestCountSetBitsLoop()
{
	int test1 = 0, test2 = 0, test3 = 0, test4 = 0;
	test1 = (2 == CountSetBitsLoop(36));
	test2 = (1 == CountSetBitsLoop(2));
	test3 = (6 == CountSetBitsLoop(-7));
	test4 = (5 == CountSetBitsLoop(-8));

	if(test1 && test2 && test3 && test4)
	{
		printf("CountSetBitsLoop passed\n");
	}
	else 
	{
		printf("CountSetBitsLoop failed, test1: %d, test2: %d, test3: %d, test4: %d\n",test1 ,test2 ,test3 ,test4 );
	}
}
void PrintFloatAnalize()
{
	float f = 1726.6;
	FloatAnalize(f);
}
