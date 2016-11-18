/*
     Uzupelnic kod
 */

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#include <cii/set.h>

#include "getword.h"

int first(int c) {
  return isdigit(c);
}

int cmpint(const void *x, const void *y) {

}

unsigned hashint(const void *x) {

}

void print_int(const void *member, void *cl) {

}

int main(int argc, char *argv[]) {
  Set_T A;

  printf("Wpisz kilka liczb i wcisnij `ctrl + d': ");

  A = Set_new(0, cmpint, hashint);
  while (getword(stdin, buf, buf_size, first, first)) {
    n = atof(buf);
    ?
    Set_put(A, ?);
  }

  /* wypisz elementy zbioru A */
  Set_map(A, print_int, stdout);

  /* wypisz posortowane elementy zbioru A */
  {
    void **A_array = Set_toArray(A, NULL);

  }

  return EXIT_SUCCESS;
}
