#include <stdio.h>
#include <unistd.h>

int main(int argc, char  **argv, char **envp)
{
	int *p = NULL;
	int *p2 = NULL;
	int i = 7;
	int j = 12;
	int k = 15;
	FILE *fp;
	printf("%d\n", j+k);
	p2 = &j;
	p = &i;


	
	if (0 == (fp = fopen("stoopid", "w")))
	{
		printf("well, that didn\'t work!\n");
		return -1;
	}
	fprintf(fp, "%p\n", p);
	if(fclose(fp))
	{
		printf("oh well");
		return -1;
	}
	
	sleep(30);

	return 0;
}