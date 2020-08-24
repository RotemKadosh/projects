#include <stdio.h> /* printf */
#include <string.h> /* strcmp , memset , memcpy, memmove, strdup*/
#include <stdlib.h> /* malloc, free */

#define BYTE_SIZE (8)
char *strdup(const char * str);
long CreateWord(int c);

void *Memset(void *s, int c, size_t n);
void *Memcpy(void *dest, void *src, size_t n);
void *Memmove(void *dest, void *src, size_t n);

void TestMemset();
void TestMemcpy();
void TestMemmove();

int main()
{
	TestMemset();
	TestMemcpy();
	TestMemmove();
	return 0;
}

long CreateWord(int c)
{
	long res = 0;
	size_t i = 0;

	for( i = 0 ; i < sizeof(size_t); ++i)
	{
		res <<= BYTE_SIZE;
		res = (res | (unsigned char)c);

	}
	return res;
}

void *Memset(void *s, int c, size_t n)
{
	void *start = s;	
	long word = CreateWord(c);
	while (0 != ((size_t)s % BYTE_SIZE))
	{
		*(char *)s = c;
		*(char *)&s += 1;
		--n;
	}
	while (n > BYTE_SIZE - 1)
	{
		*(char *)s = word;
		*(char *)&s += BYTE_SIZE;
		n -= BYTE_SIZE;
	}
	while (n > 0)
	{
		*(char *)s = c;
		*(char *)&s += 1;
		--n;
	}
	return start;
}

void TestMemset()
{
	int test1 = 0, test2 = 0, test3 = 0;
	char s1[] = "hello hello hello hello hello hello hel";
	char s11[] = "hello hello hello hello hello hello hel";
	char s2[] = "hello hello             hello hello hel";
	char s22[] = "hello hello             hello hello hel";
	char s3[] = "hello hello                            ";
	char s33[] = "hello hello                            ";
	int c1 = 'a', c2 = 'c', c3 = ' ';
	int n1 = 10, n2 = 15, n3 = 20;

	test1 = strcmp(memset(s11 , c1, n1), Memset(s1 , c1, n1));
	test2 = strcmp(memset(s22 , c2, n2), Memset(s2 , c2, n2));
	test3 = strcmp(memset(s33 , c3, n3), Memset(s3 , c3, n3));

	if (test1 && test2 && test3)
	{
		printf("Memset pass\n");
	}
	else
	{
		printf("Memset failed, test1: %d, test2: %d, test3: %d\n",test1, test2, test3 );
	}
}

void *Memcpy(void *dest, void *src, size_t n)
{
	void *start = dest;
	while ( n > BYTE_SIZE - 1)
	{
		*(size_t *)dest = *(size_t *)src;
		*(char *)&dest += BYTE_SIZE;
		*(char *)&src += BYTE_SIZE;
		n -= BYTE_SIZE; 
	}
	while( n > 0 )
	{
		*(char *)dest = *(unsigned char *)src;
		*(char *)&dest += 1;
		*(char *)&src += 1;
		--n;
	}
	return start;
}

void TestMemcpy()
{
	int test1 = 0, test2 = 0, test3 = 0;
	char s1[] = "hellonkjnads,.m";
	char s11[30] = {0};
	char s12[30] = {0};
	char s2[] = "me nakjbaskjbkjh;ahf";
	char s21[30] = {0};
	char s22[30] = {0};
	char s3[] = "12334";
	char s31[30] = {0};
	char s32[30] = {0};
	int n1 = 16, n2 = 17, n3 = 4;
	test1 = (0 == strcmp(memcpy(s11 , s1, n1), Memcpy(s12 , s1, n1)));
	test2 = (0 == strcmp(memcpy(s21 , s2, n2), Memcpy(s22 , s2, n2)));
	test3 = (0 == strcmp(memcpy(s31 , s3, n3), Memcpy(s32 , s3, n3)));

	if (test1 && test2 && test3)
	{
		printf("Memcpy pass\n");
	}
	else
	{
		printf("Memcpy failed, test1: %d, test2: %d, test3: %d\n",test1, test2, test3 );
	}
}

void *Memmove(void *dest, void *src, size_t n)
{
	void *dest_start = dest ;
	
	size_t count_to_start = (size_t)dest % BYTE_SIZE;
	size_t count_to_end = (n - count_to_start) % BYTE_SIZE;
	if(src > dest)
	{
		dest = memcpy(dest, src, n);
	}
	else
	{
		*(char *)&dest += n;
		*(char *)&src += n;

		while (count_to_end > 0)
		{
			*(char *)&dest -= 1;
			*(char *)&src -= 1;
			*(char *)dest = *(char *)src;
			--n;
			count_to_end--;
		}
		while(n > count_to_start)
		{
			*(char *)&dest -= BYTE_SIZE;
			*(char *)&src -= BYTE_SIZE;
			*(size_t *)dest = *(size_t *)src;
			n -= BYTE_SIZE;
		}
		while(n > 0)
		{		
			*(char *)&dest -= 1;
			*(char *)&src -= 1;
			*(char *)dest = *((char *)src);
			--n;
		}
	}
	return dest_start;

}

void TestMemmove()
{

    int test1 = 0, test2 = 0, test3 = 0;
    
    char *str = strdup("hello hello hello");
    char *str2 = strdup("hello hello hello");
    char *str1 = strdup("hello hello hello");
    char *str7 = strdup("hello hello hello");
    char *str_dest1 = (char *)malloc(sizeof(char)*21);
    char *str_dest2 = (char *)malloc(sizeof(char)*21);
    char *str3 = NULL;
    char *str4 = NULL;
    char *str5 = NULL;
    char *str6 = NULL;
    if(NULL == str || NULL == str2 || NULL == str1 ||
       NULL == str7 || NULL == str_dest1 || NULL == str_dest2)
    {
    	return;
    }

    

    str_dest1 = Memmove(str_dest1, str, 8);
    str_dest2 = memmove(str_dest2, str2, 8);
    str3 = Memmove(str + 2, str, 5);
    str4 = memmove(str2 +2, str2, 5);
    str5 = Memmove(str1, str1 + 2, 10);
    str6 = memmove(str7, str7 + 2, 10);


    test1 = (0 == strcmp(str_dest1 , str_dest2));
    test2 = (0 == strcmp(str3 , str4));
    test3 = (0 == strcmp(str5 , str6));


    if (test1 && test2 && test3)
    {
        printf("Memmove passed\n");
    }
    else
    {
        printf("Memmove failed, test1: %d, test2: %d, test3: %d\n", test1, test2, test3);
    }
    free(str);
    free(str2);
    free(str1);
    free(str7);
    free(str_dest1);
    free(str_dest2);
}