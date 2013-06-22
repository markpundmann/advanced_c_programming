#include <stdio.h>
#include <stdlib.h>
#define ARRAY_LENGTH 8
void printArray(int * arr, int len)
{
  int ind;
  for (ind = 0; ind < len; ind ++)
    {
      printf("%c ", arr[ind]);
    }
  printf("\n");
}

void swap(int * a, int * b)
{
  int t = * a;
  (* a) = (* b);
  (* b) = t;
}

void permute(int * arr, int ind, int length)
{
  int iter;
  if (ind == length)
    {
      printArray(arr, length);
    }
  for (iter = ind; iter < length ; iter ++)
    {
      swap(& arr[iter], & arr[ind]);
      /*
	int t = arr[iter];
	arr[iter] = arr[ind];
	arr[ind] = t;
      */
      permute(arr, ind + 1, length);
      swap(& arr[iter], & arr[ind]);
    }
}

void permutehelp(int length)
{
  int arr[ARRAY_LENGTH] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
  /* arr is an array, arr is the address of the first element
     arr is & arr[0] */
  permute(arr, 0, length);
}

int main(int argc, char ** argv)
{
  permutehelp(4);
  return EXIT_SUCCESS;
}
