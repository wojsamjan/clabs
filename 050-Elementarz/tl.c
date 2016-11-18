#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <locale.h>

/*  zamień duże litery na małe  */

int main () {
  int c;
  char *locale_name = setlocale(LC_ALL, "");
  
  printf("Internal country name: [%s]\n\n", locale_name);
  while ((c=getchar())!=EOF) 
    putchar(tolower(c));

  return EXIT_SUCCESS;
}
