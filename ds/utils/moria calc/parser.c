#include <assert.h> /*assert*/
#include <stdlib.h> /*strtod*/

#include "parser.h" 

#define NINE (57)
#define ZERO (48)
#define DOT (46)

double ParserGetNum(char **position)
{
	char *end_of_num = NULL;
	double num_to_return = 0;

	assert(NULL != position);

	num_to_return = strtod(*position,&end_of_num);
	*position = end_of_num;

	return num_to_return;
}

char ParserGetOp(char **position)
{
	char op = '\0';

	assert(NULL != *position);

	op = *(*position);
	++(*position);

	return op;
}

