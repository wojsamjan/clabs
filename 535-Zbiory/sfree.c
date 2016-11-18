/*
     $URL: http://manta.univ.gda.pl/svn/wb/labs/c/535-Zbiory/test_set.c $
     $Revision: 196 $
 */

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#include <cii/set.h>

int main(int argc, char *argv[]) {

  Set_T A, B;

  A = Set_new(0, NULL, NULL);

  Set_free(&A);
  /*
  B = NULL;
  Set_free(&B);
  */

  Set_free(NULL);


  return EXIT_SUCCESS;
}
