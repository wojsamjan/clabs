#include <stdio.h>
#include <locale.h>

int main(void) {
  setlocale(LC_NUMERIC, ""); // use the native environment
  // setlocale(LC_NUMERIC, "pl_PL.UTF-8"); // force Polish

  // 20!
  long unsigned int factorial20 = 2432902008176640000;
  // the 100,000 zero of the Riemann zeta function, accurate to within 3*10^(-9)
  //   http://www.dtc.umn.edu/~odlyZko/zeta_tables/index.html
  double y = 74920.827498994;  // zero100000 = 0.5 + y * I

  printf("%'ld\n", factorial20);
  printf("%'.9lf\n", y);
}
