/*
 *  Program czyta zbiór wierszy i wypisuje najdłuższy.
 *  Program używa funkcji strncpy i getline (rozszerzenie GNU) z glibc
*/

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 1024  /* maksymalny rozmiar wiersza */

int main() {
  int len;                   // długość bieżącego wiersza
  int max = 0;               // poprzednia maksymalna długość
  char longest[MAXLINE + 1]; // przechowywany maksymalny wiersz
  char *line = 0;            // getline umieści adres bufora z wczytanym wierszem w line
  size_t maxline = 0;        // w tym programie nie używane

  while ((len = getline(&line, &maxline, stdin)) != -1) {
    if (len > max) {
      max = len;
      strncpy(longest, line, MAXLINE);
    }
  }
  if (max > 0) { // znaleziono wiersz
    printf("%s", longest);
  }
}
