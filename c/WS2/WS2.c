#include <stdio.h>  /* for printf*/
#include <string.h> /*for strlen, strcmp*/
#include <assert.h> /*for assert*/
#include <stdlib.h> /*for malloc function*/
#define SUCCESS 0
#define FAIL 1


/*function declerations*/

int Swap (int *num1, int* num2);
int CopyArray (int arr_a[], int arr_b [], int size);
void PrintAddrs();
void Foo(int *ptr);
int SwapTwoSizeT (size_t *num1, size_t *num2);
int SwapTwoPtr (size_t **num1, size_t **num2);
size_t Strlen (const char *str);
int Strcmp (const char *str1,const char *str2);
int TestSwap();
int TestArrCopy();
int TestStrlen();
int TestStrcmp();
int TestSwapTwoPtr();

/*function definitions*/

int Swap (int *num1, int* num2)
{
	int temp;
	
	if (!num1 || !num2)
	{
		return FAIL;
	}
	
	temp = *num1;
	*num1 = *num2;
	*num2 = temp;
	return SUCCESS;
}
 
int CopyArray (int arr_a[], int arr_b[], int size)
{
	int i = 0; 
	
	if (!arr_a || !arr_b)
	{
		return FAIL;
	}
	
 	for(i = 0; i<size; i++)
 	{
 		arr_b[i] = arr_a[i];
	}
	
	return SUCCESS;
}

void PrintAddrs()
{
    static int s_i = 7; 
    int i = 7; 
    int *ptr = &i;  
    int *ptr2 = (int *)malloc(sizeof(int));    
   
  	printf("addres of s_i: %p\n",(void *)&s_i); 
   	printf("addres of i: %p\n",(void *)&i);
   	printf("address of ptr: %p adress pointed by ptr: %p\n",(void *)&ptr,(void *)ptr); 
   	printf("address of ptr2: %p adress pointed by ptr2: %p\n",(void *)&ptr2,(void *)ptr2);
    	
    free(ptr2);

    Foo(ptr);
}

void Foo(int *ptr)
{
     
   	printf("address of ptr from Foo: %p adress pointed by ptr: %p\n",(void *)&ptr,(void *)ptr);
}

int SwapTwoSizeT (size_t *num1, size_t *num2)
{
	size_t temp;
	if (!num1 || !num2)
	{
		return FAIL;
	}
	temp = *num1;
	*num1 = *num2;
	*num2 = temp;
	return SUCCESS;
}

int SwapTwoPtr (size_t **num1, size_t **num2)
{
	if (!num1 || !num2)
	{
		return FAIL;
	}
	SwapTwoSizeT((size_t *)num1,(size_t *)num2);
	return SUCCESS;
}


size_t Strlen (const char *str)
{
	const char *plc=str;
	assert(str);

	while (*str)
	{
		str++;
	}
	return (str - plc);
}

int Strcmp (const char *str1,const char *str2)
{	
	assert(str1 || str2);
	
	while(*str1 || *str2)
	{	
		if(*str1 == *str2)
		{
			str1++;
			str2++;
		}
		else
		{
			return(*str1 - *str2);
		}
	}
	return SUCCESS;
}


/*main*/

int main()
{
	TestSwap();
	TestArrCopy();
	PrintAddrs();
	TestSwapTwoPtr();
	TestStrlen();
	TestStrcmp();
	return 0;
	
}

/*tests*/

int TestSwap()
{
	int a, b, c, d, e;
	int test1, test2, test3;
	a = 4, b = 3, c = 2, d = 1, e = 5;
	Swap(&a,&d);
	Swap(&b,&c);
	Swap(&e,NULL);
	test1= (2 == b && 3 == c);
	test2= (1 == a && 4 == d);
	test3= (5 == e);
	if (test1 && test2 && test3)
	{
		printf("the swap function passed the tests\n");
		return SUCCESS;
	}
	else
	{
		printf("swap failed!, test1=%d, test2=%d, test3=%d\n",test1,test2,test3);;
		return FAIL;;
	}
	return SUCCESS;
}
	
int TestArrCopy()
{
	int arr_a[] = {1,2,3,4,5,6,7,8,9,10};
	int arr_b[sizeof(arr_a)/sizeof(arr_a[0])];
	int size = 0;
	int i = 0;
	
	size = sizeof(arr_a)/sizeof(arr_a[0]);
	CopyArray(arr_a,arr_b,size);
	
	for(i = 0; i<size; i++)
	{
		if(arr_a[i] != arr_b[i])
		{
			printf("ArrCopy failed! (arr_a[%d]= %d) != (arr_b[%d]= %d)\n",i,arr_a[i],i,arr_b[i]);
			return FAIL;
		}
	}
	printf("ArrCopy passed the test. the array has been copied\n");
	return SUCCESS;		
}

int TestSwapTwoPtr()
{
	size_t num1 = 123, num2 = 321;
	size_t *pt1 = &num1, *pt2 = &num2, *pt3 = &num1, *pt4 = &num2;
	int test1;
	SwapTwoPtr(&pt1,&pt2);
	test1= (pt3 == pt2 && pt4 == pt1);
	
	if (test1 )
	{
		printf("the SwapTwoPtr function passed the tests\n");
		return SUCCESS;
	}
	else
	{
		printf("SwapTwoPtr failed!, test1=%d\n",test1);
		return FAIL;
	}
	return SUCCESS;
}

int TestStrlen()
{
	const char *str1, *str2, *str3, *str4, *str5;
	int test1, test2, test3, test4, test5;
	
	str1 = "hello";
	str2 = "my name is rotem";
	str3 = "im 28 years old";
	str4 = "";
	str5 = "who are you?";
	
	test1 = (strlen(str1) == Strlen(str1));
	test2 = (strlen(str2) == Strlen(str2));
	test3 = (strlen(str3) == Strlen(str3));
	test4 = (strlen(str4) == Strlen(str4));
	test5 = (strlen(str5) == Strlen(str5));
	
	if (test1 && test2 && test3 && test4 && test5)
	{
		printf("the Strlen function passed the tests\n");
		return SUCCESS;
	}
	else
	{
		printf("Strlen failed!, test1=%d, test2=%d, test3=%d, test4=%d, test5=%d \n",test1,test2,test3,test4,test5);
		return FAIL;
	}
	return SUCCESS;
}

int TestStrcmp()
{
	const char *str1, *str2, *str3, *str4, *str6;
	int test1, test2, test3, test4;
	
	str1 = "hello";
	str2 = "HELLO";
	str3 = "abcde";
	str4 = "abcd";
	str6 = "abcdf";
		
	test1= (Strcmp(str1,str2) == strcmp(str1,str2));
	test2= (Strcmp(str4,str3) == strcmp(str4,str3));
	test3= (Strcmp(str1,str1) == strcmp(str1,str1));
	test4= (Strcmp(str3,str6) == strcmp(str3,str6));
	
	if (test1 && test2 && test3 && test4 )
	{
		printf("the Strcmp function passed the tests\n");
		return SUCCESS;
	}
	else
	{
		printf("Strcmp failed!, test1=%d, test2=%d, test3=%d, test4=%d \n",test1,test2,test3,test4);
		return FAIL;
	}
	return SUCCESS;
}	



