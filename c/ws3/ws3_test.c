#include "ws3.h"
#include <stdio.h> /*printf*/

void JosephusTest();


int main(int argc, char **argv, char **envp) 
{
	
	JosephusTest();
	PrintTypeSizes();
	PrintLowerEnv(envp);
  	return 0;
}
void JosephusTest()
{
	int test1 = 0, test2 = 0,  test3 = 0,  test4 = 0, test5 = 0,  test6 = 0,  test7 = 0;
	test1 = (5 == Josephus(6));
	test2 = (5 == Josephus(10));
	test3 = (1 == Josephus(16));
	test4 = (1 == Josephus(1));
	test5 = (1 == Josephus(2));
	test6 = (7 == Josephus(11));
	test7 = (1 == Josephus(4));


	if( test1 && test2 && test3  && test4  && test5 && test6 && test7 )
	{
		printf("fuction workes josephus lives\n");
	}
	else
	{
		printf( "joshephus die! test1: %d test2: %d test3: %d test4: %d test5: %d test6: %d test7: %d\n",test1 , test2, test3, test4, test5 , test6, test7);
	}
}