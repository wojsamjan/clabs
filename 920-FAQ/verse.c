/* Plik: verse.c
 * -------------
 * *t[], **ch_pp, 
 * tworzenie formatu w trakcie dzialania programu
 * zmienne lokalne petli
 * 
 * Wersja z dnia: 16.X.1999
 */

#include <stdio.h>
#include <string.h>  /* strlen */

#define print_nl printf("\n")

char *wierszyk[] = {
  "W co sie bawic -- w co sie bawic?",
  "gdy komis kazdy sprzeda ci niewidke czapke",
  "i nawet slepa babka grac przestanie w klasy",
  "a klasy dawno juz nie graja w slepa babke",
  NULL
};


int main()
{
  char **ch_pp;
  
  print_nl;
  for (ch_pp=wierszyk; *ch_pp; ch_pp++) printf("%s\n", *ch_pp);
  print_nl;
  for (ch_pp=wierszyk; *ch_pp; ch_pp++) printf("%79s\n", *ch_pp);
  print_nl;
  for (ch_pp=wierszyk; *ch_pp; ch_pp++) {
    char format[10];
    int dlugosc = 40+strlen(*ch_pp)/2;
    sprintf(format, "%%%ds\n", dlugosc);
    printf(format, *ch_pp);
  }
  print_nl;

  return 0;
}
