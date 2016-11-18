/*  oblicz pole kola  */

#include <stdio.h>
#define PI 3.14159

int main() {
  float r, a;

  printf("Podaj promien okregu: ");
  scanf("%f", &r);

  a = PI * r * r;

  printf("Pole okręgu opromieniu %3.2f wynosi %3.2f\n", r, a);
}
