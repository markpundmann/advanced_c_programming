#include <stdio.h>
#include <stdlib.h>
#define ARRAY_SIZE 8
void printResult(int * arr, int length)
{
  int iter = 0;
  int sum = 0;
  /* if it is the empty set, do not print */
  while ((sum == 0) && (iter < length))
    {
      if (arr[iter] == 1)
	{
	  sum ++;
	}
      iter ++;
    }
  if (sum == 0)
    {
      return; 
    }
  for (iter = 0; iter < length; iter ++)
    {
      if (arr[iter] == 1)
	{
	  printf("%c ", iter + 'A');
	}
      /*
	printf("%c", 65); print 'A'
	printf("%c", 67); print 'C'
	printf("%c ", 'C' - 'A');  print 2
      */
    }
  printf("\n");
}
void sub2(int * arr, int ind, int length)
/* each element in arr is either 0 or 1 */
/* ind = 0 => 'A', 1 = > 'B' ... */
/* arr[ind] means whether the character is used or not */
/* length is the size of the original set */
{
  if (ind == length)
    {
      printResult(arr, ind);
      return;
    }
  /* select a character, do the rest */
  arr[ind] = 1;
  sub2(arr, ind + 1, length);
  /* not select a character, do the rest */
  arr[ind] = 0;
  sub2(arr, ind + 1, length);
}

void subset(int n)
{
  int arr[ARRAY_SIZE] = {0}; 
  /* each element can be 0 or 1 */
  /* arr[ind] (ind can be 0, 1, 2, ...) */
  /* arr[0] = 0, 'A' is not used */
  /* arr[0] = 1, 'A' is used */
  /* arr[1] = 0, 'B' is not used */
  /* arr[1] = 1, 'B' is used */
  sub2(arr, 0, n);
}
int main(int argc, char ** argv)
{
  subset(4);
  return EXIT_SUCCESS;
}
