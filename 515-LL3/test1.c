/* 
     $URL: http://manta.univ.gda.pl/svn/wb/labs/c/515-LL3/test1.c $
     $Revision: 110 $
 */

#include <stdio.h>
#include <stdlib.h>
#include <cii/list.h>

void print_elem(void **, void *);

int main() {
  List_T p;  /* = List_list(NULL) -- tak tworzymy pustą listę */

  p=List_list("pan", "kotek", "był", "chory", NULL);
  List_map(p, print_elem, stderr);
  return EXIT_SUCCESS;
}

void print_elem(void **x, void *cl) {
  const char **str;
  FILE *fp;
 
  str=(const char **)x;
  fp=cl;
  fprintf(fp,"\t%s\n",*str);
}

