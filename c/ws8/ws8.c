#include <stdio.h> /* printf */
#include <string.h> /* strcmp , memset */
#include <stdlib.h> /* malloc, free */

#define BYTE_SIZE (8)
long CreateWord(int c);
void *Memset(void *s, int c, size_t n);
void TestMemset();
void TestMemcpy();
void *Memcpy(void *dest, void *src, size_t n);

int main()
{
	TestMemset();
	TestMemcpy();
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
		n -= 8;
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
		n -= BYTE_SIZE; 
	}
	while( n > 0 )
	{
		*(char *)dest = *(unsigned char *)src;
		*(char *)&dest += 1;
		--n;
	}
	return start;
}

void TestMemcpy()
{
	int test1 = 0, test2 = 0, test3 = 0;
	char s1[] = "hello";
	char s11[30] = {0};
	char s12[30] = {0};
	char s2[] = "me na";
	char s21[10] = {0};
	char s22[10] = {0};
	char s3[] = "12334";
	char s31[30] = {0};
	char s32[30] = {0};
	int n1 = 6, n2 = 3, n3 = 4;
	test1 = strcmp(memcpy(s11 , s1, n1), Memcpy(s12 , s1, n1));
	test2 = strcmp(memcpy(s21 , s2, n2), Memcpy(s22 , s2, n2));
	test3 = strcmp(memcpy(s31 , s3, n3), Memcpy(s32 , s3, n3));

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
	if(src > dest)
	{
		dest = Memcpy(dest, src, n);
	}
	else
	{
		while ( n > BYTE_SIZE - 1)
		{
			*(size_t *)dest = *((size_t *)src + n);
			n -= BYTE_SIZE; 
		}
	}
}