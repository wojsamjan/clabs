/*  
 *  File: graycode.c
 *
 *  $Revision: 1.1.1.1 $
 *  $Date: 2004/01/24 10:39:03 $
 *
    Liczby z przedzia³u [0..7], mo¿emy ponumerowaæ inaczej
    ni¿ w `binarycode.c'. Na przyk³ad w taki sposób:

      000 -> 0   110 -> 4
      001 -> 1   111 -> 5
      011 -> 2   101 -> 6
      010 -> 3   100 -> 7
 
    Zauwa¿my, ¿e przy takiej numeracji kolejne liczby
    ró¿ni± siê tylko na jednym bicie, np. reprezentacje
    bitowe liczb 3 i 4 ró¿ni± siê pierwszym bitem.
    Taki kodowanie liczb nazywamy kodowaniem Gray'a.
    Napisz funkcjê `GenerateGrayCode(nBits)' wypisuj±c±
    dla podanej liczby `nBits' kody Gray'a dla kolejnych
    liczb naturalnych od 0 do 2^N-1.
    Czy wiesz do czego takie kodowanie mo¿e siê przydaæ?
    UWAGA: jest wiele rozwi±zañ.
 */

#include <stdio.h>
#include <stdlib.h>
#include "strlib.h"

static void GenerateGrayCode(int nBits);


int main() {
  GenerateGrayCode(4); 
  return EXIT_SUCCESS;
}

/* Co pierwsze doklejaæ --- zero czy jedynkê */
typedef enum {
      FIRST_ZERO,
      FIRST_ONE
} ConcatFirst;

/* Je¶li najpierw trzeba dokleiæ:
 *   zero -- do pierwszego ci±gu doklej zero i ka¿ dokleiæ znowu zero,
 *           do drugiego doklej jedynkê i ka¿ dokleiæ jedynkê
 *   jedynkê -- do pierwszego doklej jedynkê i ka¿ dokleiæ zero,
 *              do drugiego doklej zero i ka¿ dokleiæ jedynkê
 */
static void generate_codes(int nBits, string current, ConcatFirst what)
{
      if (nBits == 0)
            printf("%s\n", current);
      else if (what == FIRST_ZERO) {
            generate_codes(nBits - 1, Concat(current, "0"), FIRST_ZERO);
            generate_codes(nBits - 1, Concat(current, "1"), FIRST_ONE);
      } else if (what == FIRST_ONE) {
            generate_codes(nBits - 1, Concat(current, "1"), FIRST_ZERO);
            generate_codes(nBits - 1, Concat(current, "0"), FIRST_ONE);
      }
}

/* Zacznij od doklejania zera */
static void GenerateGrayCode(int nBits)
{
      generate_codes(nBits, "", FIRST_ZERO);
}

