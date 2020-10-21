#include <stdio.h>
#include <unistd.h>

int main(int argc, char  **argv, char **envp)
{
	int *p = NULL;
	int *p2 = NULL;
	int i = 8;
	int j = 16;
	int k = 32;
	FILE *fp;
	printf("%d\n", k+i);
	p = &j;
	p2 = &i;
	

	
	if (0 == (fp = fopen("stoopid", "r")))
	{
		printf("well, that didn\'t work!\n");
		return -1;
	}
	fscanf(fp, "%p\n", &p);
	if(fclose(fp))
	{
		printf("oh well");
		return -1;
	}
	printf("%d\n", k+i);
	printf( "p points to: %d\n", *p);

	return 0;
}

