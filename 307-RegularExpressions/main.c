#include <stdio.h>
#include <stdlib.h>

#include "sgrep.h"

/* funkcja main dla funkcji sgrep: szukanie regexp w plikach */

int main(int argc, char *argv[])
{
  int i, nmatch = 0;
  FILE *f;

  if (argc < 2) {
    fprintf(stderr, "sposób użycia: sgrep regexp [plik...]\n");
    exit(1);
  } else if (argc == 2) {
    if (sgrep(argv[1], stdin, NULL))
      nmatch++;
  } else {
    for (i = 2; i < argc; i++) {
      f = fopen(argv[i], "r");
      if (f == NULL) {
        fprintf(stderr, "sgrep: nie można otworzyć pliku %s\n", argv[i]);
        continue;
      }
      if (sgrep(argv[1], f, argc>3 ? argv[i] : NULL))
        nmatch++;
      fclose(f);
    }
  }
  return nmatch == 0;
}
