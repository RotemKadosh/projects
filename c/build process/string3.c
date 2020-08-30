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
    do
    {
        if(*str == c)
        {
            return (char *)str;
        }
       
    }
    while('\0' != *str++)
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
