/*
 * Locales, I/O
 * Zamiana wielkich liter na ma³e.
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>  /* tolower */
#include <locale.h>

int main () {
  int c;
  char *locale_name = setlocale(LC_ALL, "");
  
  printf("Nazwa kraju: %s\n\n", locale_name);
  while ((c=getchar())!=EOF) putchar(tolower(c));

  return EXIT_SUCCESS;
}
