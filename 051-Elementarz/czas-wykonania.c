#include <stdio.h>
#include <time.h>
#include <assert.h>

int main() {
  clock_t  startclick, clicks;
  long int i, wynik;

  printf("na moim komputerze CLOCKS_PER_SEC = %d\n", CLOCKS_PER_SEC);

  startclick = clock();

  wynik = 0;
  for (i = 0; i < 100000000; i++) {
    wynik = wynik - i ;
  }
  // assert(wynik == ??);

  clicks = clock() - startclick;
  printf("czas wykonania = %ld\n", clicks);
}
