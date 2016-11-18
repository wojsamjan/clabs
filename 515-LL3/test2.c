/* 
     $URL: http://manta.univ.gda.pl/svn/wb/labs/c/515-LL3/test2.c $
     $Revision: 113 $
 */

#include <stdio.h>
#include <stdlib.h>
#include <cii/list.h>
#include <cii/atom.h>

void mkatom(void **, void *);

int main() {
  List_T p2, p3;
  p2=List_push(NULL, "pan");
  p2=List_push(p2, "kotek");
  p2=List_push(p2, "był");
  p2=List_push(p2, "chory");
  p2=List_append(p2, List_list("i leżał", NULL));
  printf("Lista p2:\n");
  List_map(p2, mkatom, stderr);

  printf("Lista p3:\n");
  p3=List_reverse(List_copy(p2));
  List_map(p3, mkatom, stderr);

  printf("Lista p2 odwrócona:\n");
  p2=List_reverse(p2);
  List_map(p2, mkatom, stderr);

  return EXIT_SUCCESS;
}

void mkatom(void **x, void *cl) {
  const char **str;
  FILE *fp;
 
  str=(const char **)x;
  fp=cl;

  *str=Atom_string(*str);
  fprintf(fp, "\t%s\n", *str);
}

