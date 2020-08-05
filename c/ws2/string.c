#include <stdio.h> /*printf*/
#include "String.h"
#include <assert.h> /*for assert*/
#include <stddef.h> /* size_t */
#include <ctype.h>  /*for tolower*/
#include <stdlib.h> /*fot malloc*/
#include <string.h> /*for testing -should be moved*/

#define SUCCESS 0
#define FAIL 1

#define TRUE 1
#define FALSE 0

/*--------------------function declerations-----------------------*/
size_t Strlen (const char *str);

char *Strcpy(char *dest, const char *src);

int IsPalindrom(const char *str);
int ContainSeven(int num);
void SevenBoom(int start, int end);


void StrcpyTest();
void StrncpyTest();
/*--------------------Function definitions-------------------------*/

size_t Strlen (const char *str)
{
	const char *plc=str;
	assert(str);

	while (*str)
	{
		++str;
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
			++str1;
			++str2;
		}
		else
		{
			return(*str1 - *str2);
		}
	}
	return SUCCESS;
}

char *Strcpy(char *dest, const char *src)
{
	char *dest_ptr = dest;
	assert(dest);
	assert(src);

	
	while('\0' != *src)
	{
		*dest++ = *src++;	
	}
	*dest = '\0';
	return dest_ptr;
}

char *Strncpy(char *dest, const char *src, size_t n)
{
    size_t end = n > Strlen(src) ?  Strlen(src) : n;
    char  *ptr_start = dest;
    char const *ptr_end1 = src + end;
    char const *ptr_end2 = src + n;
    assert(dest);
    assert(src);
    
    while (src != ptr_end1)
    {
       *dest = *src;
       ++dest;
       ++src;
    }
    
    while (src != ptr_end2)
    {
       *dest = '\0';
       ++dest;
       ++src;
    }
    
    *dest = '\0';
    return ptr_start;
}

int Strcasecmp(const char *str1, const char *str2)
{
    char tmp_a = 0, tmp_b = 0; 
	assert(str1 || str2);
	
	while('\0' != *str1 || '\0' != *str2)
	{	
	    tmp_a = tolower(*str1);
	    tmp_b = tolower(*str2);
		
		if(tmp_a == tmp_b)
		{
			str1++;
			str2++;
		}
		else
		{
			return(tmp_a - tmp_b);
		}
	}
	return SUCCESS;
}

char *Strchr(const char *str, int c)
{   
    assert(str);
    while('\0' != *str)
    {
        if(*str == c)
        {
            return (char *) str;
        }
        str++;
    }
    return NULL;
}

char *Strdup(const char *str)
{   
    size_t len = Strlen(str);
    char *dup = (char *)malloc(len+1);
    assert(str);
    if(NULL == dup)
    {
        return NULL;
    }
    else
    {
       dup = strcpy(dup,str);
    }
    return dup;
}

char *Strcat(char *dest, const char *src)
{   
    char *tmp=dest;
    assert(dest);
    assert(src);

    while('\0' != *tmp++){}
    --tmp;
    strcpy(tmp,src);
    return(dest);
}

char *Strncat(char *dest, const char *src, size_t n)
{
	char *tmp;
	assert(dest);
	assert(src);
	
	while('\0' != *tmp++){}
	--tmp;
	strncpy(tmp,src,n);
	
	return(dest);
}
char *Strstr(const char *haystack, const char *needle)
{	
	size_t need_len = Strlen(needle);

	size_t i=0;
	const char * hy_plc = haystack;
	const char * ndl_plc = needle;
	 
	while('\0' != *haystack)
	{
		if(*haystack == *needle)
		{
			hy_plc = haystack;
			ndl_plc = needle;
			while(ndl_plc != (needle + need_len))
			{
				if(*ndl_plc != *ndl_plc)
				{
					break;
				}
				++ndl_plc;
			}
			if(ndl_plc == needle + need_len)
			{
				return (const char *)ndl_plc;
			}
		}
		++haystack;
	}
	return NULL;
}

int  ContainChar(const char *str1, const char *str2)
{
	size_t str_len = Strlen( str2 );
	size_t i = 0;
	while('\0' != *str2++)
	{
		if(*str1 == *str2)
		{
			return TRUE;
		}
	}
	return FALSE;
}

size_t Strspn(const char *str1, const char *str2)
{
	size_t ans = 0;
	while('\0' != *str1++)
	{
		if(!ContainChar(str1, str2))
		{
			return ans;
		}
		else
		{
			++ans;
		}
	}
	return ans;
}








/*-------------------Advence-function definitions------------------*/

int IsPalindrom(const char *str)
{
    size_t start = 0, end = Strlen(str);
    assert(str);
    while(start <= end)
    {
        if(*(str + start) != *(str + end))
        {
            return TRUE;
        }
        else
        {
            start++;
            end--;
        }
    }
    return FALSE;
}

int ContainSeven(int num)
{
    int digit=0;
    while(num)
    {
        digit=num%10;
        if(7 == digit || -7 == digit)
        {
            return TRUE;
        }
        num /= 10;
    }
    return FALSE;
}

void SevenBoom(int start, int end)
{
    for( ;start<=end;start++)
    {
        if(!(start % 7) || ContainSeven(start))
        {
            printf("Boom ");
        }
        else
        {
            printf("%d ",start);
        }
    }
    printf("\n");
}


/*-------------------main----------------------------------------*/


int main ()
{
	/*StrcpyTest();*/
	/*StrncpyTest();*/
	return 0;
}

/* tests needs to be mooved to different file- */







