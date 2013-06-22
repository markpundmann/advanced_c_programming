#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_LEN 10
/* 
 * A string is an array of characters but one element in the array
 * must be the special '\0' character to end the string.  '\0' is not
 * '0'.  An array of characters may not be a string.  A string must be
 * an array of characters.
 *
 * If the array does not have '\0', you cannot use it as a string. You
 * cannot use it when calling string functions (for example, strlen).
 * Otherwise, the program's behavior is undefined.  
 *
 */
void printArray(char * arr, int len)
{
  int iter;
  /* print each element as a character and an integer */
  for (iter = 0; iter < len; iter ++)
    {
      printf("arr[%d] = %2c ", iter, arr[iter]);
      printf("arr[%d] = %2d\n", iter, arr[iter]);
    }
}
int main(int argc, char ** argv)
{ 
  char chArray[MAX_LEN];
  int iter;
  /* initialize every element to '@'
     Purpose: we want to see which elements are changed. 
     chArray is not a string because no element is '\0'.
  */
  for (iter = 0; iter < MAX_LEN; iter ++)
    {
      chArray[iter] = '@';
    }
  printArray(chArray, MAX_LEN);

  printf("\nstrcpy(chArray, \"ECE\")\n");
  strcpy(chArray, "ECE");
  printArray(chArray, MAX_LEN);

  printf("\nstrlen(chArray) = %d\n", strlen(chArray));

  printf("\nstrcat(chArray, \" 264\")\n");
  strcat(chArray, " 264");
  printArray(chArray, MAX_LEN);

  printf("\nstrlen(chArray) = %d\n", strlen(chArray));

  /*
    C does not check whether the destination has enough space
  */
  
  return EXIT_SUCCESS;
}
