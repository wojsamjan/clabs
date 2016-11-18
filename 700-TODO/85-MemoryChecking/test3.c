/*   Plik:  test3.c
     Wersja:  19 XI 2002 */

#include <stdlib.h>
#include "mem.h"

int main() {
  int n=10;
  char buf[20], *p;

  if (n>=sizeof buf)
    p=ALLOC(n);
  else
    p=buf;

  FREE(p);

  return EXIT_SUCCESS;
}
