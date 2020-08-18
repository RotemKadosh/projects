#include <stdio.h> /*ptintf */
#include <assert.h> /*assert*/
#include <limits.h> /*INT_MAX*/
#include "ws6.h"

#define TRUE (1)
#define FALSE (0)
#define FIRST_BIT ( 1 )
#define SECOND_BIT ( 1 << 1 )
#define THIRD_BIT (1 << 2)
#define FORTH_BIT ( 1 << 4 )
#define FIFTH_BIT (1 << 4)
#define SIX_BIT (1 << 5)
#define SEVEN_BIT ( 1 << 6 )
#define EIGHT_BIT ( 1 << 7 )
#define CLEAR_FIRST_NIBLLE ( -1 << 4 )

static unsigned int Is3SetBits(int n); 

long Pow2(unsigned int x ,unsigned int y)
{
	return x << y;
}
int IsPow(unsigned int n)
{
	return n && (!(n & ( n - 1)));
}
int IsPowLoop(unsigned int n)
{
	if (0 == n)
	{
		return FALSE;
	}
	while (FIRST_BIT != n)
	{
		if (0 != (n & FIRST_BIT))
		{
			return FALSE;
		}
		n >>= 1;
	}
	return TRUE;
}
int AddOne(int num)
{
	return (- ( ~ num));
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
		if (1 == (n & FIRST_BIT))
		{
			++count;
			if (4 == count)
			{
				return FALSE;
			}
		}
	}
	if (3 == count)
	{
		return TRUE;
	}
	return FALSE;
}
void Print3BitsOn(unsigned int *arr, size_t size)
{
	size_t i = 0;
	for (i = 0; i < size; ++i)
	{
		if (TRUE == Is3SetBits(arr[i]))
		{
			printf("%d, " ,arr[i]);
		}
	}
	printf("\n");
}
unsigned char ByteMirror(unsigned char byte)
{
	byte = ((byte >> 4) | (byte << 4));
	byte = ((byte & 0xCC) >> 2) | ((byte & 0x33) << 2);
	byte = ((byte & 0xAA) >> 1) | ((byte & 0x55) << 1);
	return byte;
}
unsigned char ByteMirrorLoop(unsigned char byte)
{
	size_t i = 0;
	unsigned char ans = 0;
	size_t byte_size = 8;
	for (i = 0; i < byte_size; ++i)
	{
		if (1 == (byte & 1))
		{
			ans = ((1 << (byte_size -FIRST_BIT - i)) | ans);
		}
		byte >>= 1;
	}
	return ans;
}
int Is2And6BitsOn(unsigned char byte)
{
	return (SECOND_BIT == (byte & SECOND_BIT)) && (SIX_BIT == (byte & SIX_BIT));
}
int Is2Or6BitsOn(unsigned char byte)
{
	return (SECOND_BIT == (byte & SECOND_BIT)) || (SIX_BIT == (byte & SIX_BIT));
}
unsigned char Swap3And5Bits(unsigned char byte)
{
	if ((THIRD_BIT == (byte & THIRD_BIT)  && FIFTH_BIT == (byte & FIFTH_BIT)) ||
		(0 == (byte & THIRD_BIT)  && 0 == (byte & FIFTH_BIT)))
	{
		return byte;
	}
	byte ^= THIRD_BIT;
	byte ^= FIFTH_BIT;
	return byte;
}
unsigned int FindClosestDivisibleBy16(unsigned int num)
{
	return num & CLEAR_FIRST_NIBLLE;
}
void SwapWithOnly2Var(int *num1, int *num2)
{
	*num1 = *num1 ^ *num2;
	*num2 = *num2 ^ *num1;
	*num1 = *num1 ^ *num2;
}
int CountSetBits(int num)
{
	unsigned int count = 0;
	int set_bits_in_nibble[] = {0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4};

   	count += set_bits_in_nibble[(num & 0x0F)];
	num >>= 4;
	count += set_bits_in_nibble[(num & 0x0F)];
	num >>= 4;
	count += set_bits_in_nibble[(num & 0x0F)];
	num >>= 4;
	count += set_bits_in_nibble[(num & 0x0F)];
	num >>= 4;
	count += set_bits_in_nibble[(num & 0x0F)];
	num >>= 4;
	count += set_bits_in_nibble[(num & 0x0F)];
	num >>= 4;
	count += set_bits_in_nibble[(num & 0x0F)];
	num >>= 4;
	count += set_bits_in_nibble[(num & 0x0F)];
	num >>= 4;
	return count;
}
int CountSetBitsLoop(int num)
{	
	/*unsigned char n = (unsigned char) num;*/
	unsigned int count = 0;
	size_t size = sizeof(int) << 3;
	size_t i = 0;
	while (size > 0)
	{
		count += ((num >> i) & 1);
		++i;
		--size;
	}
	return count;
}
void FloatAnalize(float num)
{
    unsigned int *float_as_int = (unsigned int *)&num;
    int i = 0;
    int count = 0;
    int fpoint = 9;
    printf("sign bit-> ");
    for (i = 31; i >= 0; --i, ++count, --fpoint)
    {
    	if(30 == i )
    	{
    		printf(" exponent->");
    		count = 0;
    	}
    	if(4 == count){
    		printf(" ");
    		count = 0;
    	}
    	if (0 == fpoint)
    	{
    		printf("mantisa -> 1.");
    	}
        printf("%d",((*float_as_int >> i) & 1));
    }
    printf("\n");
}
