/* Plik: longest.c
 * ---------------
 * Przykład z rozdziału 1.9 Tablice znakowe, K&R
 *
 * Program czyta zbiór wierszy i wypisuje najdłuższy.
 * Zadanie 1: Zamienić funkcję copy na strcpy
 *   (wykonaj man strcpy aby dowiedzieć jak działa strcpy).
 * Zadanie 2: Zamienić getline na funkcję getline z biblioteki
 *   glibc (wykonaj man getline aby dowiedzieć się jak działa getline).
 * Rozwiązania: ../longest2
 */

#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 1024 /* maksymalny rozmiar wiersza */

/* getline: wczytaj wiersz do s, podaj jego długość */
int my_getline(char s[], int lim);
/* copy: przepisz from do to
         to musi być dostatecznie duże */
void copy(char to[], char from[]);

int main() {
  int  len; /* długość bieżącego wiersza */
  int max; /* poprzednia maksymalna długość */
  char line[MAXLINE]; /* bieżący wiersz z wejścia */
  char longest[MAXLINE]; /* przechowywany maksymalny wiersz */

  max=0;
  while ((len = my_getline(line,MAXLINE))>0) {
    if (len>max) {
      max=len;
      copy(longest,line);
    }
  }
  if (max>0) { /* znaleziono wiersz */
    printf("%s",longest);
  }

  return EXIT_SUCCESS;
}

int my_getline(char s[], int lim) {
  int c, i;
  for (i=0; i<lim-1 && (c=getchar())!=EOF && c!='\n'; ++i) {
    s[i]=c;
  }
  if (c=='\n') {
    s[i]=c;
    ++i;
  }
  s[i]='\0';
  return i;
}

void copy(char to[], char from[]) {
  int i;
  i=0;
  while ((to[i]=from[i])!='\0')
    ++i;
}
