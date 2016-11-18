
#include <stdio.h>
#include <math.h>
#include <complex.h>

int main()
{
  complex double a=1.0+0*I, b=-4.0+0*I, c=13.0+0*I, x1, x2;
  //  complex double a=1.0, b=-4.0, c=13.0, x1, x2;
  x1=(-b-csqrt(b*b-4*a*c))/(2*a);
  x2=(-b+csqrt(b*b-4*a*c))/(2*a);
  printf("Pierwiastki równania: %.1f*x^2 + %.1f*x + %.1f = 0\n", 
    creal(a),creal(b),creal(c));
  printf("x1 = %f+i*%f\n",creal(x1),cimag(x1));
  printf("x2 = %f+i*%f\n",creal(x2),cimag(x2));
  return 0;
}
