
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define maxlines 20
#define maxlen 80

char *text[maxlines];
char buffer[maxlen];

int lines_cmp(const void *a, const void *b) {
  /* u¿yæ funkcji strcoll */
  ?
}

int main() {
  int i=0, total;
  setlocale(LC_ALL,""); /* uaktywnia strcoll */
  printf("Przed sortowaniem:\n");
  while (fgets(buffer, maxlen, stdin)!=NULL) {
    if (i>=maxlines) {
      fprintf(stderr,"! Za du¿o linii do sortowania.\n");
      break;
    }
    text[i]=malloc(maxlen);
    strcpy(text[i],buffer);
    printf("%d:\t%s", i, text[i]);
    i++;
  }
  total=i;

  qsort( ? );

  printf("Po sortowaniu (liczba wierszy=%d):\n", total);
  for (i=0; i<total; i++)
    printf("%d:\t%s", i, text[i]);
  return 0;
}
