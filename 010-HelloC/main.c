#include <stdio.h>
#include "delta.h"

int main() {
  double a=1, b=-5, c=6, d, x1, x2;
  d=delta(a,b,c);
  x1=(-b-d)/(2*a);
  x2=(-b+d)/(2*a);
  printf("Delta równania: %.1f*x^2 + %.1f*x + %.1f wynosi %.1f\n",
     a,b,c,d);
  printf("Pierwiastki tego równania to:\n");
  printf("x1 = %f\n",x1);
  printf("x2 = %f\n",x2);
  return 0;
}
