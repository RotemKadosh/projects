#include "string.h" 

void PilandromTest();



int main(int argc, char *argv[])
{
    ...

    return 0;
}

/* Why is it like this? */

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



    
