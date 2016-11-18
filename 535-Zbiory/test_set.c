/*
     $URL: http://manta.univ.gda.pl/svn/wb/labs/c/535-Zbiory/test_set.c $
     $Revision: 196 $
 */

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#include <cii/set.h>

#include "getword.h"

#define print_nl printf("\n");

int first(int c) {
  return isdigit(c);
}

int cmpint(const void *x, const void *y) {
  int n = *(int *) x;
  int m = *(int *) y;
  return n < m ? -1 : n == m ? 0 : 1;
}

unsigned hashint(const void *x) {
  return *(int *) x;
}

int cmpintp(const void *x, const void *y) {
  int n = **(int **) x;
  int m = **(int **) y;
  return n < m ? -1 : n == m ? 0 : 1;
}

void print_int(const void *member, void *cl) {
  fprintf((FILE *) cl, "%d ", *(int *) member);
}

int main(int argc, char *argv[]) {
  char buf[1024];
  int buf_size = 1024;  
  int i, card, n, *np;
  Set_T A;

  printf("Wpisz kilka liczb i wciśnij `ctrl + d': ");

  A = Set_new(0, cmpint, hashint);
  while (getword(stdin, buf, buf_size, first, first)) {
    n = atof(buf);
    np = malloc(sizeof(double));
    *np = n;
    Set_put(A, np);
  }

  printf("\n\t A =\t\t");
  Set_map(A, print_int, stdout);
  print_nl;

  printf("\n\t sort(A) =\t");

  {
    void **A_array = Set_toArray(A, NULL);
    card = Set_length(A);
    qsort(A_array, Set_length(A), sizeof(void *), cmpintp);
    for (i = 0; i < card; i++)
      printf("%d ", *(int *)A_array[i]);

    print_nl;
  }

  return EXIT_SUCCESS;
}
