/*   Plik:  test1.c
     Wersja:  19 XI 2002 */

#include <stdlib.h>

int main() {
  int n=10;
  char buf[20], *p;

  if (n>=sizeof buf)
    p=malloc(n);
  else
    p=buf;

  free(p);

  return EXIT_SUCCESS;
}
