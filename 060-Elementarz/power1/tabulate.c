#include <stdio.h>

int power(int base, int n);
void tabulate(int lower, int upper, int (*f)(int, int), int base);

int main() {
  tabulate(1, 5, power, 2);
  tabulate(1, 5, power, 3);
}

void tabulate(int lower, int upper, int (*f)(int,int), int base) {
  int i;
  printf(" n  result\n");
  printf("----------\n");
  for (i = lower; i <= upper; ++i)
    printf("%2d %7d\n", i, f(base, i));
}

int power(int base, int n) {
  int p;
  for (p = 1; n > 0; --n)
    p = p * base;
  return p;
}
