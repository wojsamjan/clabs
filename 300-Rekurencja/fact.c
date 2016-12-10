#include <stdio.h>
#include <locale.h>

long unsigned int Fact(int n) {
  if (n == 0)
    return 1;
  else
    return n * Fact(n - 1);
}

int main() {
  setlocale(LC_NUMERIC, ""); // use the native environment
  // setlocale(LC_ALL, "");

  for (int i = 0; i <= 20; i++)
    printf("%4d %'28ld\n", i, Fact(i));
}
