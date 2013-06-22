#include <stdio.h>
#include <stdlib.h>
int f(int n)
{
  printf("calling f(%d)\n", n);
  int a, b, c;
  if ((n == 0) || (n == 1)) /* if n is 0 or n is 1 */
    {
      return 1;
      /* the function will not execute any line below return */
      /* terminating condition */
    }
  a = f(n - 1);
  b = f(n - 2);
  c = a + b;
  return c;
}

int main(int argc, char * * argv)
{
  int a;
  a = f(4);
  printf("a = %d\n", a);
  return EXIT_SUCCESS;
}
