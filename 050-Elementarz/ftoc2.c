/* wypisz zestawienie temperatur Fahrenheita-Celsjusza
   dla f = 0,20,...300 */

#include <stdio.h>

int main() {
  int lower, upper, step;
  double fahr, celsius;

  lower = 0;   // dolna granica temperatur
  upper = 300; // górna granica
  step = 20;   // rozmiar kroku

  fahr = lower;
  while (fahr <= upper) {
    celsius = (5.0 / 9.0) * (fahr - 32);
    printf("%3.0f%6.1f\n", fahr, celsius);
    fahr = fahr + step;
  }
}
