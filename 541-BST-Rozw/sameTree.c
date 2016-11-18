/* 
    $Revision: 58 $
    $Date: 2005-11-20 20:06:34 +0100 (nie, 20 lis 2005) $
    $URL: http://manta.univ.gda.pl/svn/wb/labs/c/541-BST-Rozw/sameTree.c $
 */

#include <stdio.h>
#include <stdlib.h>
#include "BT.h"

/*  Uwaga 1: w wersji ostatecznej drzewa powinny byæ budowane za pomoc± 
    funkcji `buildRandomTree()' (zdefiniowanej w BT.h)
*/
extern struct node* buildTree();

int sameTree(struct node* a, struct node* b) {
  if (a==NULL && b==NULL) {
    return 1;
  } else if (a!=NULL && b!=NULL) {
    return a->data==b->data &&
      sameTree(a->left,b->left) &&
      sameTree(a->right,b->right);
  } else { 
    /* jedno z drzew puste a drugie nie */
    return 0;
  }
}

/*  Uwaga 2: w wersji ostatecznej funkcja `main()' powinna 
    zawieraæ wiêcej testów
 */

int main() {
  struct node* root_a=buildTree(); 
  struct node* root_b=buildTree();

  if (sameTree(root_a, root_b)) 
    printf("sameTree: drzewa s± TAKIE SAME\n");
  else
    printf("sameTree: drzewa s± RÓ¯NE\n");

  prettyPrintTree(root_a); 
  prettyPrintTree(root_b); 

  return EXIT_SUCCESS;
}
