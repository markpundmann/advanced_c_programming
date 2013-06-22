/*
 * Please fill the functions in this file.
 * You can add additional functions. 
 *
 * Hint: It is very likely that you need to write additonal functions.
 */

#include "pa03.h"
#include <stdio.h>
#include <stdlib.h>
/*
 * Hint: You may create additional arrays if needed.
 * The maximum size needed is specified by MAXLENGTH in pa03.h.
 */

void partition_rec(int budget, int pos, int *data)
{
  int i;
  //base case
  if(budget==0)
  {
    for(i=0; i<pos; i++)
    {
      printf("%d ", data[i]);
    }
    printf("\n");
    return;
  }
  //inductive case
  int spending;
  for(spending=1; spending <= budget; spending++)
  {
    data[pos] = spending;
    partition_rec(budget-spending, pos+1, data);
  }
}

void partition(int value)
{
  printf("partition %d\n", value);
  int data[MAXLENGTH];
  partition_rec(value, 0, data);
}
/*
 * =================================================================
 */
void subset_rec(char *charset, int pos, int*include, int length)
{
  int i;
  //base case
  if(pos==length)
  {
    int sum=0;
    for(i=0; i<length; i++)
    {
      sum+=include[i];
    }
    if(sum==0)
      return;
    for(i=0; i<length; i++)
    {
      if(include[i])
      {
        printf("%c ", charset[i]);
      }
    }
    printf("\n");
    return;
    }

  //inductive case
  include[pos]=1;
  subset_rec(charset, pos+1, include, length);

  include[pos]=0;
  subset_rec(charset, pos+1, include, length);

}

void subset(char * charset, int length)
{
  printf("subset of ");
  int include[MAXLENGTH];
  int i;
  for(i=0; i<length; i++)
  {
    printf("%C", charset[i]);
    include[i]=0;
  }
  printf("\n");
  subset_rec(charset, 0, include, length);
}


/*
 * =================================================================
 */
void swap(char *c1, char *c2)
{
  char temp;
  temp=*c1;
  *c1=*c2;
  *c2=temp;
}

void permute_rec(char *charset, int pos, int length)
{
  int i;
  //base case
  if(pos==length)
  {
    for(i=0;i<length;i++)
    {
      printf("%c ", charset[i]);
    }
    printf("\n");
    return;
  }
  
  //inductive case
  for(i=pos; i<length; i++)
  {
    swap(&charset[i], &charset[pos]);
    permute_rec(charset, pos+1, length);
    swap(&charset[pos], &charset[i]);
  }

}



void permute(char *charset, int length)
{
  printf("permute ");
  int i;
  for(i=0; i<length; i++)
  {
    printf("%c ", charset[i]);
  }
  printf("\n");
  permute_rec(charset, 0, length);
}


