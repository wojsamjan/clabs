/*
    Liczby z przedziału [0..7], możemy ponumerować inaczej
    niż w `binarycode.c'. Na przykład w taki sposób:

      000 -> 0   110 -> 4
      001 -> 1   111 -> 5
      011 -> 2   101 -> 6
      010 -> 3   100 -> 7

    Zauważmy, że przy takiej numeracji kolejne liczby
    różnią się tylko na jednym bicie, np. reprezentacje
    bitowe liczb 3 i 4 różnią się pierwszym bitem.
    Taki kodowanie liczb nazywamy kodowaniem Gray'a.
    Napisz funkcję `GenerateGrayCode(nBits)' wypisującą
    dla podanej liczby `nBits' kody Gray'a dla kolejnych
    liczb naturalnych od 0 do 2^N-1.
    Czy wiesz do czego takie kodowanie może się przydać?
    UWAGA: jest wiele rozwiązań.
 */

#include <stdio.h>
#include <stdlib.h>
#include "strlib.h"

static void GenerateGrayCode(int nBits);

int main() {
  GenerateGrayCode(3);
}

static void GenerateGrayCode(int nBits) {
  printf("???\n");
}
