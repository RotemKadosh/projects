#include <stdio.h> /*printf*/
#include <assert.h> /*for assert*/
#include <stddef.h> /* size_t */
#include <ctype.h>  /*for tolower*/
#include <stdlib.h> /*fot malloc*/
#include <string.h> 
#include "String.h"


#define SUCCESS 0
#define FAIL 1

#define TRUE 1
#define FALSE 0

/*--------------------function declerations-----------------------*/
size_t Strlen (const char *str);
int Strcmp (const char *str1,const char *str2);
char *Strcpy(char *dest, const char *src);
char *Strncpy(char *dest, const char *src, size_t n);
int Strcasecmp(const char *str1, const char *str2);
char *Strchr(const char *str, int c);
char *Strdup(const char *str);
char *Strcat(char *dest, const char *src);
char *Strncat(char *dest, const char *src, size_t n);
char *Strstr(const char *haystack, const char *needle);
int  ContainChar(const char *ch, const char *str2);
size_t Strspn(const char *str1, const char *str2);
char *Strtok(char *str, const char *delim);
int IsPalindrom(const char *str);
int ContainSeven(int num);
void SevenBoom(int num1, int num2);

/*--------------------Function definitions-------------------------*/

size_t Strlen(const char *str)
{
	const char *plc = str;
	assert(str);

	while ('\0' != *str)
	{
		++str;
	}
	return (str - plc);
}

int Strcmp(const char *str1, const char *str2)
{	
	assert(str1); 
    assert(str2);
	
	while('\0' != *str1 ||'\0' != *str2)
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
			++str1;
			++str2;
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
            return (char *)str;
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
    char *tmp = dest;
    assert(dest);
    assert(src);

    while('\0' != *tmp++){}
    --tmp;
    strcpy(tmp,src);
    return(dest);
}
char *Strncat(char *dest, const char *src, size_t n)
{
    char *tmp = dest;
    assert(dest);
    assert(src);
    
    while('\0' != *tmp++){}
    --tmp;
    strncpy(tmp, src, n);
    
    return(dest);
}

char *Strstr(const char *haystack, const char *needle)
{   
    size_t need_len = Strlen(needle);
    const char *hy_plc = haystack;
    const char *ndl_plc = needle;
     
    while('\0' != *haystack)
    {
        if(*haystack == *needle)
        {
            hy_plc = haystack;
            ndl_plc = needle;
            while('\0' != *ndl_plc )
            {
                if(*hy_plc != *ndl_plc)
                {
                    break;
                }
                ++ndl_plc;
                ++hy_plc;
            }
            if(ndl_plc == needle + need_len)
            {
                return (char *)haystack;
            }
        }
        ++haystack;
    }
    return NULL;
}


size_t Strspn(const char *str1, const char *str2)
{
    size_t ans = 0;
    while('\0' != *str1)
    {
        if(NULL == Strchr( str2, *str1 ))
        {
            return ans;
        }
        else
        {
            ++ans;
        }
        ++str1;
    }
    return ans;
}

char *Strtok(char *str, const char *delim)
{
    static char *start;
    assert(NULL == delim);

    if(NULL != str)
    {
        if('\0' != *str)
        {
            start = str;
        }
    }


}







/*-------------------Advance-function definitions------------------*/

int IsPalindrom(const char *str)
{
    const char  *left = str , *right = str + Strlen(str) - 1;
    assert(str);
    while(left < right)
    {
        if( *left != *right )
        {
            return FALSE;
        }
        else
        {
            ++left;
            --right;
        }
    }
    return TRUE;
}

int ContainSeven(int num)
{
    int digit = 0;
    while(num)
    {
        digit = num % 10;
        if(7 == digit || -7 == digit)
        {
            return TRUE;
        }
        num /= 10;
    }
    return FALSE;
}

void SevenBoom(int num1, int num2)
{
    int i = num1;
    for(i = num1 ; i <= num2 ; ++i )
    {
        
        if(( 0 == i % 7 && i > 6 )  || ContainSeven(i))
        {
            printf("Boom ");
        }
        else
        {
            printf("%d ", i);
        }
    }
    printf("\n");
}


/*-------------------main----------------------------------------*/



