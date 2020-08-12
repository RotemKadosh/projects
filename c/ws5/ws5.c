#include <stdio.h>/*printf , stdin , fgets , fputs */
#include <assert.h> /* assert */

#define ELEMENTS (10)
#define DEFAULT (4)
#define MAX_LINE_SIZE (100)
#define TRUE (1)

typedef struct print_me
{
	int x;
	void(*Print)(int); 
} print_me ;


typedef struct oper
{
	char *name;
	int (*Compare)(const char *str1 , const char *str2);
	int (*operation)(const char *filename);
} oper;

/*enum status {ERROR = -1 , SUCCESS = 0, _EOF = EOF ,NULL_PTR = NULL};*/

char line[MAX_LINE_SIZE];
oper actions[5];
int flag_exit;

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


int RemoveFile(const char *filename)
{
	
	return remove(filename);
}

int CountLines (const char *filename)
{
	FILE *fp = NULL	;
	int count = 0;
	char c;
	fp = fopen(filename, "r");
	if (NULL == fp)
	{
		return -1;
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
    fclose(fp); 
    printf("the number of lines in %s file is: %d\n", filename, count);
    return 0;
}

int AppendFirst (const char * filename)
{
	char *new_name;
	FILE *fp_origin = NULL	;
	FILE *fp_new = NULL	;
	fp_origin = fopen(filename , "r+");
	if (NULL == fp_origin)
	{
		return -1;
	}
	new_name = "new_name";
	fp_new = fopen(new_name, "a+");
	if (NULL == fp_new)
	{
		return -1;
	}
	fputs( line + 1 , fp_new);
	while(NULL != fgets(line, MAX_LINE_SIZE, fp_origin))
	{
		fputs(line , fp_new);
	}
	fclose(fp_origin);
	remove(filename);
	rename(new_name, filename);
	fclose(fp_new);
	return 0;
}

int WriteLine(const char * filename)
{
	FILE *fp = NULL	;
	fp = fopen(filename , "a+");
	if (NULL == fp)
	{
		return 	-1;
	}
	fputs(line, fp);
	fclose(fp);
	printf("line been weiten\n");
	return 0;
}
int Exit(const char *filename)
{
	const char *p = filename;
	++p;
	flag_exit = 1;
	return 0;
}

void InitLogActions()
{
	oper remove = {"-remove\n" , Strcmp , RemoveFile};
	oper write = {"write", Strcmp , WriteLine };
	oper count = {"-count\n", Strcmp ,CountLines};
	oper exit = {"-exit\n" , Strcmp, Exit};
	oper append_first = { "<", StrOnecmp , AppendFirst};
	actions[0] = remove;
	actions[1] = count;
	actions[2] = exit;
	actions[3] = append_first;
	actions[4] = write;
}
void Logger(const char *filename)
{
	
	int num_of_actions = sizeof(actions)/sizeof(actions[0]);
	int i = 0;
	oper op;
	flag_exit = 0;
	InitLogActions();
	while(TRUE != flag_exit)
	{
		fgets(line, 100, stdin);
		for( i = 0; i < num_of_actions ; ++i)
		{
		op = actions[i];
		if(0 == op.Compare(line , op.name))
		{
			op.operation(filename);
			break;
		}
		if(DEFAULT == i)
		{
			printf("writeline been called\n");
			op.operation(filename);
			printf("writeline return\n");
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





