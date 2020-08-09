#include <stdio.h>/*print*/
#include <stdlib.h>/*malloc*/
#include <string.h> /*strdup*/
#include <ctype.h> /*islower, tolower*/
#include "ws3.h"




size_t CalcLength(char *envp[])
{	
	size_t len = 0;
	size_t i = 0;
	char *s = envp[i];
	for ( ; s; ++i)
	{
		char *s = envp[i];
		len += (strlen(s)+1);
	}
	return len;  
}

char **CreateBuffer(char *envp[])
{	
	size_t length =CalcLength(envp);
	char *buffer[] = (char **)malloc(length);
	return buffer; 
}

char *to_lower(char *s)
{
	char *tmp = s;
	for(; '\0' != *tmp; ++tmp)
	{
		*tmp = tolower((int) *tmp);
	}
	return s;
}

char **EnvDupToLower(char *envp[] ,char *new_env[] )
{
	size_t i = 0;
	char *s = *envp;
	char *ns = *new_env; 
	for( ;'\0' != *s; ++i )
	{
		ns = strdup(s);
		ns = to_lower(ns);
		s = *(envp+i);
		ns = *(new_env +i);
	}
	return new_env;
}
void Print_env( char *envp[])
{	
	char *thisEnv = NULL;
	char **env = envp
	for (; *env != 0; ++env)
	{
		thisEnv = *env;
		printf("%s\n", thisEnv);    
	}
}

void FreeMem(*envp[])
{

	for (; *envp!= 0; ++envp)
	{
		free(*envp);    
	}
	free(envp);
}

int PrintLowerEnv(char *envp[])
{
	char *new_env[]=NULL;
	assert(envp);
	new_env[] = CreateBuffer(envp);
	new_env = EnvDupToLower(envp, new_env)
	Print_env(envp);
	FreeMem(envp);  
	return 0;
}


int main(int argc, char **argv, char **envp) {
	PrintLowerEnv(envp);
  return 0;
}
