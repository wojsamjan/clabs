
#include <stdio.h>
#include <math.h>

/* równanie kwadratowe NIE ma pierwiastków */

double delta(double a, double b, double c);

int main() {
  double a=1, b=-4, c=13, x1, x2;
  double d;
  d=b*b-4*a*c;
  x1=(-b-sqrt(delta(a,b,c)))/(2*a);
  x2=(-b+sqrt(delta(a,b,c)))/(2*a);
  printf("x1 = %f\n",x1);
  printf("x2 = %f\n",x2);
  return 0;

}
