#include <array.h>  // zawiera definicję `array'

int main() {
  array double a[2][2] = { 1, 2, 3, 4 };
  array double b[2][2] = { 5, 6, 7, 8 };
  array double c[2][2];

  c = a * b;

  printf("a =\n%.1f", a);
  printf("b =\n%.1f", b);
  printf("c =\n%.1f", c);

  return 0;
}
