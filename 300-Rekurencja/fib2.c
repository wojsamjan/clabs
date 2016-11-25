#include <stdio.h>

long long int AdditiveSequence(long long int n, long long int t0, long long int t1) {
  if (n==0) return t0;
  if (n==1) return t1;
  return AdditiveSequence(n-1, t1, t0+t1);
}

long long int Fibonacci(int n) {
  return AdditiveSequence(n, 1, 1);
}

int main() {
  int i;
  for (i = 1; i <= 91; i++)
    printf("\tfib(%i)=%lli\n", i, Fibonacci(i));
}
