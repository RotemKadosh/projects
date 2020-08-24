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
	char * s_char = (char *)s;
	size_t *s_size_t = NULL;

	while (0 != ((size_t)s_char % BYTE_SIZE))
	{
		*s_char = c;
		s_char += 1;
		--n;
	}

	s_size_t = (size_t *)s_char;

	while (n > BYTE_SIZE - 1)
	{
		*s_size_t = word;
		s_size_t += 1;
		n -= BYTE_SIZE;
	}

	s_char = (char *)s_size_t;

	while (n > 0)
	{
		*s_char = c;
		s_char += 1;
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

	test1 = (0 == memcmp(memset(s11 , c1, n1), Memset(s1 , c1, n1), n1));
	test2 = (0 == memcmp(memset(s22 , c2, n2), Memset(s2 , c2, n2), n2));
	test3 = (0 == memcmp(memset(s33 , c3, n3), Memset(s3 , c3, n3), n3));

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
	
	char * dest_char = (char *)dest;
	size_t *dest_size_t = (size_t *)dest;
	char * src_char = (char *)src;
	size_t *src_size_t = (size_t *)src;
	
	while ( n > BYTE_SIZE - 1)
	{
		*dest_size_t = *src_size_t;
		dest_size_t += 1;
		src_size_t += 1;
		n -= BYTE_SIZE; 
	}
	dest_char = (char *)dest_size_t;
	src_char = (char *)src_size_t;
	while( n > 0 )
	{
		*dest_char = *src_char;
		dest_char += 1;
		src_char += 1;
		--n;
	}
	return dest;
}

void TestMemcpy()
{
	int test1 = 0, test2 = 0, test3 = 0;
	char s1[] = "hellonkjnads,.m";
	char s11[30] = {0};
	char s12[30] = {0};
	char s2[] = "mesnakjbaskjbkjh;ahf";
	char s21[30] = {0};
	char s22[30] = {0};
	char s3[] = "12334";
	char s31[30] = {0};
	char s32[30] = {0};
	int n1 = 16, n2 = 17, n3 = 4;
	test1 = (0 == memcmp(memcpy(s11 , s1, n1), Memcpy(s12 , s1, n1), n1));
	test2 = (0 == memcmp(memcpy(s21 , s2, n2), Memcpy(s22 , s2, n2), n2));
	test3 = (0 == memcmp(memcpy(s31 , s3, n3), Memcpy(s32 , s3, n3), n3));

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
	char * dest_char = (char *)dest;
	size_t *dest_size_t = (size_t *)dest;
	char * src_char = (char *)src;
	size_t *src_size_t = (size_t *)src;
	size_t count_to_start = (size_t)dest % BYTE_SIZE;
	size_t count_to_end = (n - count_to_start) % BYTE_SIZE;
	if(src > dest)
	{
		dest = memcpy(dest, src, n);
	}
	else
	{
		while (count_to_end > 0)
		{
			dest = (char *)dest + 1;
			count_to_end--;
		}

		dest_char = (char *)dest + n;
		src_char += n;
		dest_size_t = (size_t *)dest_char;
		src_size_t = (size_t *)src_char;

		while(n > BYTE_SIZE - 1)
		{
			dest_size_t -= 1;
			src_size_t -= 1;
			*dest_size_t = *src_size_t;
			n -= BYTE_SIZE;
		}

		dest_char = (char *)dest_size_t;
		src_char = (char *)src_size_t;

		while(n > 0)
		{		
			dest_char -= 1;
			src_char -= 1;
			*dest_char = *src_char;
			--n;
		}
	}
	return dest;
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
    
    test1 = (0 == memcmp(str_dest1 , str_dest2, 8));
    test2 = (0 == memcmp(str3 , str4, 5));
    test3 = (0 == memcmp(str5 , str6, 10));


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