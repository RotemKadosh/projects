#include <stdlib.h> /* strtod*/
#include <assert.h> 
#include "parser.h"
#define TRUE (1)
#define FALSE (0)

int IsOperator(char ch)
{
    if ('+' == ch || '-' == ch || '*' == ch || '/' == ch || ')' == ch 
        || '}' == ch || ']' == ch || '^' == ch || '\0' == ch)
    {
        return TRUE;
    }
    return FALSE;
}

int IsOpenParantheses(char ch)
{
    int res = FALSE;
    if(ch == '(' || ch =='[' || ch == '{')
    {
        res = TRUE;
    }
    return res;
}

double GetNum(const char *str, const char **end_ptr, char *parantheses)
{
    double res = 0;
       
    assert(NULL != str);
    assert(NULL != end_ptr);

    res = strtod(str, (char **)end_ptr);
    if (IsOpenParantheses(*str))
    {
         ++(*end_ptr);
         *parantheses = *str;
    }
     
    return res;

}

char GetOp(const char *str,const char **end_ptr)
{
    char res = '#';
    assert(NULL != str);
    assert(NULL != end_ptr);
    if(IsOperator(*str))
    {
       res = *str;
       ++(*end_ptr);
    }
    
    return res;
}

