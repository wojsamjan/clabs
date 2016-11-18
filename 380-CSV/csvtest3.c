
/*  $Date: 2004/11/29 19:08:24 $
    $Revision: 1.1 $

    csvtest2: test biblioteki csv2.c  */

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "csv2.h"

typedef struct czlowiek_struct {
  char *imie;
  char *nazwisko;
  char *ocena;
} *czlowiekT;

czlowiekT ludzie[10];

int main(void)
{
  int i, n = 0;
  const char *line;
  
  while ((line = csv_getline(stdin)) != NULL) {
    ludzie[n] = malloc(sizeof(struct czlowiek_struct));
    /* tylko sprawdzamy */
    for (i = 0; i < csv_nfield(); i++) {
      printf("field[%d] = `%s'\t", i, csv_field(i));
    }
    printf("\n");
    ludzie[n]->imie=strdupa(csv_field(0));
    ludzie[n]->nazwisko=strdupa(csv_field(1));
    ludzie[n]->ocena=strdupa(csv_field(2));
    n++;
  }
  return 0;
}

/* Pod gdb moze Pan obejrzec czy dane z pliku zostaly
   zapamietane w tablicy ludzie:

     print *ludzie[0]
     print *ludzie[1] 

   itd.

Przepraszam za brzydkie slowo w kodzie,

  Pozdrawiam,

--W. Bzyl

 */

