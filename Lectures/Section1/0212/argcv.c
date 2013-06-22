#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main(int argc, char ** argv)
{ 
  /*
    argv stores the command-line arguments.
    When you type "gcc -Wall -Wshadow prog.c -o prog",
    gcc is the command (i.e., program)
    the others are the command-line arguments.

    When you type "ls -l",
    ls is the command (i.e., program)
    "-l" is a command-line argument.

    When you type "make clean",
    make is the command (i.e., program)
    "clean" is a command-line argument.
  */
  /*
    argc and argv are provied by the run-time system (i.e., shell)

    argc is the number of argument. c = count. argc includes the
    command itself. Thus, "make clean" has two arguments, argc is 2.

    argv stores the values of the arguments. v = value.
    Each argument is a string (char *), array of characters
    argv is an arry of the arguments. Thus, argv is an array of (char *)
    argv[0] is the command, for example, "make"
    argv[1] is the first argument, for example, "clean"
  */
  /* 
     This program prints the arguments
  */
  int iter;
  printf("argc = %d\n", argc);
  for (iter = 0; iter < argc; iter ++)
    {
      printf("argv[%d] = %s\n", iter, argv[iter]);
    }
  return EXIT_SUCCESS;
}
