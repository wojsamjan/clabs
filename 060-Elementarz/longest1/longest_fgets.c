// przykład z rozdziału 1.9 Tablice znakowe, K&R
// w tej wersji zamiast funkcji getline użyto gets
//
// Program czyta zbiór wierszy i wypisuje najdłuższy.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 1024     /* maksymalny rozmiar wiersza */

int main() {
  int len;               /* długość bieżącego wiersza */
  int max = 0;           /* poprzednia maksymalna długość */
  char line[MAXLINE];    /* bieżący wiersz z wejścia */
  char longest[MAXLINE]; /* przechowywany maksymalny wiersz */

  while (fgets(line, MAXLINE, stdin) != NULL) {
    len = strlen(line);

    if (len > max) {
      max = len;
      strncpy(longest, line, MAXLINE);
    }
  }
  if (max > 0) { /* znaleziono wiersz */
    printf("%s", longest);
  }
}

// Czy program „dobrze działa” jeśli wiersz jest dłuższy niż MAXLINE?
// długość wiersza jest równa dokładnie MAXLINE?
