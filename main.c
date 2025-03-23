#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Node.h"
#include "Tree.h"

int main()
{
  Tree *tree = createTree();
  if (tree == NULL)
  {
    printf("Failed to create tree. Exiting...\n");
    return 1;
  }

  int choice;
  char key[30];
  char description[200];
  char filename[256];
  int n;

  do
  {
    printf("\n--(Binary Search Tree Menu)--\n");
    printf("(1) Check if tree is empty\n");
    printf("(2) Insert a node\n");
    printf("(3) Print tree (inorder)\n");
    printf("(4) Search for a key\n");
    printf("(5) Delete a node\n");
    printf("(6) Load from text file\n");
    printf("(7) Store to text file\n");
    printf("(8) Exit\n");
    printf("Please enter your choice: ");
    scanf("%d", &choice);
    getchar();

    switch (choice)
    {
    case 1:
      if (treeEmpty(tree))
      {
        printf("Tree is empty.\n");
      }
      else
      {
        printf("Tree is not empty.\n");
      }
      break;

    case 2:
      printf("Enter your key: ");
      fgets(key, sizeof(key), stdin);
      key[strcspn(key, "\n")] = 0;

      printf("Enter your description: ");
      fgets(description, sizeof(description), stdin);
      description[strcspn(description, "\n")] = 0;

      Node *newNode = createNode(key, description);
      if (newNode != NULL)
      {
        insertNode(tree, newNode);
        printf("Your node is inserted.\n");
      }
      break;

    case 3:
      printf("Enter number of nodes to print: ");
      scanf("%d", &n);
      getchar();

      if (treeEmpty(tree))
      {
        printf("Tree is empty.\n");
      }
      else
      {
        int count = 0;
        inorderPrint(tree->root, n, &count);
        printf("Printed %d nodes.\n", count);
      }
      break;

    case 4:
      printf("Enter key to search: ");
      fgets(key, sizeof(key), stdin);
      key[strcspn(key, "\n")] = 0;
      Node *result = search(tree, key);
      if (result != NULL)
      {
        printf("Found:\n");
        printNode(result);
      }
      else
      {
        printf("Key not found.\n");
      }
      break;

    case 5:
      printf("Enter key to delete: ");
      fgets(key, sizeof(key), stdin);
      key[strcspn(key, "\n")] = 0;
      deleteKey(tree, key);
      printf("Node deleted if it existed.\n");
      break;

    case 6:
      printf("Enter filename to load from: ");
      fgets(filename, sizeof(filename), stdin);
      filename[strcspn(filename, "\n")] = 0;
      if (loadTextFile(tree, filename))
      {
        printf("Data loaded successfully.\n");
      }
      else
      {
        printf("Failed to load data.\n");
      }
      break;

    case 7:
      printf("Enter filename to save to: ");
      fgets(filename, sizeof(filename), stdin);
      filename[strcspn(filename, "\n")] = 0;
      if (storeTextFile(tree, filename))
      {
        printf("Data stored successfully.\n");
      }
      else
      {
        printf("Failed to store data.\n");
      }
      break;

    case 8:
      printf("Exiting program.\n");
      break;

    default:
      printf("Invalid choice. Please try again.\n");
    }
  } while (choice != 8);

  freeTree(tree);
  return 0;
}