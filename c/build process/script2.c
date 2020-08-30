#include <stdio.h>
int i ;
static int x1 = 3;
static int x2 = 0;
static int x3;
int x4 = 10;
int x5 = 0;
int x6;
int main(int argc, char const *argv[])
 {
 	char str1[20];
 	char *str2 = (char *)malloc(sizeof(*str2)*20);
 	char *str3 = "watever";
 	char str4[] = "whatever";
 	str3[0] = 'a';
 	return 0;
 }