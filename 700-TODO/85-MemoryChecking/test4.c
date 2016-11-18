/*   Plik:  test4.c
     Wersja:  19 XI 2002 */

#include <stdlib.h>
#include "mem.h"

int main() {
  int n=30;
  char buf[20], *p;

  if (n>=sizeof buf)
    p=malloc(n);
  else
    p=buf;

  FREE(p);

  return EXIT_SUCCESS;
}
