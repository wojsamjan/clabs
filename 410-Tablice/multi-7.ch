
// jeśli a * x = b, to x = a^-1 * b

#include <array.h>

int main() {
  array double a[2][2] = { 1, 2, 3, 4 };
  array double b[2] = { 5, 6 };
  array double x[2];

  x = inverse(a) * b;
  
  printf("a =\n%.1f", a);
  printf("b =\n%.1f", b);
  printf("x = inverse(a) * b =\n%.1f", x);

  return 0;
}
