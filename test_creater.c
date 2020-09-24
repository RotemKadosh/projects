#include <stdio.h>/*printf*/
#include <assert.h>/*assert*/
#include <stdlib.h>/*fgets*/
#include <string.h>/*strcmp*/
#include <sys/stat.h>/*mkdir*/
#include "ds/vector/vector.h"



#define MAX_TEXT_TO_ADD (1000)

void AddSoftLink();
void AddMakeFile();
void AddHeader();
int LineSpliter();
void GetTheFunctionName(char *str);
void AddFunctionsDecleration();
void AddMainToTest();
void AddFunctionDefenetion();
void CreatCFile();
void AppendToCFile(char * function_line);
void destroy();

static Vector_t *user_vector;
static char file_name[MAX_TEXT_TO_ADD];
static char c_file_name[MAX_TEXT_TO_ADD];
static char h_file_name[MAX_TEXT_TO_ADD];


int main(int argc, char const *argv[])
{
	
	(void)argc;
	user_vector = VectorCreate(10);


	mkdir(argv[1],0777);
	strcpy(file_name,argv[1]);
	strcpy(c_file_name,argv[1]);
	strcpy(h_file_name,argv[1]);

	strcat(c_file_name,"/");
	strcat(c_file_name,argv[1]);

	strcat(h_file_name,".h");
	strcat(c_file_name,"_test.c");

	AddSoftLink();

	AddMakeFile();
	CreatCFile();
	
	AddHeader();
	LineSpliter();
	AddFunctionsDecleration();
	AddMainToTest();
	AddFunctionDefenetion();
	destroy();
	VectorDestroy(user_vector);



	return 0;

}

void AddSoftLink()
{
	char command[100]={0};
	strcpy(command,"ln -s ~/git/ds/");
	strcat(command, file_name);
	strcat(command, "/");
	strcat(command, h_file_name);
	strcat(command, " ~/git/ds/include/");
	strcat(command, h_file_name);
	system(command);
}


void AddMakeFile()
{
	FILE *file_pointer;
	char make_file_name[35];
	strcpy(make_file_name,file_name);
	strcat(make_file_name,"/makefile");
	
	file_pointer = fopen(make_file_name, "w");

	if(NULL == file_pointer)
	{
		printf("failed to open file\n");
		return ;
	}
	fputs("CC=gcc\nCFLAGS=-ansi -pedantic-errors -Wall -Wextra -g -I.\nDEPS = ", file_pointer);
	fputs(h_file_name, file_pointer);
	fputs("\nTARGET = a.out\nARCHIVE = lib.ar\nOBJ = ../test/", file_pointer);
	fputs(file_name, file_pointer);
	fputs("_test.o ", file_pointer);
	fputs(file_name, file_pointer);
	fputs(".o\nAR=ar\n\n%%.o: %%.c $(DEPS)\n\n\t$(CC) -c -o $@ $< $(CFLAGS)\n\n$(TARGET): $(OBJ)\n\t$(CC) -o $@ $^\n\n\tar r $(ARCHIVE) $(OBJ)\n\trm *.o\n\trm ../test/*.o\n\n.PHONY: clean\nclean:\n\trm *.out\n\trm *.ar\n\n.PHONY: run\nrun:\n\t./$(TARGET)\n\n.PHONY: vlg\nvlg:\n\tvalgrind --leak-check=yes --track-origins=yes ./$(TARGET)", file_pointer);
	fclose(file_pointer);
}

void AddHeader()
{
	FILE *file_pointer;
	char *header;
	file_pointer = fopen(c_file_name, "w");

	if(NULL == file_pointer)
	{
		printf("failed to open file\n");
		return ;
	}

	fseek(file_pointer, 0, SEEK_END);
	header = malloc(256);
	strcat(header,"#include \"../utils/test.h\"\n#include \"");
	strcat(header,h_file_name);
	strcat(header,"\"\n\n");
	fputs(header,file_pointer);
	fputs("\n\n/*------------------------MACRO---------------------------*/\n\n",file_pointer);
	fclose(file_pointer);
	free(header);
}

int LineSpliter()
{
	FILE *file_pointer;
	char function_line[1000];
	
	file_pointer = fopen(h_file_name, "r");


	while (fgets(function_line,MAX_TEXT_TO_ADD, file_pointer)) 
	{
        GetTheFunctionName(function_line);
        
	}

	fclose(file_pointer);


	return 1;
}

void CreatThevector(int num_of_elements)
{
	user_vector = VectorCreate(num_of_elements);
}

void GetTheFunctionName(char *str)
{
	/*int i = 0, j = 0;*/
	int i =0;
	char *fun = NULL;
	char is_typedef[9] ;
	strncpy(is_typedef, str, 7);


	if(*str != '*' && *str != '#' && *str != ' ' && *str != '/'&& *str != '\n' && *str != '\t' && 0 != strcmp(is_typedef,"typedef"))
	{
		AppendToCFile(str);

		fun = malloc(100 *sizeof(char));
		if(NULL == fun)
		{
			return;
		}

		while(*str != ' ')
		{
			++str;
		}

		while(*str == ' ' || *str == '*')
		{
			++str;
		}

		while(*str != '(' && *str != ';')
		{
			fun[i++] = *str;
			++str;
		}
		fun[i]= '\0';
		printf("fun is-> %s\n", fun);

		VectorPushBack(user_vector, (void *)fun); /*VectorDestroy(user_vector);*/
	}
}

void AddFunctionsDecleration()
{
	size_t i = 0, j = 0;
	char *line = NULL;
	FILE *file_pointer;
	i = VectorSize(user_vector);

	file_pointer = fopen(c_file_name, "a+");
	if(NULL == file_pointer)
	{
		printf("failed to open file\n");
		return ;
	}

	fputs("/*---------------FUNCTION DECLERATION---------------------*/\n\n",file_pointer);
	for(j = 1; j <= i; ++j)
	{
		line = (char*)malloc(256 * sizeof(char));
		if(NULL == line)
		{
			return;
		}

		strcat(line,"static test_status_t ");
		strcat(line, (char*)VectorGetElement(user_vector,j));
		strcat(line,"Test(void);\n");

		fputs(line,file_pointer);
		free(line);
	}
	fclose(file_pointer);
}

void AddMainToTest()
{
	size_t i = 0, j = 0;
	char *line = NULL;
	FILE *file_pointer;
	i = VectorSize(user_vector);
	
	file_pointer = fopen(c_file_name, "a+");

	if(NULL == file_pointer)
	{
		printf("failed to open file\n");
		return ;
	}
	fputs("\n/*-------------------------MAIN---------------------------*/\n",file_pointer);
	fputs("\n\nint main()\n{\n",file_pointer);
	for(j = 1; j <= i; ++j)
	{
		line = (char*)malloc(256 * sizeof(char));
		if(NULL == line)
		{
			return;
		}   
		strcat(line,"\tRUNTEST(");
		strcat(line, (char*)VectorGetElement(user_vector,j));
		strcat(line,"Test);\n");
		fputs(line,file_pointer);
		free(line);
	}
	fputs("\n\treturn PASSED; \n}\n",file_pointer);

	fputs("\n/*--------------------------------------------------------*/\n\n",file_pointer);

	fclose(file_pointer);
}

void AddFunctionDefenetion()
{
	size_t i = 0, j = 0;
	char *line = NULL;
	FILE *file_pointer;
	i = VectorSize(user_vector);
	
	file_pointer = fopen(c_file_name, "a+");
	if(NULL == file_pointer)
	{
		printf("failed to open file\n");
		return ;
	}

	for(j = 1; j <= i; ++j)
	{
		line = (char*)malloc(256 * sizeof(char));
		if(NULL == line)
		{
			return;
		}
		strcat(line,"static test_status_t ");
		strcat(line, (char*)VectorGetElement(user_vector,j));
		strcat(line,"Test(void)\n{\n\tREQUIRE(1 == 1);\n\n\treturn PASSED;\n}");
	

		fputs(line,file_pointer);
		fputs("\n/*--------------------------------------------------------*/\n\n",file_pointer);
		free(line);
	}
	fclose(file_pointer);
}

void CreatCFile()
{
	FILE *file_pointer;
	char the_c_file_name[35];
	strcpy(the_c_file_name,file_name);
	strcat(the_c_file_name,"/");
	strcat(the_c_file_name,file_name);
	strcat(the_c_file_name,".c");
	

	file_pointer = fopen(the_c_file_name, "w");

	if(NULL == file_pointer)
	{
		printf("failed to open file\n");
		return ;
	}

	fputs("#include \"",file_pointer);
	fputs(h_file_name,file_pointer);
	fputs("\"\n\n/*------------------------MACRO---------------------------*/\n\n",file_pointer);
	fputs("/*---------------FUNCTION DECLERATION---------------------*/\n\n",file_pointer);
	fputs("/*-----------------------TYPEDEF--------------------------*/\n\n",file_pointer);
	fputs("/*-----------------------STRUCTS--------------------------*/\n\n",file_pointer);
	fputs("struct $\n{\n\n};",file_pointer);
	fputs("\n\n/*--------------------------------------------------------*/\n",file_pointer);
	fclose(file_pointer);


}
void AppendToCFile(char * function_line)
{
	FILE *file_pointer;
	char the_c_file_name[35];
	strcpy(the_c_file_name,file_name);
	strcat(the_c_file_name,"/");
	strcat(the_c_file_name,file_name);
	strcat(the_c_file_name,".c");
	
	file_pointer = fopen(the_c_file_name, "a+");
	if(NULL == file_pointer)
	{
		printf("failed to open file\n");
		return ;
	}
	fputs("\n",file_pointer);
	fputs(function_line,file_pointer);
	fputs("{\n\n}",file_pointer);
	fputs("\n/*--------------------------------------------------------*/\n",file_pointer);
	fclose(file_pointer);


}

void destroy()
{
	size_t i = 0, j = 0;
	i = VectorSize(user_vector);
	for(j = 1; j<=i; ++j)
	{
		free(VectorGetElement(user_vector,j));
	}
}