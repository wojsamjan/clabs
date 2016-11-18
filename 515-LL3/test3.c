/* 
     $URL: http://manta.univ.gda.pl/svn/wb/labs/c/515-LL3/test3.c $
     $Revision: 113 $
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cii/list.h>
#include <cii/atom.h>

void mkatom(void **, void *);
int compare(const void *, const void *);

int main() {
  int i;
  void **array; // char **array;
  List_T p3;

  p3=List_list("i leżał", "chory", "był", "kotek", "pan", NULL);

  printf("Lista p3 (nieuporządkowana):\n");
  List_map(p3,mkatom,stderr);

  printf("Lista p3 (uporządkowana):\n");
  array=List_toArray(p3,NULL); // array=(char **)List_toArray(p3,NULL);
  qsort(array,List_length(p3),sizeof(*array),compare);
  //  qsort(array,List_length(p3),sizeof(*array), 
  //                                         strcmp);
  //  qsort(array,List_length(p3),sizeof(*array),
  //	(int (*)(const void *, const void *))strcmp);
  for (i=0; array[i]; i++) 
    printf("\t%s\n",(char *)array[i]);
    // printf("\t%s\n",array[i]);

  return EXIT_SUCCESS;
}

int compare(const void *x, const void *y) {
  return strcmp(*(char **)x, *(char **)y);
}

void mkatom(void **x, void *cl) {
  const char **str;
  FILE *fp;
  str=(const char **)x;
  fp=cl;
  *str=Atom_string(*str);
  fprintf(fp,"\t%s\n",*str);
}
