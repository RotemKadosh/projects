#ifndef __PARSER_H__
#define __PARSER_H__

/*DESCRIPTION: 
*   getting the next number in given expression(string) as double.
*   if next number is open parantheses the paranthese argument is modified
*   in case of error end_ptr is not modified to be after the number found
*   and zero is returned. 
*@param
*   str - pointer to the string where the number is writen.
*   end_ptr - pointer to the next location in the string after number was found
*   paranthese - pointer that will be modified in case of open paranthese 
*   instead of number in the string
*@return
*   the number that was written in thew string converted to double.
*/
double GetNum(const char *str, const char **end_ptr, char *parantheses);
/*DESCRIPTION: 
*   returns the next char of given string if this char is legit operation char:
*   +, -, *, /, ^, ), ], }, \0
*@param
* str - pointer to char
* end_ptr - pointer to the next location in the string after the char  
*@return
* on success return the operation char found
* on failure return '#' char
*/
char GetOp(const char *str,const char **end_ptr);
#endif /*_PHARSER__*/