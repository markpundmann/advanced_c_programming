#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

int main(int argc, char *argv[])
{
  if(argc != 3)
  {
    return EXIT_FAILURE;
  }
  return Huff_load(argv[1], argv[2]);
}
