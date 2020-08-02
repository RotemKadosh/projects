#include<stdio.h>



/*function declerations*/

void printHelloHex();/*WS1.EX3 - function to print string as hex number*/
float exponential(int n);/*WS1.EX4 - function to calculate 10^n*/
int flipInt(int num);/*WS1.EX5	- function to flip intger*/
void swap (int *num1, int *num2);/* WS1.EX6 - function to swap to intigers*/
int testExponential();
int testFlipInt();
int testSwap();


/*function definitions*/


void printHelloHex() 
{
	const char *hex_hello = "\x48\x65\x6c\x6c\x6f\x20\x57\x6f\x72\x6c\x64\x21";
	printf("%s\n",hex_hello);	
}	

float exponential(int n) 
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

int flipInt(int num) 
{
	int reminder;
	int revers;
	
	reminder=num%10;
	revers=0;

	while (num)
	{
		reminder=num%10;
		revers*=10;
		revers+=reminder;
		num/=10;
	}
	return revers;
}

void swap (int *num1, int *num2) 
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
	printHelloHex();
	testExponential();
	testFlipInt();
	testSwap();
	return 0;
}

/*tests*/


int testExponential()
{
	int test1, test2, test3, test4;
	
	test1=(1.0==exponential(0));
	test2=(1000.0==exponential(3));
	test3=(0.01-exponential(-2)<0.00000001);
	test4=(-1==exponential(50));
	
	
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

int testFlipInt()
{
	int test1, test2, test3, test4, test5;
	
	test1=(1234==flipInt(4321));
	test2=(1==flipInt(1000));
	test3=(3042==flipInt(2403));
	test4=(11111==flipInt(11111));
	test5=((-123)==flipInt(-321));
	
	
	if (test1 && test2 && test3 && test4 && test5)
	{
		printf("the flipInt function passed the tests\n");
		return 0;
	}

	else
	{
		printf("flipInt failed!, test1=%d, test2=%d, test3=%d, test4=%d, test5=%d\n",test1,test2,test3,test4,test5);
		return -1;
	}
}

int testSwap()
{
	int a, b, c,d,e;
	int test1, test2, test3;
	a=4, b=3, c=2, d=1, e=5;
	swap(&a,&d);
	swap(&b,&c);
	swap(&e,NULL);
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







		
