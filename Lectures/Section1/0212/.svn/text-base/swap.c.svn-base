#include <stdio.h>
#include <stdlib.h>
void swap1(int a, int b)
{
  int t = a;
  a = b;
  b = t;
}

void swap2(int * a, int * b)
{
  int t = * a;
  * a = * b;
  * b = t;
}

void swap3(int * a, int * b)
{
  int * t = a;
  a = b;
  b = t;
}

void swap4(int * a, int * b)
{
  int t = a;
  a = b;
  b = t;
}

int main(int argc, char ** argv)
{
  int a = 264;
  int b = 2013;
  swap1(a, b);
  printf("a = %d, b = %d\n", a, b);

  a = 264;
  b = 2013;
  swap2(& a, & b);
  printf("a = %d, b = %d\n", a, b);

  a = 264;
  b = 2013;
  swap3(& a, & b);
  printf("a = %d, b = %d\n", a, b);

  a = 264;
  b = 2013;
  swap4(& a, & b);
  printf("a = %d, b = %d\n", a, b);
  return EXIT_SUCCESS;
}
