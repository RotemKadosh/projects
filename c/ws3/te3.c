#include <stdio.h>
#include <string.h>

char *strdup(const char *str);

int main() 
{ 
    char source[] = "GeeksForGeeks"; 

    char *target = (char *)strdup(source);

    printf("%s", target); 
    return 0; 
}