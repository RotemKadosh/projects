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
    do
    {
       *dest++ = *src 
    }
	while('\0' != *src++)
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