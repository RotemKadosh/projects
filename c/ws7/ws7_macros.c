#include <stdio.h> /*printf*/

#define MAX2(a, b) (a > b ? a :b)
#define MAX3(a, b, c) (a > b) ? ( a > c ? a : c ) : ( b > c ? b : c )
#define SIZEOF_VAR(var) ((size_t)(&(var) + 1) - (size_t)(&(var))) 

#define SIZEOF_TYPE(X) (size_t)(((X*) 0 ) + 1 )

void TestMaxMacros() ;

void TestMaxMacros()
{
	int a = 1, b = 2, c = 3, d = 4;
	int test1 = 0, test2 = 0, test3 = 0 ;

	test1 = (c == MAX2(a, c));
	test2 = (d == MAX3(a, c, d));
	test3 = (b == MAX3(a, b, c));

	if (test1 && test2 && test3)
	{
		printf("MAX2 and MAX3 passed\n");
	}
	else
	{
		printf("failed. test1: %d, test2: %d, test3: %d \n", test1, test2, test3);
	}
}



void TestSizeVarMacro()
{
	int a = 1;
	int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 9};
	double arr2[5] = {1.0, 2.3, 4.5, 6.7, 8.9};

	int test1 = 0, test2 = 0, test3 = 0 ;
	

	test1 = (4 == SIZEOF_VAR(a));
	test2 = (40 == SIZEOF_VAR(arr));
	test3 = (40 == SIZEOF_VAR(arr2));

	if (test1 && test2 && test3)
	{
		printf("SIZEOF_VAR passed\n");
	}
	else
	{
		printf("SIZEOF_VAR failed. test1: %d, test2: %d, test3: %d \n", test1, test2, test3);
	}
}
void TestSizeTypeMacro()
{
	int test1 = 0, test2 = 0, test3 = 0 ;

	test1 = (4 == SIZEOF_TYPE(int));
	test2 = (1 == SIZEOF_TYPE(char));
	test3 = (8 == SIZEOF_TYPE(double));

	if (test1 && test2 && test3)
	{
		printf("SIZEOF_TYPE passed\n");
	}
	else
	{
		printf("SIZEOF_TYPE failed. test1: %d, test2: %d, test3: %d \n", test1, test2, test3);
	}
}

int main()
{
	TestMaxMacros();
	TestSizeVarMacro();
	TestSizeTypeMacro();
	return 0;
}