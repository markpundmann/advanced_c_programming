#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

int main(int argc, char *argv[])
{
  //check to see if there are 2 inputs
  if(argc != 2)
  {
    return EXIT_FAILURE;
  }
  //load the inputs and run the compression
  Huff_load(argv[1]);
  return EXIT_SUCCESS;




}
