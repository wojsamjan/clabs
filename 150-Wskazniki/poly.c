#include <stdio.h>
#include <stdlib.h>
#include "genlib.h" /* biblioteka CSLIB */
#include "simpio.h"

void GetCoefficients(double *a, double *b);
void Solve(double a, double b, double *x);
void Display(double x);

int main() {
  double a, b, x;  /* wspolczynniki */
  GetCoefficients(&a, &b);
  Solve(a, b, &x);
  Display(x);
  return EXIT_SUCCESS;
}

void GetCoefficients(double *a, double *b) {
  printf("Ten program oblicza pierwiastek rownania a*x=b\n");
  printf("Podaj a: ");
  *a = GetReal();
  printf("Podaj b: ");
  *b = GetReal();
  if (*a==0) Error("wspolczynnik `a' powinien byc rozny od 0");
}

void Solve(double a, double b, double *x) {
  *x=b/a;
}
void Display(double x) {
  printf("Pierwiastkiem rwnaniajest x=%g\n",x);
}
