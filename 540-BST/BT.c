/* 
    $Revision: 58 $
    $Date: 2004/04/16 18:22:47 $ 
    $URL: http://manta.univ.gda.pl/svn/wb/labs/c/540-BST/BT.c $
*/

#include <stdio.h>
#include <stdlib.h>
#include "BT.h"

struct node* new_node(int data) {
  struct node* node=malloc(sizeof(struct node));
  node->data=data;
  node->left=node->right=NULL;
  return node;
}

struct node* insert(struct node* node, int data) {
  if (node==NULL)
    return new_node(data);
  else {
    if (data<=node->data)
      node->left=insert(node->left,data);
    else
      node->right=insert(node->right,data);
    return node;  /* zwróæ niezmieniony wska¼nik do wêz³a */
  }
}

int size(struct node* node) {
  if (node==NULL)
    return 0;
  else 
    return size(node->left)+1+size(node->right);
}

int lookup(struct node *node, int target) {
  if (node==NULL) {
    return 0;
  } else {
    if (target==node->data) {
      return 1;
    } else {
      if (target<node->data)
	return lookup(node->left,target);
      else
	return lookup(node->right,target);
    }
  }
}

void printTree(struct node* node) {
  if (node==NULL)
    return;
  printTree(node->left);
  printf("%d ", node->data);
  printTree(node->right);
}

void prettyPrintTree(struct node* node) {
  printf("\n--------------------------------------------------");
  printf("\n`prettyPrintTree()' function is UNDER CONSTRUCTION");
  printf("\n--------------------------------------------------\n");
}

struct node* buildRandomTree(int number_of_nodes, int seed) {
  struct node* root=new_node(1001);  
  printf("\n--------------------------------------------------");
  printf("\n`buildRandomTree()' function is UNDER CONSTRUCTION");
  printf("\n--------------------------------------------------\n");
  return root;
}
