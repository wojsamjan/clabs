
/*  $Date: 2004/03/16 20:21:02 $
    $Revision: 1.1 $

    csvtest2: test biblioteki csv2.c  */

#include <stdio.h>
#include "csv2.h"

int main(void)
{
  int i;
  const char *line;
  
  while ((line = csv_getline(stdin)) != NULL) {
    /*    printf("line = `%s'\n", line); */
    for (i = 0; i < csv_nfield(); i++)
      printf("field[%d] = `%s'\n", i, csv_field(i));
  }
  return 0;
}
