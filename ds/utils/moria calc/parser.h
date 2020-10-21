/*
 * NAME:       parser
 * AUTHORS:    OL94
 * VERSION:    0.1
 */

#ifndef __PARSER_H__
#define __PARSER_H__


/*DESCRIPTION: 
*return the next valid number
*@param
*	position - location in the string. 
*
*@return
*vaid number
*/
double ParserGetNum(char **position);

/*DESCRIPTION: 
*return the operation in the location
*@param
*	position - location in the string
*	
*@return
* operation to do
*/
char ParserGetOp(char **position);


#endif /*__PARSER_H__*/