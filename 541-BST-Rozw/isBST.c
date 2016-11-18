/* 
    $Revision: 59 $
    $Date: 2005-11-20 20:42:39 +0100 (nie, 20 lis 2005) $
    $URL: http://manta.univ.gda.pl/svn/wb/labs/c/541-BST-Rozw/isBST.c $
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "BT.h"

/*  Uwaga: drzewa powinny byæ budowane w funkcji `buildTree';
    przyk³adowe drzewa s± w plikach: tree[cyfra]{2}.c
*/

extern struct node* buildTree();

/*  Uwaga: w rozwi±zaniu korzystamy z funkcji opakowuj±cej */

int isBSTRecursive(struct node *node, int min, int max);

int isBST(struct node* node) {
  return isBSTRecursive(node, INT_MIN, INT_MAX);
}

/*  zwraca 1 je¶li liczby umieszczone w wêz³ach drzewa s±
    >= min  i  <= max  i drzewo o korzeniu `node' jest BST  */

int isBSTRecursive(struct node *node, int min, int max) {
  if (node==NULL)
    return 1;
  /* fa³sz: drzewo nie spe³nia warunku min-max */
  if (node->data<min || node->data>max)
    return 0;
  /* pozosta³ych przypadkach sprawd¼ poddrzewa rekurencyjnie
     u¶ci¶laj±c w ograniczenia min-max */
  return 
    isBSTRecursive(node->left, min, node->data) &&
    isBSTRecursive(node->right, node->data+1, max);
}


int main() {
  struct node* root=buildTree();

  if (isBST(root)) 
    printf("isBST: drzewo jest BST\n");
  else
    printf("isBST: drzewo NIE jest BST\n");

  printf("\n"); 
  printTree(root); 
  prettyPrintTree(root); 

  return EXIT_SUCCESS;
}
