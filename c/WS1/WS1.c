#include<stdio.h>



/*function declerations*/

void PrintHelloHex();/*WS1.EX3 - function to print string as hex number*/
float Exponential(int n);/*WS1.EX4 - function to calculate 10^n*/
int FlipInt(int num);/*WS1.EX5	- function to flip intger*/
void Swap (int *num1, int *num2);/* WS1.EX6 - function to swap to intigers*/
int TestExponential();
int TestFlipInt();
int TestSwap();


/*function definitions*/


void PrintHelloHex() 
{
	const char *hex_hello = "\x48\x65\x6c\x6c\x6f\x20\x57\x6f\x72\x6c\x64\x21";
	printf("%s\n",hex_hello);	
}	

float Exponential(int n) 
{	
	float base;
	float result;
	
	if (n>=38)
	{
		printf("n is to large\n");
		return -1;
	}
	base=10.0;
	result=1.0;

	if (n<0)
	{
		base=0.1;
		n*=-1;
	}

	while (n>0)
	{
		result*=base;
		n--;
	}
	return result;
}

int FlipInt(int num) 
{
	int remainder;
	int revers;
	
	remainder=num%10;
	revers=0;

	while (num)
	{
		remainder=num%10;
		revers*=10;
		revers+=remainder;
		num/=10;
	}
	return revers;
}

void Swap(int *num1, int *num2) 
{
	int temp;

	if (NULL==num1 || NULL==num2)
	{
		return;
	}

	temp=*num1;
	*num1=*num2;
	*num2=temp;
}

	
/*main function*/
	
int main()
{
	PrintHelloHex();
	TestExponential();
	TestFlipInt();
	TestSwap();
	return 0;
}

/*tests*/


int TestExponential()
{
	int test1, test2, test3, test4;
	
	test1=(1.0==Exponential(0));
	test2=(1000.0==Exponential(3));
	test3=(0.01-Exponential(-2)<0.00000001);
	test4=(-1==Exponential(50));
	
	
	if (test1 && test2 && test3 && test4)
	{
		printf("the exponential function passed the tests\n");
		return 0;
	}

	else
	{
		printf("exponential failed!, test1=%d, test2=%d, test3=%d, test4=%d\n",test1,test2,test3, test4);
		return -1;
	}
}

int TestFlipInt()
{
	int test1, test2, test3, test4, test5;
	
	test1=(1234==FlipInt(4321));
	test2=(1==FlipInt(1000));
	test3=(3042==FlipInt(2403));
	test4=(11111==FlipInt(11111));
	test5=((-123)==FlipInt(-321));
	
	
	if (test1 && test2 && test3 && test4 && test5)
	{
		printf("the FlipInt function passed the tests\n");
		return 0;
	}

	else
	{
		printf("FlipInt failed!, test1=%d, test2=%d, test3=%d, test4=%d, test5=%d\n",test1,test2,test3,test4,test5);
		return -1;
	}
}

int TestSwap()
{
	int a, b, c, d, e;
	int test1, test2, test3;
	a=4, b=3, c=2, d=1, e=5;
	Swap(&a,&d);
	Swap(&b,&c);
	Swap(&e,NULL);
	test1=(2==b && 3==c);
	test2=(1==a && 4==d);
	test3=(5==e);
	if (test1 && test2 && test3)
	{
		printf("the swap function passed the tests\n");
		return 0;
	}
	else
	{
		printf("swap failed!, test1=%d, test2=%d, test3=%d\n",test1,test2,test3);
		return -1;
	}
}







		
