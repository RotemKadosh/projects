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

char *Strtok(char *str, const char *delim)
{
    static char *start;
    assert(NULL != delim);

    if(NULL != str)
    {
        if('\0' != *str)
        {
            start = str;
        }
    }
    while( *start == *delim)
    {
        ++start;
    }
    while(*delim != *start  && '\0' != *start)
    {
        ++start;
    }
    if('\0' == *start)
    {
        return NULL;
    }
    return start;

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

char *RemoveEdges(char *str, char *ans, size_t len)
{
    char *begin = str, char *end = str+len;

   while('\0' != begin && isspace((int) *begin))
   {
        ++begin;
   }
    while(end >= begin && isspace((int) *end))
   {
        --end;
   }
   ans = memmove(ans , begin , (end - begin));
   *(ans + end - begin + 1)='\0';
   return ans;
}
char *RemoveDouble(char *str)
{
`  size_t len = 0;
   int counter = 0; 
   char * tmp = str;
   while('\0' != *tmp)
   {
    if( isspace(*tmp))
    {
        if(counter>0)
        {
            len = Strlen(tmp)-1;
            tmp = memmove(tmp, tmp+1 ,len )
        }
        else
        {
            ++tmp;
        }
    }
    else
    {
        counter = 0;
        ++tmp;
    }
   }
}

char * RemoveExtraWS(char *str)
{   
    int counter = 0;
    size_t len= Strlen(*str);
    char *ans = (char *)malloc(len);
    assert(str);
    ans = RemoveEdges(str, ans, len);
    ans = RemoveDouble(ans)
    return ans;


}

/*-------------------main----------------------------------------*/



