#include <stdio.h>
#include <stdlib.h>

/*function decleration*/

void Swap (int *num1, int* num2);
void CopyArray (int arr_a[], int arr_b [], int size);
int Strlen (char *str);
int Strcmp (char *str1, char *str2);

/*function definition*/

void Swap (int *num1, int* num2)
{
 	int temp=*num1;
 	*num1=*num2;
 	*num2=temp;
}
 
void CopyArray (int arr_a[], int arr_b [], int size)
{
	int i; 
 	for(i=0;i<size;i++)
 	{
 		arr_b[i]=arr_a[i];
	}
}

int Strlen (char *str)
{
	int p;
	p=str;
	while (*str != '\0')
	{
		str++;
	}
	return (str-p);
}

int Strcmp (char *str1, char *str2)
{
	while('\0'!=*str1 || '\0' !=*str2)
	{	
		if(*str1>*str2)
		{
			return 1;
		}
		else if (*str2>*str3)
		{
			return -1;
		}
		else
		{
			str1++;
			str2++;
		}
	}
	return








