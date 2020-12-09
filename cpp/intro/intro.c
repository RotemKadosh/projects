//#include <cstdio>
#include <stdio.h>


const struct x
{
  int i;
};

inline void foo()
{}

const struct x x1 = {6};
const struct x x2 = {9};

int main()
{
  

  x1.i = 4;


  printf("%d %d\n", x1.i, x2.i);
  return 0;
}