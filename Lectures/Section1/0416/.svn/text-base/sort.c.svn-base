#include <stdio.h>
#include <stdlib.h>
#define ARRAY_SIZE 10

int compInt(const void * p1, const void * p2)
{
  int * ip1 = (int * const) p1;
  int * ip2 = (int * const) p2;
  int v1 = * ip1;
  int v2 = * ip2;
  // printf("v1 = %d, v2 = %d\n", v1, v2);
  if (v1 == v2) { return 0; }
  if (v1 < v2) { return -1; }
  return 1;
}

int compChar(const void * p1, const void * p2)
{
  char * cp1 = (char * const) p1;
  char * cp2 = (char * const) p2;
  int c1 = * cp1;
  int c2 = * cp2;
  // printf("c1 = %c, c2 = %c\n", c1, c2);
  if (c1 == c2) { return 0; }
  if (c1 < c2) { return -1; }
  return 1;
}

int main(int argc, char * * argv)
{
  int ind;
  int intArray[ARRAY_SIZE] = { 5, 4 ,7, 3, 8, 2, 1, 0, 9, 6};
  qsort(& (intArray[0]), ARRAY_SIZE, sizeof(int), compInt);
  for (ind = 0; ind < ARRAY_SIZE; ind ++)
    {
      printf("%d ", intArray[ind]);
    }
  printf("\n\n");
  char charArray[ARRAY_SIZE] = {'e', 'P', 'm', 'a', 'Q', 
			       'Z', 'k', 'C', 'Y', 'w'};
  qsort(& (charArray[0]), ARRAY_SIZE, sizeof(char), compChar);
  for (ind = 0; ind < ARRAY_SIZE; ind ++)
    {
      printf("%c ", charArray[ind]);
    }
  printf("\n\n");

  /* understand const */
  int a = 15;
  int b = 23;
  const int * p1 = & a; // cannot use p1 to change a, can change p1's value
  p1 = & b;
  // * p1 = 19; // error
  printf("* p1 = %d, a = %d, b = %d\n", * p1, a, b);

  int * const p2 = & a; // p2's value cannot change, can use p1 to change a
  * p2 = -31;
  // p2 = & b; // error
  printf("* p2 = %d, a = %d, b = %d\n", * p2, a, b);
  return EXIT_SUCCESS;
}
