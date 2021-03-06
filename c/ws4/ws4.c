#include <stdio.h>/*printf, scanf*/
#define EXIT (0)
#define ESC (27)
#define IF_ELSE (1)
#define SWITCH_CASE (2)
#define LUT (3)
#define _A (65)
#define _T (84)
#define TRUE (1)

void IfElse();
void SwitchCase();
void A();
void T();
void Esc();
void Lut();

int main()
{
	
	int choise = 0;
	while(TRUE)
	{
		printf("for if else press 1\nfor switch case press 2\nfor LUT press 3\nfor exit press 0\n");

		scanf(" %d" , &choise);
		switch(choise)
		{
		case IF_ELSE:
			IfElse();
			break;
		case SWITCH_CASE:
			SwitchCase();
			break;
		case LUT:
			Lut();
			break;
		default:
			printf("not an option\n");
		}
	}
	system('stty -icanon -echo');
	return 0;
}

void DisableTerminalBufferAndEcho()
{
	system('stty -icanon -echo');
}
void EnableTerminalBufferAndEcho()
{
	system('stty icanon echo');
}
void IfElse()
{
	char key = 0;
	while(key != _ESC)
	{
		printf("press a key:\n");
		scanf(" %c", &key);
		if( _T == (int)key )
		{
			printf("T was pressed\n");
		}
		else if( _A == (int)key)
		{
			printf("A was pressed\n");
		}
		else if(_ESC == (int)key)
		{
			printf("good bey!\n");
			return;
		}
		else
		{
			printf("not an option for IfElse, try again...\n");
			
		}	
	}
}

void SwitchCase()
{
	char key = 0;
	while(_ESC != (int)key)
	{
		printf("press a key:\n");
		scanf(" %c", &key);
		switch ((int)key)
		{
		case _T:
			printf("T was pressed\n");
			break;
		case _A:
			printf("A was pressed\n");
			break;
		case _ESC:
			printf("goodbey\n");
			break;
		default:
			printf("not an option for SwitchCase, try again...\n");
		}	
	}		
}

void A()
{
	printf("A was pressed\n");
}

void T()
{
	printf("T was pressed\n");
}

void Esc()
{

	return;
}

void Lut()
{

	char key = 0;
	void (*fun_ptr_arr[256])(void) = { NULL };
	fun_ptr_arr[ _A ] = A;
	fun_ptr_arr[ _T ] = T;
	fun_ptr_arr[ _ESC ] = Esc;
	while( _ESC != (int)key)
	{
		printf("press a key:\n");
		scanf(" %c", &key);
		if(NULL == fun_ptr_arr[(int)key])
		{
			printf("not an option for lut\n");
		}
		else
		{
			(*fun_ptr_arr[(int)key])();
		}
	}	
}


