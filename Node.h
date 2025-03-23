#ifndef NODE_H
#define NODE_H

typedef struct node
{
  char key[30];
  char description[200];
  struct node *left;
  struct node *right;
} Node;
Node *createNode(char *key, char *description);
void printNode(Node *node);
#endif