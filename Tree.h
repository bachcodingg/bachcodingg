#ifndef TREE_H
#define TREE_H

#include "Node.h"

typedef struct
{
  Node *root;
} Tree;

// Tree functions
Tree *createTree();
int treeEmpty(Tree *tree);
void insertNode(Tree *tree, Node *newNode);
void inorderPrint(Node *root, int n, int *count);
Node *search(Tree *tree, char *key);
void deleteKey(Tree *tree, char *key);
int loadTextFile(Tree *tree, const char *filename);
int storeTextFile(Tree *tree, const char *filename);
void freeTree(Tree *tree);

#endif