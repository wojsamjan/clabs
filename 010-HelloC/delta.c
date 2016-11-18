
#include <math.h>
#include "delta.h"

double delta(double a, double b, double c) {
  double result;
  result=sqrt(b*b-4*a*c);
  return result;
}
