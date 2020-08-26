#include <stddef.h> /* size_t */
#include <assert.h> /*assert*/
#include "bit_array.h"


#define ALL_ONE_MASK (0xFFFFFFFFFFFFFFFF)
#define ALL_ZERO_MASK (0x0000000000000000) 
#define NUM_OF_BITS (63) 


bit_array_t BitsArrSetAll(bit_array_t arr)
{
	(void)arr;
	return -1;
}

bit_array_t BitsArrResetAll(bit_array_t arr)
{
	(void)arr;
	return 0;
}

char *BitsArrToString(bit_array_t arr, char *dest)
{
    int i = 0;
    char *dest_stert = dest;
    int digit = 0;
    
    assert(NULL != dest);
        
    dest = dest + 64;
    *dest = '\0';
    --dest;

    for (i = 0; i < 64; ++i)
    {
        digit = arr & 1;
        *dest = (unsigned char)digit + '0';
        arr >>= 1;
        --dest;
    }

    return dest_stert;
}
bit_array_t BitsArrFlip(bit_array_t arr)
{
	return ~arr;
}
bit_array_t BitsArrSetOn(bit_array_t arr, size_t idx)
{
	
	return ( arr |= ((bit_array_t)1 << idx));
}
bit_array_t BitsArrSetOff(bit_array_t arr, size_t idx)
{
	bit_array_t mask = (bit_array_t)(-1);
	mask ^= ((bit_array_t)1 << idx);
	return (arr &= mask);
}


