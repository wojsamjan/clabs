/* Wypisz zestawienie temperatur Fahrenheita-Celsjusza
  dla f = 0, 20, ..., 300.

  Konkretnie, chodzi o taką tabelkę:
    0	-17
    20	-6
    40	4
    60	15
    80	26
    100	37
    120	48
*/

#include <stdio.h>

int main() {
  int fahr, celsius;

  int lower = 0;   // dolna granica temperatur
  int upper = 300; // górna granica
  int step = 20;   // rozmiar kroku

  fahr = lower;
  while (fahr <= upper) {
    celsius = 5 * (fahr - 32) / 9;
    printf("%i\t%i\n", fahr, celsius);
    fahr = fahr + step;
  }
}
