#include <stdio.h>

void function(int a, int b, int c) {
  int *ret;

  ret = &ret + 2;
  (*ret) += 7;
}

int main() {
  int x;

  x = 5;
  function(1,2,3);
  x = 6;
  printf("%d\n",x);

  return 0;
}

/* prześledzić działanie krok po kroku pod debuggerem;
   instrukcja x =6 jest pomijana
   gcc -S sin-03.c  # => sin-03.s (tu już coś widać)
*/
