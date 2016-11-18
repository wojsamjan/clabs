#include <stdio.h>
#include <stdlib.h>

/* przepisz wejście na wyjście; wersja 1 */

/* przeczytaj znak
   while (znak nie jest sygnałem końca pliku)
      wypisz właśnie przeczytany znak
      przeczytaj następny znak
 */

int main() {
  int c;
  c=getchar();
  while (c!=EOF) {
    putchar(c);
    c=getchar();
  }
}
