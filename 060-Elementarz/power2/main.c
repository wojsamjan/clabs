#include <stdio.h>
#include <stdlib.h>

/* testowanie funkcji `power' */

#include "power.h"

int main() {
  int i;
  for (i = 0; i < 10; ++i) {
    printf("i=%d\tpower(2,i)=%d\tpower(-3,i)=%d\n", i, power(2, i), power(-3, i));
  }
}
