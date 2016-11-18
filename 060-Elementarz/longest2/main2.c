#include <stdio.h>
#include <stdlib.h>

/* wypisz najdłuższy wiersz */

#define MAXLINE 1024 /* maksymalny rozmiar wiersza */

#include "getline.h"
#include "copy.h"

int main() {
  int  len; /* długość bieżącego wiersza */
  int max; /* poprzednia maksymalna długość */
  char line[MAXLINE]; /* bieżący wiersz z wejścia */
  char longest[MAXLINE]; /* przechowywany maksymalny wiersz */

  max = 0;
  while ((len = my_getline(line, MAXLINE)) > 0) {
    if (len > max) {
      max = len;
      copy(longest, line);
    }
  }
  if (max > 0) { /* znaleziono wiersz */
    printf("%s",longest);
  }
}
