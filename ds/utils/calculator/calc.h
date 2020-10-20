#ifndef __CALC_H__
#define __CLAC_H__


/*DESCRIPTION: 
* calculate the mathematical expression given in math_exp
* support operations: +, -, *, /, ^, (), [], {}.
* '\0' charecter act as '=' button.
* in case of use of parantheses:
* an open parantheses should be closed by same kind of parantheses.
* different use will resolve as syntax error
* using iligle operation such as divid a number by zero 
* will resolve to Math error
*@param
* math_exp - a string containing the mathematical expression to calculate
* exit_status - a pioter to integer that will indicate 
*               whther or not there was an error in the process of 
                evaluating the expression
*@return
* result of the given expression on success, undefine in case of failure.
*/
double Calculate(const char *math_exp, int *exit_status);


/*possible valuse of exit_status*/
enum calc_status
{
    SUCCESS = 0, 
    MATH_ERROR,
    SYNTAX_ERROR,
    MALLOC_ERROR
};

#endif /*__CLAC_H__*/