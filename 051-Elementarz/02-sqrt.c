/*  oblicz pierwiastek kwadratowy z podanej liczby */

#include <stdio.h>
#include <math.h>   /* uwaga: cc -o 02-sqrt 02-sqrt.c -lm */

int main() {
  float x, s;

  printf("Wpisz liczbe rzeczywista: ");
  scanf("%f", &x);

  s = sqrt(x);

  printf("Pierwiastek kwadratowy z %f rowna sie %f\n", x, s);
}
