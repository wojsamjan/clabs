#include <stdio.h>

#ifndef SECOND
int power(int m, int n) {
  int i,p;
  p = 1;
  for (i = 1; i <= n; ++i) {
    p = p * m;
  }
  return p;
}
#else
int power(int base, int n) {
  int p;
  for (p = 1; n > 0; --n)
    p = p * base;
  return p;
}
#endif

int main() {
  int i;

  for (i = 0; i < 10; ++i) {
    printf("\tpower(2,%d)=%d\tpower(-3,%d)=%d\n", i, power(2,i), i, power(-3,i));
  }
}
