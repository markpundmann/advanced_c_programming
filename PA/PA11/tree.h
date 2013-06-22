#ifndef TREE_H
#define TREE_H

typedef struct leaf {
    int value;
    struct leaf *left;
    struct leaf *right;
} HuffNode;
int Huff_load(char *infile, char *outfile);
void Huff_postOrderPrint(HuffNode *tree);

#endif /* tree.h */

