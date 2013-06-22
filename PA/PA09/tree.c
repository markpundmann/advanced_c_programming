#include <stdio.h>
#include <stdlib.h>
#include "tree.h"


/*
 * In this program, you must NOT use while, for, goto.  If you need to
 * traverse the tree, you must use recursion.
 *
 * You cannot use global or static variables.  You will lose 1 point
 * (25% of the full score) for each global or static variable.
 *
 * You cannot use "mysterious" constants in the program. If you need
 * a constant, you have to define a symbol at the top of this file.
 *
 * You will probably write many "helper" functions in order to
 * simplify the code in readTree and writeTree.
 */ 


Tree *Tree_create(int value)
{  
  //allocate memory for new tree and set childs to NULL
  Tree *node = malloc(sizeof(Tree));
  node->value = value;
  node->left = NULL;
  node->right = NULL;
  return node;
}

void destroyTree(Tree * root)
{
  if(root != NULL)
  {
    destroyTree(root->left);
    destroyTree(root->right);
    free(root);
  }
}


Tree * Tree_insert(Tree * root, int val)
/*
 * Hint: read 10.2.2 of the course handout.
 */
{
  //Base Case
  if (root == NULL)
  {
    return Tree_create(val);
  }
  //Recursive cases
  if (val < root->value)
  {
    root->left = Tree_insert(root->left, val);
  }
  else if(val > root->value)
  {
    root->right = Tree_insert(root->right, val);
  }
  
  return root; 
}

Tree *findSuccessor(Tree *node)
{
  //base case no left node
  if(node->left == NULL)
  {
    return node;
  }
  //recursive call
  return findSuccessor(node->left);
}


Tree * Tree_delete(Tree * root, int val)
/*
 * Hint: Check the last question in the final exam of Fall
 * 2012. Blackboard - Past Exams - FinalFall2012.pdf.
 * 
 * When deleting a node, we have to consider different scenarios:
 *
 * 1. If this node has no child, release the memory occupied by this
 * node.  
 *
 * 2. If this node has only one child, make this node's parent * point
 * to this node's child and release the memory occupied by this * node.
 *
 * 3. If this node has two children, find this node's successor. The
 * successor is the node that appears immediately after this node in
 * in-order traversal. The successor must be on the right side of this
 * node.  Exchange the values of this node and the successor. Delete
 * the successor.
 *
 */
{
  //Base Case
  if(root == NULL)
  {
    return NULL;
  }
  //Recursive calls
  if(val < root->value)
  {
    root->left = Tree_delete(root->left, val);
    return root;
  }
  if(val > root->value)
  {
    root->right = Tree_delete(root->right, val);
    return root;
  }
  //at this point, we have found the deleteable node
  //case 1
  //nothing to left and right so delete this node
  if(root->left == NULL && root->right == NULL)
  {
    free(root);
    return NULL;
  }
  //case 2  left has a node, right is null
  if(root->right == NULL)
  {
    Tree *temp = root->left;
    free(root);
    return temp;
  }
  //case 3, right has a node, left is null
  if(root->left == NULL)
  {
    Tree *temp= root->right;
    free(root);
    return temp;
  }
  //case 4, both childs contain values;
  
  Tree *successor = findSuccessor(root->right);
  root->value = successor->value;
  successor->value = val;

  //delete the successor
  root->right = Tree_delete(root->right, val);


  return root;  
}


Tree * readTree(char * infile)
/*
 * The function opens a file whose name is given by the argument.
 * If fopen fails, this function returns NULL.
 *
 * The input file's format:
 * Each line contains a command an an integer.
 * c n
 * c is a command, either i (insert) or r (remove)
 * n is an integer
 *
 * If the input file contains an empty line (i.e., does not have a
 * command and an integer), the tree is not changed.
 *
 * You do not need to worry about the possibility of an invalid
 * command.  For example,
 *
 * m 34 
 *
 * will not occur in the input file.
 *
 * The function inserts or deletes the numbers based on the commands
 * in the input file.  The function returns the binary search tree
 * built based on these commands.
 *
 * Remember to close the file.
 *
 * Hint: The file may be empty. In this case, the function should
 * return NULL. It is possible that the first command is r.  Your
 * program must not crash when deleting a number from an empty tree.
 * 
 */
{
  FILE *f = fopen(infile, "r"); //open file and check for valid input
  if (f == NULL)
  {
    return NULL;
  }
  Tree *root = NULL;
  char command;
  int value;
  while(fscanf(f, "%c %d\n", &command, &value) == 2)
  { //use loop to continue scanning input and either insert or delete the value based on the command sent
    switch(command)
    {
    case 'i':
      root=Tree_insert(root, value);
      break;
    case 'r':
      root=Tree_delete(root, value);
      break;
    }

  }

  fclose(f);
  return root;
}

int preOrder(FILE *f, Tree * root)
{
  if(root == NULL)
  {
    return EXIT_SUCCESS;
  }
  if(fprintf(f, "%d\n", root->value) < 0)
  {
    return EXIT_FAILURE;
  }
  if(preOrder(f, root->left) != EXIT_SUCCESS)
  {
    return EXIT_FAILURE;
  }
  if(preOrder(f, root->right) != EXIT_SUCCESS)
  {
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;



}

int inOrder(FILE *f, Tree * root)
{
  if(root == NULL)
  {
    return EXIT_SUCCESS;
  }
  if(inOrder(f, root->left) != EXIT_SUCCESS)
  {
    return EXIT_FAILURE;
  }
  if(fprintf(f, "%d\n", root->value) < 0)
  {
    return EXIT_FAILURE;
  }
  if(inOrder(f, root->right) != EXIT_SUCCESS)
  {
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

int postOrder(FILE *f, Tree * root)
{
  if(root == NULL)
  {
    return EXIT_SUCCESS;
  }
  if(postOrder(f, root->left) != EXIT_SUCCESS)
  {
    return EXIT_FAILURE;
  }
  if(postOrder(f, root->right) != EXIT_SUCCESS)
  {
    return EXIT_FAILURE;
  }
  if(fprintf(f, "%d\n", root->value) < 0)
  {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;

}

int writeTree(char * outfile, Tree * root)
/*
 * If the tree is empty, the function creates an empty file
 * and returns EXIT_SUCCESS.
 *
 * The function opens a file whose name is given by the argument.
 *
 * If fopen fails, this function returns EXIT_FAILURE;
 *
 * The function writes the root in three traverse orders:
 * pre-order, in-order, and post-order.  
 *
 * The function closes the file and returns EXIT_SUCCESS.
 *
 * Hint: You may open the output file multiple times.  The first fopen
 * needs to use "w" and the following fopen should use "a" so that the
 * previously written content is not erased.
 *
 */
{
  FILE *f = fopen(outfile, "w");
  if(f==NULL)
  {
    return EXIT_FAILURE;
  }
  preOrder(f, root);
  inOrder(f, root);
  postOrder(f, root);

  fclose(f);  

  return EXIT_SUCCESS;
}

