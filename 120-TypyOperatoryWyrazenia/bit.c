#include <stdio.h>
#include <stdlib.h>

/* bitcount: policz bity 1 w `x' */
int bitcount(unsigned int n) {
  int b;
  for (b=0; n!=0; n>>=1)
    if (n&01)
      b++;
  return b;
}

int main() {
  int m = 9;
  printf("liczba bitów 1 w `%d' = %d\n", m, bitcount(m));
  return EXIT_SUCCESS;
}
