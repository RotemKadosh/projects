#include <stdio.h>/*printf*/
#include <stdlib.h>/*malloc free*/
/*global vars*/
const int const_global;
const int const_global_init = 1;
int global;
int global_init = 3;

/*global static vars*/
static const int static_const_global;
static const int static_const_global_init = 1;
static int static_global;
static int static_global_init = 3;

/*static func*/
void function(void)
{
		/*lv var*/
	const int const_local = 0;
	int local = 0;
	
	int t;
	static const int j = 1;
	static const int k = 2;
	static int l = 3;
	static int m = 4;
	printf("%lu\n",(size_t)&local);
	printf("%lu\n", (size_t)&t);
	char *string_literal = "r";
	void *heap_un_aligned = NULL;
	void *heap_aligned = NULL;
	heap_un_aligned = malloc(15);
	heap_aligned = malloc(16);

}
