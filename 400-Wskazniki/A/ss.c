/*  
 *  Uzupe³niæ brakuj±cy kod. 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define maxlines 20
#define maxlen 80

char text[maxlines][maxlen]; /* marnujemy pamiêæ */

int lines_cmp(const void *a, const void *b) {
  /* u¿yæ funkcji strcoll; man strcoll */
  ?
}

int main() {
  int i=0, total;
  setlocale(LC_ALL,""); /* uaktywnia strcoll */
  printf("Przed sortowaniem:\n");
  while (fgets(text[i++], maxlen, stdin)!=NULL) {
    if (i>=maxlines) {
      fprintf(stderr,"! Za du¿o linii do sortowania.\n");
      break;
    }
    printf("%d:\t%s", i-1, text[i-1]);
  }
  total=i-1;

  qsort( ? );

  printf("Po sortowaniu:\n");
  for (i=0; i<total; i++)
    printf("%d:\t%s", i, text[i]);
  return 0;
}
