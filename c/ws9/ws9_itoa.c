#include <stdio.h> /*printf*/
#include <stdlib.h> /*malloc, free, itoa*/
#include <string.h> /*strcmp*/
#include <math.h>/*pow*/
#define NULL_CHAR (1)
#define ASCII_GAP (48)
#define FALSE (0)
#define TRUE (1)

static int power(int base ,int exp); 
static size_t NumOfDigits(int num, int base);

static int ConvertCharToDig(const char *str);
static int IsDigitLegit(const char *str, int base );
static const char *MoveToStartAndCalcLen(const char *str, int *len, int base, int *minus_flag);

int Atoi(const char *str , int base);
char *Itoa(int value, char * str, int base);
static int TestAtoiBase10(const char *str);
static void TestItoa();
static void TestAtoi();
static void ThreeCharArr(char arr1[], size_t size1, char arr2[], size_t size2, char arr3[], size_t size3);


int main()
{
	
	char arr1[] = {'a', 'b', 'c', 'd'};
	char arr2[] = {'a', 'E', 'c', 'd'};
	char arr3[] = {'a', 'b', 'a', 'f'};
	ThreeCharArr(arr1, sizeof(arr1)/sizeof(arr1[0]), arr2, sizeof(arr2)/sizeof(arr2[0]),arr3, sizeof(arr3)/sizeof(arr3[0]));
	return 0;
}
static int power(int base ,int exp) 
{	
	int result = 1;

	while (0 < exp)
	{
		result *= base;
		exp--;

	}
	return result;
}
static size_t NumOfDigits(int num, int base)
{
	size_t dig = 0;

	do
	{
		++dig;
		num /= base;

	}while(num != 0);
	
	return dig;
}

char *Itoa(int value, char * str, int base)
{
	int digit = 0;
	char *str_start = str;
	int num_of_digit = NumOfDigits(value, base);
	if(0 == value)
	{
		*str = '0';
		++str;
		*str ='\0';
	}
	else if(0 > value)
	{

		*str = '-';
		++str;
		value *= -1;
	}

	str = str + num_of_digit ;
	*str = '\0';
	--str;

	while (0 < value)
	{	
		digit = value % base;
		*str = (unsigned char)((digit > 9) ? (digit-10) + 'A' : digit + '0');
		--str;
		value /= base;
	}
	return str_start;
} 
 
static void TestItoa()
{
	int n1 = 15, n2 = -85, n3 = 0;
	
	int test1 = 0, test2 = 0, test3 = 0;
	int test11 = 0, test22 = 0, test33 = 0;
	int test111 = 0, test222 = 0, test333 = 0;

	char *res1 = (char *)malloc(32);
	char *res2 = (char *)malloc(32);
	char *res3 = (char *)malloc(32);
	
	char *res11 = (char *)malloc(32);
	char *res22 = (char *)malloc(32);
	char *res33 = (char *)malloc(32);
	
	char *res111 = (char *)malloc(32);
	char *res222 = (char *)malloc(32);
	char *res333 = (char *)malloc(32);
	
	char *str1 = "15" ;
	char *str2 = "-85";
	char *str3 = "0";

	char *str11 = "1111" ;
	char *str22 = "-1010101";
	char *str33 = "0";

	char *str111 = "F" ;
	char *str222 = "-55";
	char *str333 = "0";

	

	if(NULL == res1 || NULL == res2 || NULL == res3
	|| NULL == res11 || NULL == res22 || NULL == res33
	|| NULL == res111 || NULL == res222 || NULL == res333 )
	{
		return;
	}
	
	res1 = Itoa(n1, res1, 10);
	res2 = Itoa(n2, res2, 10);
	res3 = Itoa(n3, res3, 10);

	res11 = Itoa(n1, res11, 2);
	res22 = Itoa(n2, res22, 2);
	res33 = Itoa(n3, res33, 2);

	res111 = Itoa(n1, res111, 16);
	res222 = Itoa(n2, res222, 16);
	res333 = Itoa(n3, res333, 16);

	test1 = (0 == strcmp(str1, res1));
	test2 = (0 == strcmp(str2, res2));
	test3 = (0 == strcmp(str3, res3));

	test11 = (0 == strcmp(str11, res11));
	test22 = (0 == strcmp(str22, res22));
	test33 = (0 == strcmp(str33, res33));

	test111 = (0 == strcmp(str111, res111));
	test222 = (0 == strcmp(str222, res222));
	test333 = (0 == strcmp(str333, res333));


	if(test1 && test2 && test3 &&
		test11 && test22 && test33 &&
		test111 && test222 && test333)
	{
		printf("Itoa  passed\n");
	}
	else
	{
		printf("Itoa  failed, test1: %d, test2: %d, test3: %d\ntest11: %d, test22: %d, test33: %d\ntest111: %d, test222: %d, test333: %d\n",test1, test2, test3,test11, test22, test33, test111, test222, test333);
	}

	free(res1);
	free(res2);
	free(res3);

	free(res11);
	free(res22);
	free(res33);

	free(res111);
	free(res222);
	free(res333);
}
static int ConvertCharToDig(const char *str)
{
	int ascii_gap = (*str >= 'A') ? (int)('A' - 10) : (48);
	int digit = ((int)*str - ascii_gap);
	return digit;
}
static int IsDigitLegit(const char *str, int base )
{	
	int digit = ConvertCharToDig(str);
	if(digit < 0 || digit >= base)
	{
		return FALSE;
	}
	return TRUE;
}
static const char *MoveToStartAndCalcLen(const char *str, int *len, int base, int *minus_flag)
{
	const char *str_start = NULL;
	while ('\0' != *str && (' '== *str))
	{
		++str;
	}
	
	if ('-' == *str)
	{
		*minus_flag = -1;
		++str;
	}
	str_start = str;
	while ('\0' != *str && IsDigitLegit(str, base))
	{
		++*len;
		++str;
	}
	return str_start;
		
}
int Atoi(const char *str , int base)
{
	int num = 0;
	int len = 0;
	int minus_flag = 1;
	const char *str_new = MoveToStartAndCalcLen(str, &len, base, &minus_flag);
	int digit = 0;
	int count = 0;
	while(count < len)
	{
		digit = ConvertCharToDig(str_new);
		if(!IsDigitLegit(str_new, base))
		{
			return num;
		}
		num += digit * power(base , len -1);
		--len;
		++str_new;
	}
	return num * minus_flag;
}		

static int TestAtoiBase10(const char *str)
{

    return (atoi(str) == Atoi(str, 10));

}
static void TestAtoi2()
{
	int test1 = 0, test2 = 0, test3 = 0, test4 = 0;
	int test5 = 0, test6 = 0, test7 = 0, test8 = 0;
	int test9 = 0, test10 = 0, test11 = 0;

	test1 = (-121 == Atoi("-121", 10));
	test2 = (478 == Atoi("122201", 3));
	test3 = (-9873167 == Atoi("-211222130033", 4));
	test4 = (354163 == Atoi("42313123", 5));
	test5 = (514232 == Atoi("41132", 6));
	test6 = (230630 == Atoi("41132", 7));
	test7 = (120254 == Atoi("41132", 8));
	test8 = (-2000000 == Atoi("-1MLI2", 33));
	test9 = (12121212 == Atoi("H3SOO", 29));
	test10 = (-121 == Atoi("-11111", 3));
	test11 = (200000000 == Atoi("3B2OZK", 36));

	if(test1 && test2 && test3 &&
		test4 && test5 && test6 &&
		test7 && test8 && test9
		&& test10 && test11)
	{
		printf("Itoa  passed\n");
	}
	else
	{
		printf("Itoa  failed, test1: %d,\ntest2: %d,\ntest3: %d\ntest4: %d,\ntest5:%d,\ntest6: %d\ntest7: %d,\ntest8: %d,\ntest9: %d,\ntest10: %d\n,test11: %d\n",test1, test2, test3,test4, test5, test6, test7, test8, test9, test10, test11);
	}
}
static void TestAtoi()
{

    int test1 = 0, test2 = 0, test3 = 0, test4 = 0, test5 = 0, test6 = 0, test7 = 0, test8 =0;


    test1 = (54365 == Atoi("1B98C", 13));
    test2 = (6574 == Atoi("1212232  7", 4));
    test3 =    (654 == Atoi("1010001110", 2));
    test4 = (23 == Atoi("N", 25));
    test5 = (896 == Atoi("3EB", 15));
    test6 = (-2147483647 == Atoi("  -ZIK0ZJ  123", 36));
    test7 = (5 == Atoi("101", 2));
    test8 = (26 == Atoi("101", 5));




    if (test1 && test2 && test3 && test4 && test5 && test6 && test7 && test8)
    {
        printf("TestAtoi passed the test!\n");
    }
    else
    {
        printf("TestAtoi failed, test1 = %d, test2 = %d, test3 = %d, test4 = %d, test5 = %d, test6 = %d, test7 = %d, test8 = %d\n", test1, test2, test3, test4, test5, test6, test7, test8);
    }
}
static void ThreeCharArr(char arr1[], size_t size1, char arr2[], size_t size2, char arr3[], size_t size3)
{
 int arr [255][3]= { 0 };
 size_t idx = 0;
 char ch = 0;
 for (idx = 0; idx < size1 ; ++idx)
 {
 	ch = arr1[idx];
 	++arr[(int)ch][0];
 }
 for (idx = 0; idx < size2 ; ++idx)
 {
 	ch = arr2[idx];
 	++arr[(int)ch][1];
 }
 for (idx = 0; idx < size3 ; ++idx)
 {
 	ch = arr3[idx];
 	++arr[(int)ch][2];
 }
 for (idx = 0; idx < 255; ++idx)
 {
 	if (1 <= arr[idx][0] && 1 <= arr[idx][1] && 0 == arr[idx][2] )
 	{
 		printf("%c ", (unsigned char)idx);
 	}
 }
 printf("\n");
}