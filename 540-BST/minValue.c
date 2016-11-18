/* 
   $Revision: 54 $
   $URL: http://manta.univ.gda.pl/svn/wb/labs/c/540-BST/minValue.c $
*/

#include <stdio.h>
#include <stdlib.h>
#include "BT.h"

/*        4
         / \
        2   5
         \
          3 
*/

struct node* buildTree() {
  struct node* root=new_node(4);  
  root->left=new_node(2);
  root->right=new_node(5);
  root->left->right=new_node(3);
  return root;
}


int minValue(struct node* node) {
  struct node *current = node;

  while(current->left!=NULL)
    current=current->left;

  return current->data;
}


int main() {
  struct node* root=buildTree();
  int mv;

  mv=minValue(root);
  printf("min value = %d\n", mv);

  printTree(root);
  printf("\n");

  return EXIT_SUCCESS;
}
