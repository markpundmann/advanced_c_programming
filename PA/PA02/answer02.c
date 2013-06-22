/*
 * Please fill the functions in this file.
 */
#include "pa02.h"

/*
 * C does not initialize variables.
 *
 * int sum; 
 *
 * is different from
 *
 * int sum = 0;
 *
 * The value of sum is undefined (garbage) in the first case.
 *
 */

/* 
   array is an array of integers
   length is the length of the array (i.e. the number of elements)
  
   If an array has length elements.  The valid indexes are between 0
   and length - 1, not between 1 and length.  array[length] will
   access an invalid memory location and possibly terminate the
   program abnormally.

   This function returns the sum of the elements.
   For example, if
   array[0] is 3
   array[1] is 11
   array[2] is 9
   and length is 3
   This function should return 3 + 11 + 9 = 23.

   If the array has no element (length is 0), the function returns 0.

*/
int addElement(int * array, int length)
{
  if(length == 0)
    return 0;  
  else
  {
    return (addElement(array, length - 1) + array[length - 1]);  // adds the last spot in the array with the sum of the recursive call of an array one smaller than the current.  
  }
}
/*
 * =================================================================
 */
/* 
   array is an array of integers
   length is the length of the array (i.e. the number of elements)
  
   If an array has length elements.  The valid indexes are between 0
   and length - 1, not between 1 and length.  array[length] will
   access an invalid memory location and possibly terminate the
   program abnormally.

   This function returns the number of negative elements in the array
   For example, if
   array[0] is -3
   array[1] is 11
   array[2] is -9
   array[3] is 0
   and length is 4
   This function should return 2.
   0 is not considered as a negative number.

*/
int countNegative(int * array, int length)
{
  if(length == 0)
    return 0;
  else if (array[length - 1] < 0)
    return (countNegative(array, length - 1) + 1);  // increments the sum if the last number in the array is negative and recursively calls same method to check earlier spots
  else
    return (countNegative(array, length - 1));  // same thing as above except does not increment the sum
}
/*
 * =================================================================
 */
/* 
   array is an array of integers
   length is the length of the array (i.e. the number of elements)
  
   If an array has length elements.  The valid indexes are between 0
   and length - 1, not between 1 and length.  array[length] will
   access an invalid memory location and possibly terminate the
   program abnormally.

   This function returns 1 if the elements are increasing
   (i.e. array[i] < array[j] for all 0 <= i < j < length).  If the
   elements are not increasing, this function returns 0.

   For example, if
   array[0] is 3
   array[1] is 9
   array[2] is 11
   and length is 3
   This function should return 1.
   
   If 
   array[0] is 3
   array[1] is 11
   array[2] is 9
   and length is 3
   This function should return 0.

   If 
   array[0] is 3
   array[1] is 3
   array[2] is 9
   and length is 3
   This function should return 0.

   If the array has only one element (i.e. length is 1), the function
   returns 1.  If the array has no element (length is 0), the function
   also returns 1.

*/
int isIncreasing(int * array, int length)
{
  if(length <= 1)  //if at the end of the array
  {
    return 1;
  }
  else if ((array[length-1] > array[length-2]) && (isIncreasing(array, length-1))) //if the last two positions in the array are increasing, and all the spots before it are, return true
  {
    return 1;
  }
  else
  {
    return 0;  // else return false
  }
}
