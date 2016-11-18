#include <stdio.h>
#include <stdlib.h>

double *table(void) {
  double math_constants[] = { 3.14, 2.71 };
  return math_constants;
}

double *table2(void) {
  double *math_constants;
  math_constants = malloc(2*sizeof(double));
  math_constants[0] = 3.14;
  math_constants[1] = 2.71;
  return math_constants;
}

int main()
{
  double *stale;

  stale = table();
  printf("pi = %f\n", stale[0]);

  stale = table2();
  printf("pi = %f\n", stale[0]);

  return 0;
}
