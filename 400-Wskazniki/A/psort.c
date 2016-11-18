
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define maxlines 20
#define maxlen 80

char *text[maxlines];
char buffer[maxlen];

int lines_cmp(const void *a, const void *b) {
  return strcoll(*(char **)a, *(char **)b);
}

int main() {
  int i=0, total;
  setlocale(LC_ALL,""); /* uaktywnia strcoll */
  printf("Przed sortowaniem:\n");
  while (fgets(buffer, maxlen, stdin)!=NULL) {
    if (i>=maxlines) {
      fprintf(stderr,"! Za dużo linii do sortowania.\n");
      break;
    }
    text[i]=malloc(maxlen);
    strcpy(text[i],buffer);
    printf("%d:\t%s", i, text[i]);
    i++;
  }
  total=i;
  qsort(text, total, sizeof(char *), lines_cmp);
  printf("Po sortowaniu (liczba wierszy=%d):\n", total);
  for (i=0; i<total; i++)
    printf("%d:\t%s", i, text[i]);
  return 0;
}

/* 1. Poprawić program, tak aby cała pamięć alokowana dynamicznie była
      wykorzystana.
   2. Usunąć ograniczenia na długość i liczbę sortowanych linii.
   3. Sprawdzić czy pamięć została przydzielona przez `malloc'.
*/
