#include <stdio.h> /*printf*/

void IntToLong(int arr [], size_t size);
int CheckArr(int arr1[], int arr2 [] , size_t size);
void Test ();



void IntToLong(int arr [], size_t size)
{
	 unsigned int i = 0;
	for(i = 0 ; i < size; i += 2 )
	{
		arr[i] += arr[i + 1];
		arr[i + 1] = 0;
	}
}
int CheckArr(int arr1[], int arr2 [] , size_t size)
{
	unsigned int i = 0;
	for (i=0 ; i < size; i++)
	{
		if(arr1[i] != arr2[i])
		{
			return 0;
		}
	}
	return 1;
}

int main()
{
	Test();
	return 0;

}
void Test ()
{
	size_t s1 = 0, s2 = 0, s3 = 0, s4 = 0, s5 = 0;
	int test1 = 0, test2 = 0, test3 = 0, test4 = 0, test5 = 0;

	int  arr1[6] = {1 ,3 ,6 ,7, 8, 5};
	int check1[6] = {4, 0, 13, 0 ,13, 0};
	int arr2[4] = {5, 7, 3, 0 };
	int check2[4] = {12, 0, 3, 0};
	int arr3[4] = {0, 0, 0, 0 };
	int check3[4] = {0, 0, 0, 0};
	int arr4[2] = {-1 , 1};
	int check4[2] = {0 , 0};
	int arr5[6] = {-1, -4 , 5 ,6 ,-8 , 5};
	int check5[6] = {-5 , 0 , 11 ,0 , -3, 0 };
	
	s1= sizeof(arr1) / sizeof(arr1[0]);
	s2= sizeof(arr2) / sizeof(arr2[0]);
	s3= sizeof(arr3) / sizeof(arr3[0]);
	s4= sizeof(arr4) / sizeof(arr4[0]);
	s5= sizeof(arr5) / sizeof(arr5[0]);

	IntToLong(arr1, s1);
	IntToLong(arr2,  s2);
	IntToLong(arr3,  s3);
	IntToLong(arr4,  s4);
	IntToLong(arr5,  s5);


	test1 = CheckArr(arr1 ,check1 ,s1);
	test2 = CheckArr(arr2 ,check2 ,s2);
	test3 = CheckArr(arr3 ,check3 ,s3);
	test4 = CheckArr(arr4 ,check4 ,s4);
	test5 = CheckArr(arr5 ,check5 ,s5);

	if(test1 && test2 && test3 && test4 && test5)
	{
		printf("pass the test");
	}
	else 
	{
		printf( "faild, test1:%d  test2:%d test3:%d  test4:%d test5:%d \n",test1 , test2, test3, test4, test5);
	}
}