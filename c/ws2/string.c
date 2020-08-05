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
    size_t i = 0;
	
	assert(dest);
	assert(src);
    
    for(i = 0; i < end ; ++i)
    {
       dest[i] = src[i];
    }
    
    for( ; i < n ; ++i)
    {
       dest[i] = '\0';
    }
    
    dest[i] = '\0';
    return dest;
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
	char *tmp;
	assert(dest);
	assert(src);

	while('\0' != *tmp++){}
	
	strcpy(tmp,src);
	
	return(dest);
}

char *Strncat(char *dest, const char *src, size_t n)
{
	char *tmp;
	assert(dest);
	assert(src);
	
	while('\0' != *tmp++){}
	
	strncpy(tmp,src,n);
	
	return(dest);
}
char *Strstr(const char *haystack, const char *needle)
{	
	size_t need_len = Strlen(needle);
	size_t i=0;
	 
	while('\0' != *haystack)
	{
		if(*haystack == *needle)
		{
			for(i = 1; i < need_len ; ++i)
			{
				if(haystack[i] != needle[i])
				{
					break;
				}
			}
			if(i == need_len-1)
			{
				return haystack;
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



void StrcpyTest()
{
    int test1 = 0, test2 = 0, test3 = 0, test4 = 0; 
    const char *src1 = "copy this string";
    char *dest1 =(char *)malloc(Strlen(src1)+1);

    const char *src2 = "ore    klm";
    char *dest2 =(char *)malloc(Strlen(src2)+1);

    const char *src3 = "";
    char *dest3 =(char *)malloc(Strlen(src3)+1);

    const char *src4 = "hello";
    char *dest4 ="im already here";
        
    test1 = (0==Strcmp(src1,Strcpy(dest1,src1)));
	test2 = (0==Strcmp(src2,Strcpy(dest2,src2)));
	test3 = (0==Strcmp(src3,Strcpy(dest3,src3)));
	test4 = (0==Strcmp(src4,Strcpy(dest4,src4)));
	
	
	if (test1 && test2 && test3 && test4 )
	{
		printf("the Strcpy function passed the tests\n");
	}
	else
	{
		printf("Strcpy failed!, test1=%d, test2=%d, test3=%d, test4=%d \n",test1,test2,test3,test4);
		
	}
}
 /*   
void StrncpyTest()
{
    int test1 = 0, test2 = 0, test3 = 0, test4 = 0; 
    const char *src1 = "copy this string";
    char *dest1 =(char *)malloc(Strlen(src1)+1);

    const char *src2 = "ore    klm";
    char *dest2 =(char *)malloc(Strlen(src2)+1);

    const char *src3 = "";
    char *dest3 =(char *)malloc(Strlen(src3)+1);

    const char *src4 = "hello";
    char *dest4 ="im already here";
        
    test1 = (0==Strcmp(Strncpy(dest1,src1,3),strncpy(dest1,src1,3)));
	test2 = (0==Strcmp(Strncpy(dest2,src2,6),strncpy(dest2,src2,6)));
	test3 = (0==Strcmp(Strncpy(dest3,src3,0),strncpy(dest3,src3,0)));
	test4 = (0==Strcmp(Strncpy(dest4,src4,6),strncpy(dest4,src4,6)));
	
	
	if (test1 && test2 && test3 && test4 )
	{
		printf("the Strncpy function passed the tests\n");
	}
	else
	{
		printf("Strncpy failed!, test1=%d, test2=%d, test3=%d, test4=%d \n",test1,test2,test3,test4);
		
	}

}    
    
  */  
    
    
    





