#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tree.h"

typedef struct StackNode
{
  //Create a structure Stack
  HuffNode *node;
  struct StackNode *next;
} Stack;

Stack *Stack_push(Stack *stack, HuffNode *node)
{
  //Creates a new item and pushes on top of the stack
  Stack *item = malloc(sizeof(Stack));
  item->node=node;
  item->next=stack;
  return item;
}

Stack *Stack_pop(Stack *stack)
{
  //Check to see if the stack is empty
  if(stack==NULL)
  {
    return NULL;
  }
  //move the current top of the stack to the next element
  //then, free the current top element
  //finally return the current top element
  Stack *next = stack->next;
  free(stack);
  return next;
}

HuffNode *Stack_peek(Stack *stack)
{
  //check to see if the stack is empty
  if(stack==NULL)
  {
    return NULL;
  }
  //else return the top stack element
  return stack->node;
}

int Stack_getCount(Stack *stack)
{
  //check to see if the stack is empty
  if(stack==NULL)
  {
    return 0;
  }
  //else recursively call this method with the next stack element + 1
  //thereby iterating through the stack and totalling the elements
  return 1 + Stack_getCount(stack->next);
}


HuffNode *Huff_create(int value)
{
  //create a huffmans node with the inputs value and initialize the branches to null
  //return the node
  HuffNode *node = malloc(sizeof(HuffNode));
  node->value = value;
  node->right = NULL;
  node->left = NULL;
  return node;
}

HuffNode *Huff_createNode(HuffNode *left, HuffNode *right)
{
  //creates a huffmans node based on the left and right branches and set the value to 0
  HuffNode *node = Huff_create(0);
  node->left = left;
  node->right = right;
  return node;
}
  

void HuffNode_destroy(HuffNode *node)
{
  //free the memory for the node
  free(node);
}

void HuffNode_destroyTree(HuffNode *node)
{
  //check to see if the input node is empty
  if(node==NULL)
  {
    return;
  }
  //else recursively call this method down each branch
  //then free free the current node
  HuffNode_destroyTree(node->left);
  HuffNode_destroyTree(node->right);
  HuffNode_destroy(node);
}

int Huff_load(char *filename)
{
  //open the file and check to see if it is an actual input
  FILE *f = fopen(filename, "r");
  if(f==NULL)
  {
    return EXIT_FAILURE;
  }
 
  //initialize a stack and int variable
  int ch;
  Stack *stack = NULL;

  //use a loop to iterate through the input file
  while((ch = fgetc(f)) != EOF) 
  {
    //if value is 1, get the next character
    if(ch == '1')
    {
      ch = fgetc(f);
      if(ch == EOF)
      {
        return EXIT_FAILURE;
      }
      //push a node containing the character onto the stack
      stack = Stack_push(stack, Huff_create(ch));
    }
    else if(ch == '0')
    {
      //if the stack contains only one element, the huffman tree is complete and we are done (break)
      if(Stack_getCount(stack) == 1)
      {
        break;
      }
      //the first element of the stack is the right element
      //store that as a variable and pop it off
      //then, get the left element of the stack and pop that off
      //finally, push the two branches onto the stack
      HuffNode *right = Stack_peek(stack);
      stack = Stack_pop(stack);
      HuffNode *left = Stack_peek(stack);
      stack = Stack_pop(stack);
      stack = Stack_push(stack, Huff_createNode(left, right));

    }
    else
    {
      fclose(f);
      return EXIT_FAILURE;
    }
  }
  //create a tree variable from the top of the stack
  //then, erase the stack
  //and print the tree
  //and finally erase the tree
  HuffNode *tree = Stack_peek(stack);
  stack = Stack_pop(stack);
  Huff_postOrderPrint(tree);
  HuffNode_destroyTree(tree);

  fclose(f);
  return EXIT_SUCCESS;

}


/* DO NOT MODIFY THIS FUNCTION!!! */
void Huff_postOrderPrint(HuffNode *tree)
{
    // Base case: empty subtree
    if (tree == NULL) {
		return;
    }

    // Recursive case: post-order traversal

    // Visit left
    printf("Left\n");
    Huff_postOrderPrint(tree->left);
	printf("Back\n");
    // Visit right
    printf("Right\n");
    Huff_postOrderPrint(tree->right);
	printf("Back\n");
    // Visit node itself (only if leaf)
    if (tree->left == NULL && tree->right == NULL) {
		printf("Leaf: %c\n", tree->value);
    }
    

}
