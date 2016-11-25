#include <stdio.h>

long long int Fib(int n) {
  if (n <= 2)
    return n;
  else
    return Fib(n-1) + Fib(n-2);
}

int main() {
  int i;
  for (i = 1; i <= 50; i++)
    printf("\tfib(%i) = %lli\n", i, Fib(i));
}
