/* przyklad uzycia #define -- definiowanie stalej */

#include <stdio.h>

#define PI 3.142

/* Dokladniejsza wartosc w math.h */

int main()
{
  double r, c, ac, as, v;

  r = 10.01;
  printf("Promien = %f\n", r);

  c = 2.0 * PI * r;
  printf("Obwod kola = %f\n", c);

  ac = PI * r * r;
  printf("Pole kola = %f\n", ac);

  as = 4.0 * PI * r * r;
  printf("Powierzchnia kuli = %f\n", as);

  v = 4.0/3.0 * PI * r * r * r;
  printf("Objetosc kuli = %f\n", v);

  return 0;
}
