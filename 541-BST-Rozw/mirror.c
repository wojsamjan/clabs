/* 
    $Revision: 59 $
    $Date: 2005-11-20 20:42:39 +0100 (nie, 20 lis 2005) $
    $URL: http://manta.univ.gda.pl/svn/wb/labs/c/541-BST-Rozw/mirror.c $
 */

#include <stdio.h>
#include <stdlib.h>
#include "BT.h"

/*  Uwaga: drzewa powinny byæ budowane w funkcji `buildTree';
    przyk³adowe drzewa s± w plikach: tree[cyfra]{2}.c
*/

extern struct node* buildTree();


void mirror(struct node *node) {
  if (node==NULL) {
    return;
  } else {
    struct node *temp;
    mirror(node->left);
    mirror(node->right);
    /* przestaw wska¼niki w wê¼le `node' */
    temp=node->left;
    node->left=node->right;
    node->right=temp;
  }
}


int main() {
  struct node* root=buildTree();

  prettyPrintTree(root);  /* orygina³ */
  printf("\n");
  mirror(root);
  prettyPrintTree(root);  /* odbicie lustrzane */
  printf("\n");

  return EXIT_SUCCESS;
}
