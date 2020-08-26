#include <stdio.h> /*printf*/
#include <stdlib.h> /*malloc, free, itoa*/
#include <string.h> /*strcmp*/

#define NULL_CHAR (1)
#define ASCII_GAP (48)
#define FALSE (0)
#define TRUE (1)
#define IS_LITTLE_ENDIAN (1 == (char)(int)1)

/*-------help functions -------*/
static int power(int base ,int exp); 
static size_t NumOfDigits(int num, int base);
static int ConvertCharToDig(const char *str);
static int IsDigitLegit(const char *str, int base );
static const char *MoveToStartAndCalcLen(const char *str, int *len, int base, int *minus_flag);

/*-------functions -------*/
int Atoi(const char *str , int base);
char *Itoa(int value, char * str, int base);
static void ThreeCharArr(char arr1[], size_t size1, char arr2[], size_t size2, char arr3[], size_t size3);
int WhichEndian();

/*-------tests -------*/
static void TestItoa();
static void TestAtoi();


int main()
{
	int a = IS_LITTLE_ENDIAN;
	char arr1[] = {'a', 'b', 'c', 'd'};
	char arr2[] = {'a', 'E', 'c', 'd'};
	char arr3[] = {'a', 'b', 'a', 'f'};
	TestItoa();
	TestAtoi();
	printf("%s\n", a ? " macro: little endian" : "macro: big endian");
	ThreeCharArr(arr1, sizeof(arr1)/sizeof(arr1[0]), arr2, sizeof(arr2)/sizeof(arr2[0]),arr3, sizeof(arr3)/sizeof(arr3[0]));
	WhichEndian();
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
char *Itoa(int value, char *str, int base)
{
	int digit = 0;
	char *str_start = str;
	int num_of_digit = NumOfDigits(value, base);
	if(0 > value)
	{

		*str = '-';
		++str;
		value *= -1;
	}
	str = str + num_of_digit ;
	*str = '\0';
	--str;
	do
	{	
		digit = value % base;
		*str = (unsigned char)((digit > 9) ? (digit-10) + 'A' : digit + '0');
		--str;
		value /= base;
	}while (0 < value);
	return str_start;
} 

static void TestItoa()
{
	int n1 = 15, n2 = -85, n3 = 0;
	
	int test1 = 0, test2 = 0, test3 = 0;
	int test4 = 0, test5 = 0, test6 = 0;
	int test7 = 0, test8 = 0, test9 = 0;

	char res1[32] = {0}, res2[32] = {0}, res3[32] = {0}, res4[32] = {0};
	char res5[32] = {0}, res6[32] = {0}, res7[32] = {0}, res8[32] = {0}, res9[32] = {0};

	char *str1 = "15" , *str2 = "-85", *str3 = "0", *str4 = "1111", *str5 = "-1010101";
	char *str6 = "0", *str7 = "F", *str8 = "-55", *str9 = "0";
	
	Itoa(n1, res1, 10);
	Itoa(n2, res2, 10);
	Itoa(n3, res3, 10);
	Itoa(n1, res4, 2);
	Itoa(n2, res5, 2);
	Itoa(n3, res6, 2);
	Itoa(n1, res7, 16);
	Itoa(n2, res8, 16);
	Itoa(n3, res9, 16);

	test1 = (0 == strcmp(str1, res1));
	test2 = (0 == strcmp(str2, res2));
	test3 = (0 == strcmp(str3, res3));
	test4 = (0 == strcmp(str4, res4));
	test5 = (0 == strcmp(str5, res5));
	test6 = (0 == strcmp(str6, res6));
	test7 = (0 == strcmp(str7, res7));
	test8 = (0 == strcmp(str8, res8));
	test9 = (0 == strcmp(str9, res9));

	if(test1 && test2 && test3 &&
	   test4 && test5 && test6 &&
	   test7 && test8 && test9)
	{
		printf("Itoa passed\n");
	}
	else
	{
		printf("Itoa failed, test1: %d\ntest2: %d\ntest3: %d\ntest4: %d\ntest5: %d\ntest6: %d\ntest7: %d\ntest8: %d\ntest9: %d\n",test1, test2, test3,test4, test5, test6, test7, test8, test9);
	}
}

static int ConvertCharToDig(const char *str)
{
	int ascii_gap = (*str >= 'A') ? (int)('A' - 10) : '0';
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


static const char *MoveToStart(const char *str, int *minus_flag)
{
	while ('\0' != *str && (' '== *str))
	{
		++str;
	}
	
	if ('-' == *str)
	{
		*minus_flag = -1;
		++str;
	}
	return str;
}

int CalcLen(const char *str, int base)
{
	int len = 0;
	while ('\0' != *str && IsDigitLegit(str, base))
	{
		++len;
		++str;
	}
	return len;		
}
/*
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
*/
int Atoi(const char *str , int base)
{
	int num = 0;
	int len = 0;
	int minus_flag = 1;
	int digit = 0;
	int count = 0;
	
	const char *str_new = MoveToStart(str, &minus_flag);
	len = CalcLen (str_new, base);
	
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
static void TestAtoi()
{
	int test1 = 0, test2 = 0, test3 = 0, test4 = 0;
	int test5 = 0, test6 = 0, test7 = 0, test8 = 0;
	int test9 = 0, test10 = 0, test11 = 0;

	test1 = (-121 == Atoi("-121", 10));
	test2 = (478 == Atoi("122201", 3));
	test3 = (-9873167 == Atoi("-211222130033", 4));
	test4 = (354163 == Atoi("42313123", 5));
  	test5 = (-2147483647 == Atoi("  -ZIK0ZJ  123", 36));
    test6 = (5 == Atoi("101", 2));
    test7 = (26 == Atoi("101", 5));
	test8 = (-2000000 == Atoi("-1MLI2", 33));
	test9 = (12121212 == Atoi("H3SOO", 29));
	test10 = (-121 == Atoi("-11111", 3));
	test11 = (200000000 == Atoi("3B2OZK", 36));

	if(test1 && test2 && test3 &&
		test4 && test5 && test6 &&
		test7 && test8 && test9
		&& test10 && test11)
	{
		printf("Atoi passed\n");
	}
	else
	{
		printf("Atoi failed, test1: %d,\ntest2: %d,\ntest3: %d\ntest4: %d,\ntest5:%d,\ntest6: %d\ntest7: %d,\ntest8: %d,\ntest9: %d,\ntest10: %d\n,test11: %d\n",test1, test2, test3,test4, test5, test6, test7, test8, test9, test10, test11);
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
int WhichEndian()
{
	unsigned int i = 1; 
   	char *c = (char*)&i; 
   	if (*c)
   	{
   		printf("function: Little endian\n");
   		return TRUE; 
   	}     
   	else
   	{
       printf("function: Big endian\n"); 
   	}
   	return FALSE; 
}