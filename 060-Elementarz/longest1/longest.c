/*
 * Przykład z rozdziału 1.9 Tablice znakowe, K&R
 *
 * Program czyta zbiór wierszy i wypisuje najdłuższy.
 * Program używa funkcji strncpy z string.h
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 1024 // maksymalny rozmiar wiersza

// getline: wczytaj wiersz do s, podaj jego długość
int my_getline(char s[], int lim);

int main() {
  int len;                   // długość bieżącego wiersza
  int max;                   // poprzednia maksymalna długość */
  char line[MAXLINE + 1];    // bieżący wiersz z wejścia
  char longest[MAXLINE + 1]; // przechowywany maksymalny wiersz
  max = 0;
  while ((len = my_getline(line, MAXLINE)) > 0) {
    if (len > max) {
      max = len;
      strncpy(longest, line, MAXLINE);
    }
  }
  if (max > 0) { // znaleziono wiersz
    printf("%s", longest);
  }
}

int my_getline(char s[], int lim) {
  int c, i;
  for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i) {
    s[i] = c;
  }
  if (c == '\n') {
    s[i] = c;
    ++i;
  }
  s[i] = '\0';
  return i;
}
