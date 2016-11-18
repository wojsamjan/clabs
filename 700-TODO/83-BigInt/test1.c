/*   Plik:  test1.c
   Wersja:  4 XII 2002 */

#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "mem.h"

void show_int(void **, void *);
void mult(void **, void *);

int main() {
  List_T p1, p2;
  int *n, *m, *k;
  NEW(n); *n=2;
  NEW(m); *m=2002;
  NEW(k); *k=4;
  p1=List_list(n,m,NULL); /* 2 2002 */
  //  List_map(p1,show_int,stderr);
  //  p1=List_push(p1,k);
  *m=1999;
  List_map(p1,show_int,stderr);
  p2=List_reverse(List_copy(p1));
  List_map(p2,show_int,stderr);
  p2=List_pop(p2,(void **)&n);
  printf("\t[%d]\n",*n);

  return EXIT_SUCCESS;
}

void show_int(void **x, void *cl) {
  const int **n;
  FILE *fp;
  n=(const int **)x;
  fp=cl;
  fprintf(fp,"\t%d\n",**n);
}
