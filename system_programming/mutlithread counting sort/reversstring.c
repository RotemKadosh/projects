#include <stdio.h>
#include <assert.h>
#include <string.h>

void RecRevers(char *start, char *end);
void revers(char *str);
void CharSwap(char *ptr1, char *ptr2);

void CharSwap(char *ptr1, char *ptr2)
{
    char temp = *ptr1;
    *ptr1 = *ptr2;
    *ptr2 = temp;
}

void revers(char *str)
{
    char *ptr_end = NULL;

    assert(NULL != str);

    ptr_end = str + strlen(str) - 1;

    RecRevers(str, ptr_end);
}

void RecRevers(char *start, char *end)
{
    assert(NULL != start);
    assert(NULL != end);

    if (end <= start)
    {
        return;
    }
    CharSwap(start, end);
    RecRevers(start + 1, end - 1);
}

int main(int argc, char ** argv)
{
    char str1[10] = "hello me!";
    revers(str1);
    printf("%s \n", str1);

}
