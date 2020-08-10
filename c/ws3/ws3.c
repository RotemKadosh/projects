#include <stdio.h>/*print*/
#include <stdlib.h>/*malloc*/
#include <string.h> /*strdup*/
#include <ctype.h> /*islower, tolower*/
#include <assert.h> /*assert*/
#include "ws3.h"

#define FALSE 0;
#define TRUE 1;

/*declerations */
size_t CalcLength(char *envp[]);
char **CreateBuffer( size_t length);
void to_lower(char *s);
char **EnvDupToLower(char *envp[] ,char *new_env[] );
void PrintEnv( char *envp[], size_t size);
void FreeMem(char *envp[], size_t size);
char *strdup(const char *s);
void PrintEnv( char *envp[], size_t size);
int MoreThenOne(int army[], size_t size);
void killNext( int army[] ,size_t size ,size_t solider);
size_t MoveSowred(int army [],size_t size ,size_t solider);
int OneAlive(int army[], size_t size);
void InitArmy(int *army, size_t size);
size_t Josephus(size_t num_of_soldiers);
void PrintTypeSizes();
/*definitions*/

size_t CalcLength(char *envp[])
{	
	size_t i = 0;
	for (i = 0 ; 0 != *envp++ ; ++i)
	{ }
	return i;  
}

char **CreateBuffer( size_t length)
{	
	
	char **buffer = (char **)malloc(length * sizeof(char *));
	if(NULL == buffer)
	{
		printf("malloc fail");
		return NULL;
	}
	return buffer; 
}

void to_lower(char *s)
{
	while( '\0' != *s)
	{
		*s = tolower((int) *s);
		++s;
	}
}

char **EnvDupToLower(char *envp[] ,char *new_env[] )
{
	char **new_start = new_env;
	size_t i = 0;
	for(i = 0 ;0 != *envp; i++ )
	{
		*(new_env) = strdup(*envp);
		if(NULL == *(new_env))
		{
			FreeMem(envp, i);
		}
		to_lower(*new_env);
		++envp;
		++new_env;
	}
	return new_start;
}

void PrintEnv( char *envp[], size_t size)
{	
	size_t i = 0;
	for(i = 0; i < size; i++){
		printf("%s\n", *(envp+i));
	}

}

void FreeMem(char *env[], size_t size)
{
	size_t i = 0;
	for (i = 0; i < size; ++i)
	{
		free(*(env+i));    
	}
	free(env);
}

int PrintLowerEnv(char *envp[])
{
	size_t length = 0;
	char **new_env = NULL;
	assert(envp);
	length = CalcLength(envp);
	new_env = CreateBuffer(length);
	if(NULL == new_env)
	{
		return 1;
	}
	new_env = EnvDupToLower(envp, new_env);
	PrintEnv(new_env, length);
	FreeMem(new_env, length);  
	return 0;
}







int MoreThenOne(int army[], size_t size)
{
	size_t counter = 0;
	size_t i =0;
	for(i = 0; i < size; ++i )
	{
		if(1 == army[i])
		{
			++counter;
		}
		if(2 <=counter)
		{
			return TRUE;
		}
	}
	return FALSE;
}

void killNext( int army[] ,size_t size ,size_t solider)
{	
	size_t place = solider + 1;
	for ( ;place < size; ++place)
	{
		if(1 == army[place])
		{
			army[place] = 0;
			return;
		}
	}
	for(place = 0; place <= solider ; ++place)
	{
			if(1 == army[place])
		{
			army[place] = 0;
			return;
		}
	}
}

size_t MoveSowred(int army [],size_t size ,size_t solider)
{
	size_t place = solider + 1;
	for ( ;place < size; ++place)
	{
		if(1 == army[place])
		{
			return place;
		}
	}
	for(place = 0; place <= solider ; ++place)
	{
			if(1 == army[place])
		{
			return place;
		}
	}
	return place;
}

int OneAlive(int army[], size_t size)
{
	size_t i = 0;
	for( ; i < size ; ++i)
	{
		if(1 == army[i])
		{
			return i;
		}
	}
	return -1;
}

void InitArmy(int *army, size_t size)
{
	size_t i = 0;
	for( ; i < size; ++i)
	{
		*(army + i) = 1;
	}
}
size_t Josephus(size_t num_of_soldiers)
{
	size_t solider = 0;
	int *army =(int *)malloc(num_of_soldiers*sizeof(int));
	InitArmy(army , num_of_soldiers);
	assert(num_of_soldiers);
	while(MoreThenOne(army, num_of_soldiers))
	{
		killNext(army, num_of_soldiers, solider);
		solider = MoveSowred(army,num_of_soldiers ,solider);
	}
	solider = OneAlive(army,num_of_soldiers);
	free(army);
	return solider;
}

void PrintTypeSizes() 
{
	int int_type;
    unsigned int un_int_type;
    float float_type;
    double double_type;
    unsigned char un_char_type;
 	char char_type;
    short short_type;
    unsigned short un_short_type;
    long long_type;
    unsigned long un_long_type;
    long double long_double_type;

    printf("Size of int: %ld bytes\n", sizeof(int_type));
    printf("Size of unsigned int: %ld bytes\n", sizeof(un_int_type));
    printf("Size of float: %ld bytes\n", sizeof(float_type));
    printf("Size of double: %ld bytes\n", sizeof(double_type));
    printf("Size of char: %ld byte\n", sizeof(char_type));
    printf("Size of unsigned char: %ld byte\n", sizeof(un_char_type));
    printf("Size of unsigned short: %ld byte\n", sizeof(un_short_type));
    printf("Size of short: %ld byte\n", sizeof(short_type));
    printf("Size of long: %ld byte\n", sizeof(long_type));
   	printf("Size of unsigned long: %ld byte\n", sizeof(un_long_type));
   	printf("Size of long double: %ld byte\n", sizeof(long_double_type));
}


