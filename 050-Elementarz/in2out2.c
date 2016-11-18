#include <stdio.h>
#include <stdlib.h>

/* przepisz wejście na wyjście; wersja 2 */

int main() {
  int c;
  while ((c = getchar()) != EOF) {
    putchar(c);
  }
}
