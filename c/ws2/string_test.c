#include <stdio.h> /*printf*/
#include <assert.h> /*for assert*/
#include <stddef.h> /* size_t */
#include <ctype.h>  /*for tolower*/
#include <stdlib.h> /*fot malloc*/
#include <string.h> /*for testing -should be moved*/
#include "String.h" 

#define SUCCESS 0
#define FAIL 1

#define TRUE 1
#define FALSE 0

char *strdup(const char *s);
int strcasecmp(const char *str1, const char *str2);
char *strtok(char *str, const char *delim);

void StrcpyTest();
void StrncpyTest();
void StrcasecmpTest();
void StrchrTest();
void StrdupTest();
void StrcatTest();
void StrncatTest();
void StrstrTest();
void StrspnTest();
void PilandromTest();
void StrtokTest();

int main(int argc, char *argv[])
{
    StrcpyTest();
    StrncpyTest();
    StrcasecmpTest();
    StrchrTest();
    StrdupTest();
    StrcatTest();
    StrncatTest();
    StrstrTest();
    StrspnTest();
    PilandromTest();
    SevenBoom(0 , 21);
    SevenBoom(6 , 47);
    StrtokTest();



    return 0;
}

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

    const char *src3 = "shorter then n";
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

    test1 = (!strcmp(dest1, dest2));
    test2 = (!strcmp(dest3, dest4));
    test3 = (!strcmp(dest5, dest6));

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

    test1 = (!strcmp(dest1, dest2));
    test2 = (!strcmp(dest3, dest4));
    test3 = (!strcmp(dest5, dest6));

    if (test1 && test2 && test3)
    { 
        printf("function Strncat passed\n");
    }
    else
    {
        printf("Strncat failed, test1: %d, test2: %d, test3: %d\n", test1, test2, test3);
    } 
}  

void StrstrTest()
{
    char *ptr1 = NULL, *ptr2 = NULL, *ptr3 = NULL, *ptr4 = NULL, *ptr5 = NULL, *ptr6 = NULL;
    const char *src1 = "hello cat erer";
    const char *dest1 = "cat";
    const char *dest2 = "cat";
    const char *src2 = " my name is Rotem";
    const char *dest3 = "cat check two";
    const char *dest4 = "cat check two";
    const char *src3 = "shorter then nS";
    const char *dest5 = "Short";
    const char *dest6 = "Short";

    int test1 = 0, test2 = 0, test3 = 0;    

    ptr1 = Strstr(src1 , dest1);
    ptr2 = strstr(src1 , dest2);
    
    ptr3 = Strstr(src2 , dest3);
    ptr4 = strstr(src2 , dest4);

    ptr5 = Strstr(src3 , dest5);
    ptr6 = strstr(src3 , dest6);

    test1 = ( ptr1 == ptr2 );
    test2 = ( ptr3 == ptr4 );
    test3 = ( ptr5 == ptr6 );

    if (test1 && test2 && test3)
    { 
        printf("function Strstr passed\n");
    }
    else
    {
        printf("Strstr failed, test1: %d, test2: %d, test3: %d\n", test1, test2, test3);
    } 

} 
void StrspnTest()
{
    size_t seg1 = 0, seg2 = 0, seg3 = 0, seg4 = 0, seg5 = 0, seg6 = 0;
    const char *src1 = "hello cgcdbat erer";
    const char *dest1 = "helocer ";
    const char *dest2 = "helocer ";
    const char *src2 = " my name is Rotem";
    const char *dest3 = "L";
    const char *dest4 = "L";
    const char *src3 = "shorter then nS";
    const char *dest5 = "shorteS ";
    const char *dest6 = "shorteS ";

    int test1 = 0, test2 = 0, test3 = 0;    

    seg1 = Strspn(src1 , dest1);
    seg2 = strspn(src1 , dest2);
    
    seg3 = Strspn(src2 , dest3);
    seg4 = strspn(src2 , dest4);

    seg5 = Strspn(src3 , dest5);
    seg6 = strspn(src3 , dest6);

    test1 = ( seg1 == seg2 );
    test2 = ( seg3 == seg4 );
    test3 = ( seg5 == seg6 );

    if (test1 && test2 && test3)
    { 
        printf("function Strspn passed\n");
    }
    else
    {
        printf("Strspn failed, test1: %d, test2: %d, test3: %d\n", test1, test2, test3);
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
    
    
    test1 = (TRUE == IsPalindrom( str1 ));
    test2 = (FALSE == IsPalindrom( str2 ));
    test3 = (TRUE == IsPalindrom( str3 ));
    test4 = (TRUE == IsPalindrom( str4 ));
    test5 = (FALSE == IsPalindrom( str5 ));
    
    
    if(test1 && test2 && test3 && test4 && test5)
    {
        printf("the IsPalindrom function passed the tests\n");  
    
    }
    else
    {
        printf("IsPalindrom failed!, test1=%d, test2=%d, test3=%d, test4=%d, test5=%d \n", test1, test2, test3, test4, test5);
    }
}
void StrtokTest()
{
    int failed=0;
    char str1[] = "-this - string - needs - to - be - broken";
    char *str2[] = "also this one";
    char *str3[] = "and /also /this /one";
   
    char *delim1 = "-";
    char *delim2 = " ";
    char *delim3 = "/";
    

    char *my_ptr, *str_ptr;
    my_ptr  = Strtok(str1D, delim1);
    str_ptr = strtok(str1D, delim1);

    while(NULL != str_ptr)
    {
        printf("%s\n",*str_ptr);
        str_ptr = strtok(NULL , delim1);
    }

    /*
    while ((NULL != my_ptr || NULL != str_ptr) && 0 == failed )
    {
        if(my_ptr != str_ptr)
        {
            failed=1;
        }
        else
        {
            my_ptr  = Strtok(NULL, delim1);
            str_ptr = strtok(NULL, delim1);
        }
    }
    my_ptr  = Strtok(str2D, delim2);
    str_ptr = strtok(str2D, delim2);
    while ((NULL != my_ptr || NULL != str_ptr ) && 0 == failed )
    {
        if(my_ptr != str_ptr)
        {
            failed=2;
        }
        else
        {
            my_ptr  = Strtok(NULL, delim2);
            str_ptr = strtok(NULL, delim2);
        }
    }
    my_ptr  = Strtok(str3D, delim3);
    str_ptr = strtok(str3D, delim3);
    while ((NULL != my_ptr || NULL != str_ptr) && 0 == failed )
    {
        if(my_ptr != str_ptr)
        {
            failed=3;
        }
        else
        {
            my_ptr  = Strtok(NULL, delim3);
            str_ptr = strtok(NULL, delim3);
        }
    }
    if(0 == failed)
    {
        printf("Strtok passed the test\n");
    }
    else
    {
        printf("Strtok failed in test: %d\n", failed);
    }
*/
}
   
    
 


    
