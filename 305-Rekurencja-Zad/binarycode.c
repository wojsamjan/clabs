/*  
   W komputerze, liczby ca³kowite s± reprezentowane w postaci
    ci±gu bitów, z których ka¿dy mo¿e przyjmowaæ warto¶æ
    0 lub 1. Za pomoc± ci±gu bitów d³ugo¶ci N mo¿na przedstawiæ 
    2^N ró¿nych liczb ca³kowitych.
    Na przyk³ad trzy bity wystarczaj± do zapisania o¶miu (2^3)
    liczb ca³kowitych:

      000 -> 0   100 -> 4
      001 -> 1   101 -> 5
      010 -> 2   110 -> 6
      011 -> 3   111 -> 7

   Napisaæ funkcjê rekurencyjn± `GenerateBinaryCode(nBits)'
   wypisuj±c± wszystkie ci±gi bitów d³ugo¶ci `nBits'.
 */

#include <stdio.h>
#include <stdlib.h>
#include "strlib.h"

static void GenerateBinaryCode(int nBits);

int main() {
  GenerateBinaryCode(3); 
  return EXIT_SUCCESS;
}

static void GenerateBinaryCode(int nBits) {
  printf("???\n");
}
