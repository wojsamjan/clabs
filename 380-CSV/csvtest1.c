
/*  $Date: 2004/03/16 20:21:02 $
    $Revision: 1.1 $

    csvtest1: test biblioteki cvs1.c  */

#include <stdio.h>
#include "csv1.h"

int main(void)
{
  int i, nf;

  while ((nf = csv_getline(stdin)) != -1)
    for (i = 0; i < nf; i++)
      printf("field[%d] = `%s'\n", i, csv_field[i]);
  return 0;
}
