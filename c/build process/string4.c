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

char *Strstr(const char *haystack, const char *needle)
{   
    size_t need_len = Strlen(needle);
    const char *hy_plc = haystack;
    const char *ndl_plc = needle;
     
    while('\0' != *haystack)
    {
        if( 0 == strncmp(haystack, needle, need_len))
        {
            return (char *)haystack;
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
