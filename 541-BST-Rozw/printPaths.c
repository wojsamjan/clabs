/* 
    $Revision: 56 $
    $Date: 2005-11-20 19:50:54 +0100 (nie, 20 lis 2005) $
    $URL: http://manta.univ.gda.pl/svn/wb/labs/c/541-BST-Rozw/printPaths.c $
 */

#include <stdio.h>
#include <stdlib.h>
#include "BT.h"


/*  Uwaga 1: drzewa powinny byæ budowane w funkcji `buildTree';
    przyk³adowe drzewa s± w plikach: tree[cyfra]{2}.c

    Uwaga 2: w rozwi±zaniu korzystamy z funkcji opakowuj±cej
    (ang. wrapper function) oraz funkcji pomocniczej
    wypisuj±cej ¶cie¿kê w jednym wierszu  
 */


extern struct node* buildTree();
   

/*  dla wêz³a `node' i tablicy `path' w której zapisano ¶cie¿kê
    od korzenia do wêz³a `node' (ale bez wêz³a `node')
    wypisz wszystkie ¶cie¿ki od korzenia do li¶cia  */

void printPathRecursively(struct node *node, int path[], int path_length);

/*  wypisz ¶cie¿kê `t' w jednym wierszu  */

void printTable(int t[], int len);

void printPaths(struct node* node) {
  int path[1000];  /* u³atwiamy sobie zadanie, zak³adaj±c ¿e
                      d³ugo¶ci ¶cie¿ek < 1000 */
  printPathRecursively(node,path,0);
}

void printPathRecursively(struct node *node, int path[], int path_length) {
  if (node==NULL)
    return;
  /* dopisz `node' to `path' */  
  path[path_length] = node->data;
  path_length++;

  /* je¶li `node' jest li¶ciem, to wypisz ca³± ¶cie¿kê;
     w przeciwnym wypadku przejd¼ do ¶cie¿ek w lewym i prawym poddrzewie */
  if (node->left==NULL && node->right==NULL) {
    printTable(path,path_length); 
  } else { 
    printPathRecursively(node->left,path,path_length);
    printPathRecursively(node->right,path,path_length);
  }
}

void printTable(int t[], int len) {
  int i;
  for (i=0; i<len; i++)
    printf("%d ", t[i]);
  printf("\n");
}


int main() {
  struct node* root=buildTree();
  
  printPaths(root);
  printf("\n");

  printTree(root);
  printf("\n");

  return EXIT_SUCCESS;
}
