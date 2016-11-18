
// jeśli a * x = b, to x = a^-1 * b

#include <array.h>

int main() {
  array double a[4][4] = 
    { 1, 1, 0, 0,
      1, 1, 1, 0,
      0, 1, 1, 1,
      0, 0, 1, 1 };
  array double b[4] = { 2, 3, 3, 2 };
  array double x[4];

  x = inverse(a) * b;
  
  printf("det(a) = %.0f\n", determinant(a));
  printf("a =\n%.1f", a);
  printf("b =\n%.1f", b);
  printf("x = a^-1 * b = %.1f", x);

  return 0;
}
