#include <stdio.h>
#include <stdlib.h>
#define ARRAY_LENGTH 8
void printArray(int * arr, int len)
{
  int ind;
  for (ind = 0; ind < len - 1; ind ++)
    {
      printf("%d + ", arr[ind]);
    }
  printf("%d\n", arr[len - 1]);
}

void part(int * arr, int ind, int val)
/*
  arr stores the values used in the partition
  ind which element we are going to use
  val: the value to be partitioned 
*/
{
  int first; 
  if (val == 0)
    {
      printArray(arr, ind);
      return;
    }
  for (first = 1; first <= val ; first ++ )
    {
      arr[ind] = first;
      part(arr, ind + 1, val - first);
    }
}

void parthelp(int val)
{
  int arr[ARRAY_LENGTH] = {0};
  part(arr, 0, val);
}

int main(int argc, char ** argv)
{
  parthelp(4);
  return EXIT_SUCCESS;
}
