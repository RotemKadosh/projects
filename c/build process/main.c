#include <stdio.h>
#include "g.h"




int main()
{
	printf("%d\n", g_s);
	foo();
	printf("%d\n", g_s);
	return 0;	
}