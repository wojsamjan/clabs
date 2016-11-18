/* 
    $Revision: 56 $
    $Date: 2005-11-20 19:50:54 +0100 (nie, 20 lis 2005) $
    $URL: http://manta.univ.gda.pl/svn/wb/labs/c/541-BST-Rozw/hasPathSum.c $
 */

#include <stdio.h>
#include <stdlib.h>
#include "BT.h"

/*  Uwaga: drzewa powinny byæ budowane w funkcji `buildTree';
    przyk³adowe drzewa s± w plikach: tree[cyfra]{2}.c
*/

extern struct node* buildTree();


/* odejmij liczbê umieszczon± w `node->data' od `sum'
   przechodz±c rekurencyjnie w dó³ drzewa; 
   sprawd¼ czy `sum' jest równe 0 po przej¶ciu ca³ej ¶cie¿ki */

int hasPathSum(struct node* node, int sum) {
  if (node==NULL) {
    return (sum==0);
  } else {
    sum -= node->data;
    return hasPathSum(node->left, sum) || hasPathSum(node->right, sum);
  }
}


int main() {
  struct node* root=buildTree();
  int sum;

  sum=8;
  
  if (hasPathSum(root, sum))
    printf("drzewo zawiera ¶cie¿kê od korzenia do li¶cia o sumie %d\n", sum);
  else
    printf("drzewo NIE zawiera ¶cie¿ki od korzenia do li¶cia o sumie %d\n", sum);

  printTree(root);
  printf("\n");

  return EXIT_SUCCESS;
}
