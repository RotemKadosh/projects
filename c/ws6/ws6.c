#include <stdio.h> /*ptintf */
#include <assert.h> /*assert*/
#include "ws6.h"

#define TRUE (1)
#define FALSE (0)
#define SECOND_BIT ( 1 << 1 )
#define SIX_BIT (1 << 5)


long Pow2(unsigned int x ,unsigned int y);
int IsPow(unsigned int n);
int IsPowLoop(unsigned int n);

int AddOneLoop(int num);
unsigned int Is3SetBits(int n);
void Print3BitsOn(unsigned int *arr, size_t size);

unsigned char ByteMirrorLoop(unsigned char byte);
int Is2And6BitsOn(unsigned char byte);
int Is2Or6BitsOn(unsigned char byte);

long Pow2(unsigned int x ,unsigned int y)
{
	return x << y;
}

int IsPow(unsigned int n)
{
	return n && (!(n&(n-1)));
}

int IsPowLoop(unsigned int n)
{
	if(0 == n)
	{
		return FALSE;
	}
	while(1 != n)
	{
		if(0 != n%2)
		{
			return FALSE;
		}
		n /= 2;
	}
	return TRUE;
}

int AddOneLoop(int num)
{
	int last_on = 1;
	while(0 != (num & last_on))
	{
		num = num ^ last_on;
		last_on <<= 1;
	}
	num = num ^ last_on;
	return num;
}
unsigned int Is3SetBits(int n)
{
	int count = 0;
	for (;0 != n ;n >>= 1)
	{
		if(1 == (n & 1))
		{
			++count;
			if(4 == count)
			{
				return FALSE;
			}
		}
	}
	if(3 == count)
	{
		return TRUE;
	}
	return FALSE;
}

void Print3BitsOn(unsigned int *arr, size_t size)
{
	size_t i = 0;
	for(i = 0; i < size; ++i)
	{
		if(TRUE == Is3SetBits(arr[i]))
		{
			printf("%d, " , arr[i]);
		}
	}
	printf("\n");
}

unsigned char ByteMirrorLoop(unsigned char byte)
{
	size_t i = 0;
	unsigned char ans = 0;
	size_t byte_size = 8;
	for(i = 0; i < byte_size; ++i)
	{
		if(1 == (byte & 1))
		{
			ans = ((1 << (byte_size -1 - i)) | ans);
		}
		byte >>= 1;
	}
	return ans;
}

int Is2And6BitsOn(unsigned char byte)
{
	return  (SECOND_BIT == (byte & SECOND_BIT)) && (SIX_BIT == (byte & SIX_BIT));
}

int Is2Or6BitsOn(unsigned char byte)
{
	return (SECOND_BIT == (byte & SECOND_BIT)) || (SIX_BIT == (byte & SIX_BIT));
}




