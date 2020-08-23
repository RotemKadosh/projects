#include <stdio.h> /* printf, sprintf */
#include <assert.h> /*assert*/
#include <stdlib.h> /*realloc, free*/
#include <string.h> /*strlen*/

#define NUM_OF_ELEMENTS (6)
#define NULL_CHAR (1)
#define CAST(type, element ) *(type *)&element->value

typedef struct element element_t;
typedef struct element_functions element_functions_t;
typedef enum status {FAIL = -1, SUCCESS = 0} status_t;

static void PrintInt(const element_t *element);
static void PrintFloat(const element_t *element);
static void PrintString(const element_t *element);

static status_t AddInt(element_t *element , int to_add);
static status_t Addfloat(element_t *element , int to_add);
static status_t AddStr(element_t *element , int to_add);

static void FreeString(element_t *element);
static void FreeIntFloat(element_t *element);

static status_t InitArray(element_t *array_of_elements);
static size_t NumOfDigits(int num);
static void PrintArray(element_t *array_of_elements);
static status_t AddToArray(element_t *array_of_elements, int to_add);
static void CleanArray(element_t *array_of_elements);
static status_t Events();
char *strdup(const char * str);


int main()
{
	if(SUCCESS != Events())
	{
		return FAIL;
	}
	return SUCCESS;
}

struct element
{
	void *value;
	const element_functions_t *func_elem;
};

struct element_functions
{
	void (*ptr_print)(const element_t *element);
	int (*ptr_add )(element_t *element , int to_add);
	void (*ptr_free)(element_t *element);
};

static element_functions_t int_functions_g = {PrintInt, AddInt, FreeIntFloat};
static element_functions_t float_functions_g = {PrintFloat, Addfloat, FreeIntFloat};
static element_functions_t string_functions_g = {PrintString, AddStr , FreeString};

static void PrintInt(const element_t *element)
{
	assert(NULL != element);
	printf("%d\n", CAST(int, element));
}
static void PrintFloat(const element_t *element)
{
	assert(NULL != element);
	printf("%f\n", CAST(float, element));
}
static void PrintString(const element_t *element)
{
	assert(NULL != element);
	printf("%s\n", (char *)element->value);
}
static status_t AddInt(element_t *element , int to_add)
{
	assert(NULL != element); 
	CAST(int, element) += to_add;
	return SUCCESS;
}
static status_t Addfloat(element_t *element , int to_add)
{
	assert(NULL != element);
	*(float *)&element->value += (float)to_add;
	return SUCCESS;
}
static status_t AddStr(element_t *element , int to_add)
{
	size_t size = 0;
	assert(NULL != element);
	size = strlen((char *)element->value) + (size_t)NULL_CHAR + NumOfDigits(to_add);
	element->value = realloc(element->value, size);
	if (NULL == element->value )
	{
		return FAIL;
	}
	if(0 > sprintf(element->value  , "%s%d",(char *) element->value , to_add))
	{
		return FAIL;
	}

	return SUCCESS;
}

static void FreeString(element_t *element)
{
	assert(NULL != element);
	free((char *)element->value);
}

static void FreeIntFloat(element_t *element)
{
	assert(NULL != element);
}
static void InitInt(element_t *element, const int input)
{
	CAST(int, element) = input;
	element->func_elem = &int_functions_g;
}
static void InitFloat(element_t *element, const float input)
{
	CAST(float, element)= input;
	element->func_elem = &float_functions_g;
}
static status_t InitString(element_t *element, char *input)
{
	element->value = (void *)strdup(input);
	if(NULL == element->value)
	{
		return FAIL;
	}
	element->func_elem = &string_functions_g;
	return SUCCESS;
}

static status_t InitArray(element_t *array_of_elements)
{
	InitInt(&array_of_elements[0],5);
	InitInt(&array_of_elements[1],10);
	InitFloat(&array_of_elements[2],12.5);
	InitFloat(&array_of_elements[3],1.2);
	if (SUCCESS != InitString(&array_of_elements[4],"hello"))
	{
		return FAIL;
	}
	if (SUCCESS != InitString(&array_of_elements[5],"hellohello"))
	{
		return FAIL;
	}

	return SUCCESS;
}

static size_t NumOfDigits(int num)
{
	size_t dig = 0;
	do
	{
		++dig;
		num /=10;
	}while(num > 0);
	return dig;
}

static void PrintArray(element_t *array_of_elements)
{
	size_t i = 0;
	for(i = 0; i < NUM_OF_ELEMENTS; ++i)
	{
		element_t el = array_of_elements[i];
		el.func_elem->ptr_print((const element_t *)&el);  
	}
}

static status_t AddToArray(element_t *array_of_elements, int to_add)
{
	size_t i = 0;
	for(i = 0; i < NUM_OF_ELEMENTS; ++i)
	{
		if(SUCCESS != array_of_elements[i].func_elem->ptr_add(&array_of_elements[i], to_add))
		{
			return FAIL;
		}
	}
	return SUCCESS;
}

static void CleanArray(element_t *array_of_elements)
{
	size_t i = 0;
	for(i = 0; i < NUM_OF_ELEMENTS; ++i)
	{
		element_t el = array_of_elements[i];
		el.func_elem->ptr_free(&el);	
	}
}

static status_t Events()
{
	element_t array_of_elements [NUM_OF_ELEMENTS] = {NULL};
	if(0 != InitArray(array_of_elements))
	{
		return FAIL;
	}

	PrintArray(array_of_elements);
	if(0 != AddToArray(array_of_elements, 10))
	{
		return FAIL;
	}
	PrintArray(array_of_elements);
	CleanArray(array_of_elements);
	return SUCCESS;
}



