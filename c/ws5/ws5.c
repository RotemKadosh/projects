#include <stdio.h>/*printf , stdin , fgets , fputs */
#include <assert.h> /* assert */

#define ELEMENTS (10)
#define DEFAULT (4)
#define MAX_LINE_SIZE (100)
#define TRUE (1)
#define FALSE (0)
#define NUM_OF_ACT (5)

typedef enum status {SUCESS, FOPEN_ERR , FCLOSE_ERR, FGETS_ERR , FGETC_ERR, FPUTS_ERR, REMOVE_ERR, RENAME_ERR, EXIT_SUCESS} status;

int Strcmp(const char *str1, const char *str2);
int StrOnecmp(const char *str1, const char *str2);
status RemoveFile(const char *filename, int *flag_exit, char *line);
status CountLines (const char *filename, int *flag_exit, char *line);
status AppendFirst (const char * filename,int *flag_exit, char *line);
status WriteLine(const char * filename,int *flag_exit, char *line);
status Exit(const char *filename, int *flag_exit, char *line);
void InitLogActions();
void Logger(const char *filename);
void Print(int member);
void Ex1();
void UnUsed(const char *filename, int *flag_exit, char *line);

typedef struct print_me
{
	int x;
	void(*Print)(int); 
} print_me ;

typedef struct oper
{
	char *name;
	int (*Compare)(const char *str1 , const char *str2);
	status (*operation)(const char *filename, int *flag_exit , char *line);
} oper;


int Strcmp(const char *str1, const char *str2)
{	
	assert(str1); 
    assert(str2);
	while('\0' != *str1 ||'\0' != *str2)
	{	
		if(*str1 == *str2)
		{
			++str1;
			++str2;
		}
		else
		{
			return(*str1 - *str2);
		}
	}
	return 0;
}

int StrOnecmp(const char *str1, const char *str2)
{	
	assert(str1); 
    assert(str2);
	return(*str1 - *str2);	
}
int WriteCmp(const char *str1, const char *str2)
{
	assert(str1);
	assert(str2);
	return 0;
}
status RemoveFile(const char *filename, int *flag_exit, char *line)
{
	UnUsed(filename, flag_exit, line);
	if(-1 == remove(filename))
	{
		return REMOVE_ERR;
	}
	return SUCESS;
}

status CountLines (const char *filename , int *flag_exit, char *line)
{
	FILE *fp = NULL;
	int count = 0;
	char c;
	fp = fopen( filename, "a+" );
	UnUsed( filename, flag_exit, line );
	if (NULL == fp)
	{
		return FOPEN_ERR;
	}
	c = getc(fp);
	while( c != EOF)
	{
        if (c == '\n') 
        {
            count = count + 1; 
        }
        c = getc(fp);
	}
	if(EOF == fclose(fp))
	{
		return FCLOSE_ERR;
	} 
    printf("the number of lines in %s file is: %d\n", filename, count);
    return SUCESS;
}

status AppendFirst (const char * filename, int *flag_exit, char *line)
{
	char *new_name;
	FILE *fp_origin = NULL;
	FILE *fp_new = NULL;
	fp_origin = fopen(filename , "r+");
	UnUsed(filename, flag_exit, line);
	if (NULL == fp_origin)
	{
		return FOPEN_ERR;
	}
	new_name = "new_name";
	fp_new = fopen(new_name, "a+");
	if (NULL == fp_new)
	{
		return FOPEN_ERR;
	}
	if(EOF == fputs( line + 1 , fp_new))
	{
		return FPUTS_ERR;
	}
	while(NULL != fgets(line, MAX_LINE_SIZE, fp_origin))
	{
		if(EOF == fputs(line , fp_new))
		{
			return FPUTS_ERR;
		}
	}
	if(EOF == fclose(fp_origin))
	{
		return FCLOSE_ERR;
	}
	if(-1 == remove(filename))
	{
		return REMOVE_ERR;
	}
	if(-1 == rename(new_name, filename))
	{
		return RENAME_ERR;
	}
	if(EOF == fclose(fp_new))
	{
		return FCLOSE_ERR;
	}
	return SUCESS;
}

status WriteLine(const char *filename, int *flag_exit, char *line)
{
	FILE *fp = NULL;
	fp = fopen(filename , "a+");
	UnUsed(filename, flag_exit, line);
	if (NULL == fp)
	{
		return 	FOPEN_ERR;
	}
	if(EOF == fputs(line, fp))
	{
		return FCLOSE_ERR;
	}
	if(EOF == fclose(fp))
	{
		return FCLOSE_ERR;
	}
	return SUCESS;
}

status Exit(const char *filename, int *flag_exit, char *line)
{

	const char *p = filename;
	UnUsed(filename, flag_exit, line);
	++p;
	*flag_exit = 1;
	return EXIT_SUCESS;
}

void InitLogActions(oper actions[])
{
	oper remove = {"-remove\n" , Strcmp , RemoveFile};
	oper write = {"write", WriteCmp , WriteLine };
	oper count = {"-count\n", Strcmp ,CountLines};
	oper exit = {"-exit\n" , Strcmp, Exit};
	oper append_first = { "<", StrOnecmp , AppendFirst};
	actions[0] = remove;
	actions[1] = count;
	actions[2] = exit;
	actions[3] = append_first;
	actions[4] = write;
}

void UnUsed(const char *filename, int *flag_exit, char *line)
{
	++filename;
	++flag_exit;
	++line;
}

void Logger(const char *filename)
{
	char line[MAX_LINE_SIZE];
	oper actions[NUM_OF_ACT];
	int flag_exit = 0;
	int i = 0;
	oper op;
	flag_exit = 0;
	InitLogActions(actions);
	while(SUCESS == flag_exit)
	{
		fgets(line, 100, stdin);
		for( i = 0; i < NUM_OF_ACT ; ++i)
		{
			op = actions[i];

			if(0 == op.Compare(line , op.name))
			{
				flag_exit = op.operation(filename, &flag_exit, line);
				break;
			}
			
		}
	}
}

int main()
{
	Logger("text.txt");
	return 0;
}

void Print(int member)
{
	printf("%d\n", member );
}

void Ex1()
{
	print_me print_me_array [ELEMENTS];
	int i = 0;
	for (i = 0; i < ELEMENTS; ++i)
	{
		print_me p ;
		p.x = i;
		p.Print = &Print;
		print_me_array[i] = p;
		print_me_array[i].Print( print_me_array[i].x );
	}
}





