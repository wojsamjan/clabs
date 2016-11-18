/* Plik: p2.c
 * -------------
 * Obliczanie pierwiastków równania pierwszego stopnia
 */

#include <stdio.h>
#include <stdlib.h> /*  EXIT_SUCCESS */
#include "genlib.h"
#include "simpio.h"

struct poly1
{
  double a, b; /* współczynniki */
  double x;    /* pierwiastek */
};

typedef struct poly1 poly1T;

void GetCoefficients( ? );
void Solve( ? );
void Display( ? );

int main() {
  poly1T polynomial = { 0, 0 };
  GetCoefficients( ? );
  Solve( ? );
  Display( ? );
  return EXIT_SUCCESS;
}

void Solve(poly1T *p) {
  ?
}
void Display(poly1T p) {
  printf("Rozwiązaniem równania %g*x=%g jest x=%g\n", ?);
}

void GetCoefficients(poly1T *p) {
  printf("Ten program oblicza pierwiastek równania a*x=b\n");
  printf("Podaj a: ");
  p->a = GetReal();
  printf("Podaj b: ");
  p->b = GetReal();
  if (p->a==0) Error("wspólczynnik `a' powinien być różny od 0");
}
