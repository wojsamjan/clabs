/*  
    W komputerze, liczby całkowite są reprezentowane w postaci
    ciągu bitów, z których każdy może przyjmować wartość
    0 lub 1. Za pomocą ciągu bitów długości N można przedstawić 
    2^N różnych liczb całkowitych.
    Na przykład trzy bity wystarczają do zapisania ośmiu (2^3)
    liczb całkowitych:

      000 -> 0   100 -> 4
      001 -> 1   101 -> 5
      010 -> 2   110 -> 6
      011 -> 3   111 -> 7

   Napisać funkcję rekurencyjną `GenerateBinaryCode(nBits)'
   wypisującą wszystkie ciągi bitów długości `nBits'.
 */

#include <stdio.h>
#include <stdlib.h>
#include "strlib.h"

static void GenerateBinaryCode(int nBits);
static void RecursiveBinaryCode(int nBits, string bCode);

int main() {
  GenerateBinaryCode(3); 
  return EXIT_SUCCESS;
}

static void GenerateBinaryCode(int nBits) {
  RecursiveBinaryCode(nBits,"");
}
static void RecursiveBinaryCode(int nBits, string bCode) {
  if (nBits==0) {
    printf("%s\n",bCode);
  } else {
    RecursiveBinaryCode(nBits-1,Concat(bCode,"0"));
    RecursiveBinaryCode(nBits-1,Concat(bCode,"1"));
  }
}
