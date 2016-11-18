/*  Plik: p1.c
 *  Obliczanie pierwiastków równania pierwszego stopnia
 */

#include <stdio.h>
#include <stdlib.h> /* EXIT_SUCCESS */
#include "genlib.h"
#include "simpio.h"

void GetCoefficients( ? );
void Solve( ? );
void Display( ? );

int main() {
  double _współczynniki_;
  GetCoefficients( ? );
  Solve( ? );
  Display( ? );
  return EXIT_SUCCESS;
}









void Solve(double a, double b, double *px) {
  ?
}

void GetCoefficients(double *pa, double *pb) {
  printf("Ten program oblicza pierwiastek równania a*x=b\n");
  printf("Podaj a: ");
  *pa = GetReal();
  printf("Podaj b: ");
  *pb = GetReal();
  if (*pa==0) Error("wspólczynnik `a' powinien być różny od 0");
}

void Display(double x) {
  printf("Pierwiastkiem równania jest x=%g\n",x);
}
