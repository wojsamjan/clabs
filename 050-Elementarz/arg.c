#include <stdio.h>
#include <stdlib.h>

/* czytanie argumentów z linii poleceń */

int main(int argc, char *argv[]) {
  printf("  Liczba argumentów:  %d\n", argc);
  printf("          Argumenty: ");

  for(int i = 0; i < argc; i++) {
    printf(" [%d => %s]", i, argv[i]);
  }
  printf("\n");
}
