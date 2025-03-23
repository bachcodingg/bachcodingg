#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Node.h"

Node *createNode(char *key, char *description)
{
  Node *newNode = (Node *)malloc(sizeof(Node));
  if (!newNode)
  {
    printf("Error, allocation failed\n");
    return NULL;
  }

  if (key == NULL || description == NULL)
  {
    char tempKey[30];
    char tempDesc[200];

    printf("Enter the key value: ");
    scanf("%29s", tempKey);
    getchar(); 

    printf("Enter the description: ");
    fgets(tempDesc, sizeof(tempDesc), stdin);
    tempDesc[strcspn(tempDesc, "\n")] = 0;

    strcpy(newNode->key, tempKey);
    strcpy(newNode->description, tempDesc);
  }
  else
  {
    strcpy(newNode->key, key);
    strcpy(newNode->description, description);
  }

  newNode->left = NULL;
  newNode->right = NULL;
  return newNode;
}

void printNode(Node *node)
{
  if (node == NULL)
  {
    printf("The node is NULL.\n");
  }
  else
  {
    printf("Key: %s\nDescription: %s\n", node->key, node->description);
  }
}