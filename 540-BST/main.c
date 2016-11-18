/* 
   $Revision: 49 $
   $URL: http://manta.univ.gda.pl/svn/wb/labs/c/540-BST/main.c $
*/

#include <stdio.h>
#include <stdlib.h>
#include "BT.h"        /* printTree */
#include "build123.h"


int main() {
  struct node* root;

  printf("\tBudujê drzewo  2\n");
  printf("\t              / \\\n");
  printf("\t             1   3\n");
  root= build123a();
  printTree(root);
  printf("\n");

  printf("\tBudujê drzewo  5\n");
  printf("\t              / \\\n");
  printf("\t             4   6\n");
  root= build123b();
  printTree(root);
  printf("\n");

  printf("\tBudujê drzewo  8\n");
  printf("\t              / \\\n");
  printf("\t             7   9\n");
  root= build123c();
  printTree(root);
  printf("\n");

  return EXIT_SUCCESS;
}
