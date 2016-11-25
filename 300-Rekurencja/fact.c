#include <stdio.h>

int Fact(int n) {
  if (n == 0)
    return 1;
  else
    return n * Fact(n-1);
}

int main() {
  int i;
  for (i=0; i < 11; i++)
    printf("\t%8d\n", Fact(i));
}
