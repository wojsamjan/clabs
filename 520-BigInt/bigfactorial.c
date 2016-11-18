/* 
    $URL: http://manta.univ.gda.pl/svn/wb/labs/c/520-BigInt/bigfactorial.c $
    $Revision: 195 $
*/

#include <stdio.h>
#include <stdlib.h>

#include "bigint.h"

static BigInt_T BigFactorial(int n);

int main() {
  int lower_limit = 20;
  int upper_limit = 44; 

  int i;

  printf("\n   n  |  n!\n");
  printf("-------------------------------------------------------------------\n");
  for (i=lower_limit; i<=upper_limit; i++) {
    printf("%5d |%60s\n", i, BigIntToString(BigFactorial(i)));
  }
  printf("\n");

  return EXIT_SUCCESS;
}

static BigInt_T BigFactorial(int n) {
  if (n == 0)
    return NewBigInt(1);
  else
    return MultiplyBigInt(NewBigInt(n), BigFactorial(n-1));
}
