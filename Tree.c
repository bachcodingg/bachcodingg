#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Tree.h"
#include "Node.h"

Tree *createTree()
{
  Tree *tree = (Tree *)malloc(sizeof(Tree));
  if (!tree)
  {
    printf("Error, memory allocation issue.\n");
    return NULL;
  }
  tree->root = NULL;
  return tree;
}

int treeEmpty(Tree *tree)
{
  if (tree == NULL || tree->root == NULL)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

Node *insert(Node *root, Node *newNode)
{
  if (root == NULL)
    return newNode;
  int cmp = strcmp(newNode->key, root->key);
  if (cmp < 0)
    root->left = insert(root->left, newNode);
  else if (cmp > 0)
    root->right = insert(root->right, newNode);
  else
  {
    printf("Error, Duplicate key: %s. Node not inserted.\n", newNode->key);
    free(newNode);
  }
  return root;
}

void insertNode(Tree *tree, Node *newNode)
{
  if (!tree || !newNode)
    return;
  tree->root = insert(tree->root, newNode);
}

void inorderPrint(Node *root, int n, int *count)
{
  if (!root || *count >= n)
    return;
  inorderPrint(root->left, n, count);
  if (*count < n)
  {
    printNode(root);
    (*count)++;
  }
  inorderPrint(root->right, n, count);
}

Node *search(Tree *tree, char *key)
{
  if (!tree || !key)
    return NULL;

  Node *node = tree->root;
  while (node)
  {
    int cmp = strcmp(key, node->key);
    if (cmp > 0)
      node = node->right;
    else if (cmp < 0)
      node = node->left;
    else
      return node;
  }
  return NULL;
}

Node *deleteNode(Node *root, char *key)
{
  if (root == NULL)
  {
    return NULL;
  }
  int cmp = strcmp(key, root->key);
  if (cmp > 0)
  {
    root->right = deleteNode(root->right, key);
  }
  else if (cmp < 0)
  {
    root->left = deleteNode(root->left, key);
  }
  else
  {
    if (root->left == NULL)
    {
      Node *temp = root->right;
      free(root);
      return temp;
    }
    else if (root->right == NULL)
    {
      Node *temp = root->left;
      free(root);
      return temp;
    }
    Node *temp = root->right;
    while (temp->left != NULL)
    {
      temp = temp->left;
    }
    strcpy(root->key, temp->key);
    strcpy(root->description, temp->description);
    root->right = deleteNode(root->right, temp->key);
  }
  return root;
}

void deleteKey(Tree *tree, char *key)
{
  if (!tree)
    return;
  tree->root = deleteNode(tree->root, key);
}

int loadTextFile(Tree *tree, const char *filename)
{
  FILE *file = fopen(filename, "r");
  if (!file)
  {
    perror("File not found");
    return 0;
  }
  char line[300];
  int success = 0;
  while (fgets(line, sizeof(line), file))
  {
    line[strcspn(line, "\n")] = 0;
    if (strlen(line) == 0)
    {
      continue;
    }
    char *colon = strchr(line, ':');
    if (!colon)
    {
      printf("Skipping invalid line format (missing colon): %s\n", line);
      continue;
    }
    *colon = '\0';
    char *key = line;
    char *description = colon + 1;

    if (strlen(key) == 0 || strlen(description) == 0)
    {
      printf("Skipping invalid line format (empty key or description): %s\n", line);
      continue;
    }
    Node *node = createNode(key, description);
    if (!node)
    {
      printf("Memory allocation failed for key '%s', skipping\n", key);
      continue;
    }

    insertNode(tree, node);
    success = 1;
  }

  fclose(file);
  return success;
}

void storePreorder(FILE *file, Node *node)
{
  if (!node)
  {
    return;
  }
  fprintf(file, "%s:%s\n", node->key, node->description);
  storePreorder(file, node->left);
  storePreorder(file, node->right);
}

int storeTextFile(Tree *tree, const char *filename)
{
  FILE *file = fopen(filename, "w");
  if (!file)
  {
    perror("Error: could not open file");
    return 0;
  }
  storePreorder(file, tree->root);
  fclose(file);
  return 1;
}

void freeNodes(Node *node)
{
  if (node == NULL)
  {
    return;
  }
  freeNodes(node->left);
  freeNodes(node->right);
  free(node);
}

void freeTree(Tree *tree)
{
  if (!tree)
    return;
  freeNodes(tree->root);
  free(tree);
}