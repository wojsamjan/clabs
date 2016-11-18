#include <stdio.h>

#include "helpers.h"

void GetCoefficients(int *a, int *b) {
   printf("podaj a: ");
   scanf("%d", a);
   printf("podaj b: ");
   scanf("%d", b);
}

void Solve(int a, int b, int *x) {
  *x = b / a;
}

void DisplayResults(int x) {
  printf("wynik: %d\n", x);
}
