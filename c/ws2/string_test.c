#include "String.h" 
#include <stdio.h> /*printf*/
#include <assert.h> /*for assert*/
#include <stddef.h> /* size_t */
#include <ctype.h>  /*for tolower*/
#include <stdlib.h> /*fot malloc*/
#include <string.h> /*for testing -should be moved*/

#define SUCCESS 0
#define FAIL 1

#define TRUE 1
#define FALSE 0


char *strdup(const char *s);
int strcasecmp(const char *, const char *);
void StrcpyTest();
void StrncpyTest();
void StrncpyTest();
void PilandromTest();
size_t Strlen (const char *str);
int Strcmp (const char *str1,const char *str2);
void TestStrcpy(void);
void StrcasecmpTest();
void StrchrTest();
void StrdupTest();
void StrcatTest();
void StrncatTest();
void StrstrTest();

char *Strcpy(char *dest, const char *src);
char *Strncpy(char *dest, const char *src, size_t n);



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
                return (char *)ndl_plc;
            }
        }
        ++haystack;
    }
    return NULL;
}

int main(int argc, char *argv[])
{
    StrstrTest();
    return 0;
}

/* Why is it like this? */

void StrstrTest()
{
    
    const char *src1 = "hello cat erer";
    const char *dest1 = "cat";
    const char *dest2 = "cat  ";
    const char *src2 = " my name is Rotem";
    const char *dest3 = "cat check two";
    const char *dest4 = "cat check two";
    const char *src3 = "shorter then nS";
    const char *dest5 = "Short";
    const char *dest6 = "Short";

    int test1 = 0, test2 = 0, test3 = 0;    

    Strstr(dest1, src1);
    strstr(dest2, src1);
    
    Strstr(dest3, src2);
    strstr(dest4, src2);

    Strstr(dest5, src3);
    strstr(dest6, src3);

    test1 = ( !strcmp( dest1, dest2));
    test2 = ( !strcmp( dest3, dest4));
    test3 = ( !strcmp( dest5, dest6));

    if (test1 && test2 && test3)
    { 
        printf("function Strstr passed\n");
    }
    else
    {
        printf("Strstr failed, test1: %d, test2: %d, test3: %d\n", test1, test2, test3);
    } 

}  


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
 /*
void StrcpyTest()
{
    const char *src1 = "hello world";
    char dest1[15] = {0};
    char *dest2 = (char *)malloc(15);
    const char *src2 = " my name is Rotem";
    char dest3[25] = {0};
    char dest4[25] = " hold dif str";
   
    int test1, test2;

    Strcpy(dest1, src1);
    strcpy(dest2, src1);
    Strcpy(dest3, src2);
    strcpy(dest4, src2);

    test1 = (strcmp(dest1, src1) == strcmp(dest2, src1));
    test2 = (strcmp(dest3, src2) == strcmp(dest4, src2));

    if (test1 && test2)
    { 
        printf("function Strcpy passed\n");
    }
    else
    {
        printf("Strcpy failed, test1: %d, test2: %d\n", test1, test2);
    } 
    free(dest2); 
}
 
void StrncpyTest()
{
    size_t size1 = 5, size2 = 20, size3 = 30;
    const char *src1 = "hello world";
    char *dest1 = (char *)malloc(size1);
    char *dest2 = (char *)malloc(size1);

    const char *src2 = " my name is Rotem";
    char *dest3 = (char *)malloc(size2);
    char *dest4 = (char *)malloc(size2);

    const char *src3= "shorter then n";
    char *dest5 = (char *)malloc(size3);
    char *dest6 = (char *)malloc(size3);
    
    size_t n1 = 5, n2 = 0, n3 = 16;
    int test1 = 0, test2 = 0, test3 = 0;    

    Strncpy(dest1, src1, n1);
    strncpy(dest2, src1, n1);
    
    Strncpy(dest3, src2, n2);
    strncpy(dest4, src2, n2);

    Strncpy(dest5, src3, n3);
    strncpy(dest6, src3, n3);

    test1 = (strcmp(dest1, src1) == strcmp(dest2, src1));
    test2 = (strcmp(dest3, src2) == strcmp(dest4, src2));
    test3 = (strcmp(dest5, src3) == strcmp(dest6, src3));
    
    free(dest1);
    free(dest2);
    free(dest3);
    free(dest4);
    free(dest5);
    free(dest6);


    if (test1 && test2 && test3)
    { 
        printf("function Strncpy passed\n");
    }
    else
    {
        printf("Strncpy failed, test1: %d, test2: %d, test3: %d\n", test1, test2, test3);
    } 

}  

void StrcasecmpTest()
{

    const char *src1 = "hello world";
    const char *dest1 = "HELLO world";
    const char *dest2 = "HELLO world";

    const char *src2 = " my name is Rotem";
    const char *dest3 = "   My name is Rotem";
    const char *dest4 = "   My name is Rotem";

    const char *src3= "shorter then n";
    const char *dest5 ="";
    const char *dest6 ="";
    
    int test1 = 0, test2 = 0, test3 = 0;    

    Strcasecmp(dest1, src1);
    strcasecmp(dest2, src1);
    
    Strcasecmp(dest3, src2);
    strcasecmp(dest4, src2);

    Strcasecmp(dest5, src3);
    strcasecmp(dest6, src3);

    test1 = (strcmp(dest1, src1) == strcmp(dest2, src1));
    test2 = (strcmp(dest3, src2) == strcmp(dest4, src2));
    test3 = (strcmp(dest5, src2) == strcmp(dest6, src2));



    if (test1 && test2 && test3)
    { 
        printf("function Strcasecmp passed\n");
    }
    else
    {
        printf("Strcasecmp failed, test1: %d, test2: %d, test3: %d\n", test1, test2, test3);
    } 

}   

void StrchrTest()
{
    char *ptr1 = NULL, *ptr2 = NULL, *ptr3 = NULL, *ptr4 = NULL, *ptr5 = NULL, *ptr6 = NULL;
    const char *src1 = "ABCDEFG";
    int c1 = 'A';
    int c2 = 'A';

    const char *src2 = " my name is Rotem";
    int c3 = 'o';
    int c4 = 'o';

    const char *src3= "shorter then n";
    int c5 = 'q';
    int c6 = 'q';
    
    int test1 = 0, test2 = 0, test3 = 0;    

    ptr1 = Strchr(src1, c1);
    ptr2 = strchr(src1, c2);
    
    ptr3 = Strchr(src2, c3);
    ptr4 = strchr(src2, c4);

    ptr5 = Strchr(src3, c5);
    ptr6 = strchr(src3, c6);

    test1 = (ptr1 == ptr2);
    test2 = (ptr3 == ptr4);
    test3 = (ptr5 == ptr6);



    if (test1 && test2 && test3)
    { 
        printf("function StrchrTest passed\n");
    }
    else
    {
        printf("StrchrTest failed, test1: %d, test2: %d, test3: %d\n", test1, test2, test3);
    } 

} 
void StrdupTest()
{
    char *ptr1 = NULL, *ptr2 = NULL, *ptr3 = NULL, *ptr4 = NULL, *ptr5 = NULL, *ptr6 = NULL;
    const char *src1 = "ABCDEFG";
    const char *src2 = " my name is Rotem";
    const char *src3= "shorter then n";
    
    int test1 = 0, test2 = 0, test3 = 0;    

    ptr1 = Strdup(src1);
    ptr2 = strdup(src1);
    
    ptr3 = Strdup(src2);
    ptr4 = strdup(src2);

    ptr5 = Strdup(src3);
    ptr6 = strdup(src3);

    test1 = (strcmp(ptr1, src1) == strcmp(ptr2, src1));
    test2 = (strcmp(ptr3, src2) == strcmp(ptr4, src2));
    test3 = (strcmp(ptr5, src3) == strcmp(ptr6, src3));
    
    free(ptr1);
    free(ptr2);
    free(ptr3);
    free(ptr4);
    free(ptr5);
    free(ptr6);


    if (test1 && test2 && test3)
    { 
        printf("function Strdup passed\n");
    }
    else
    {
        printf("Strdup failed, test1: %d, test2: %d, test3: %d\n", test1, test2, test3);
    } 

} 

void StrcatTest()
{
    
    const char *src1 = "hello world";
    char dest1[50] = "cat check one";
    char dest2[50] = "cat check one";
    const char *src2 = " my name is Rotem";
    char dest3[50] = "cat check two";
    char dest4[50] = "cat check two";
    const char *src3= "shorter then n";
    char dest5[50] = "cat check three";
    char dest6[50] = "cat check three";

    int test1 = 0, test2 = 0, test3 = 0;    

    Strcat(dest1, src1);
    strcat(dest2, src1);
    
    Strcat(dest3, src2);
    strcat(dest4, src2);

    Strcat(dest5, src3);
    strcat(dest6, src3);

    test1 = (!strcmp(dest1,dest2));
    test2 = (!strcmp(dest3,dest4));
    test3 = (!strcmp(dest5,dest6));

    if (test1 && test2 && test3)
    { 
        printf("function Strcat passed\n");
    }
    else
    {
        printf("Strcat failed, test1: %d, test2: %d, test3: %d\n", test1, test2, test3);
    } 

}
void StrncatTest()
{
    size_t n1 = 5, n2 = 0, n3 = 17;
    const char *src1 = "hello world";
    char dest1[50] = "cat check one";
    char dest2[50] = "cat check one";
    const char *src2 = " my name is Rotem";
    char dest3[50] = "cat check two";
    char dest4[50] = "cat check two";
    const char *src3= "shorter then n";
    char dest5[50] = "cat check three";
    char dest6[50] = "cat check three";

    int test1 = 0, test2 = 0, test3 = 0;    

    Strncat(dest1, src1, n1);
    strncat(dest2, src1, n1);
    
    Strncat(dest3, src2, n2);
    strncat(dest4, src2, n2);

    Strncat(dest5, src3, n3);
    strncat(dest6, src3, n3);

    test1 = (!strcmp(dest1,dest2));
    test2 = (!strcmp(dest3,dest4));
    test3 = (!strcmp(dest5,dest6));

    if (test1 && test2 && test3)
    { 
        printf("function Strncat passed\n");
    }
    else
    {
        printf("Strncat failed, test1: %d, test2: %d, test3: %d\n", test1, test2, test3);
    } 

}  


void PilandromTest()
{
    int test1=0, test2=0, test3=0, test4=0, test5=0;
    
    char *str1 = "abba";
    char *str2 = "abBa";
    char *str3 = "abcba";
    char *str4 = "";
    char *str5 = "ma ma";
    
    
    test1 ==(SUCCESS == IsPilandrom( str1 ));
    test2 ==(FAIL == IsPilandrom( str2 ));
    test3 ==(SUCCESS == IsPilandrom( str3 ));
    test4 ==(FAIL == IsPilandrom( str4 ));
    test5 ==(FAIL == IsPilandrom( str5 ));
    
    
    if(!test1 && !test2 && !test3 && !test4 && !test5)
    {
        printf("the IsPilandrom function passed the tests\n");  
    
    }
    else
    {
        printf("IsPilandrom failed!, test1=%d, test2=%d, test3=%d, test4=%d, test5=%d \n",test1,test2,test3,test4,test5);
    
    }
}
 */   
    
    



    
