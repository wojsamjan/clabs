/* 
   $Revision: 54 $
   $URL: http://manta.univ.gda.pl/svn/wb/labs/c/540-BST/maxDepth.c $
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

int maxDepth(struct node* node) {
  if (node==NULL)
    return 0;
  else {
    int ldepth=maxDepth(node->left);
    int rdepth=maxDepth(node->right);
    if (ldepth>rdepth)
      return ldepth+1;
    else
      return rdepth+1;
  }
}


int main() {
  struct node* root=buildTree();
  int depth;

  depth=maxDepth(root);
  printf("max depth = %d\n", depth);

  printTree(root);
  printf("\n");

  return EXIT_SUCCESS;
}
