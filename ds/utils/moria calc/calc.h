/*
 * NAME:       parser
 * AUTHORS:    OL94
 * VERSION:    0.1
 */

#ifndef __CALC_H__
#define __CALC_H__

typedef enum  
{
    SUCCESS = 0,
    MATH_ERROR,
    SYNTAX_ERROR,
    MALLOC_ERROR,
    NUM_OF_STATUS
}calc_status;

/*DESCRIPTION: 
*calculate the given expretion
*@param
*	math_exp - the exptetion to calculate. 
*	exit_status - status of the expretion.
*
*@return
*calculation of the expretion.
*/
double Calculate(const char *math_exp, int *exit_status);

#endif /*__CALC_H__*/