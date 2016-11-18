/*  
   Tym razem chcemy otrzymaæ co¶ takiego:
      ListPermutations("AABB") => AABB
                                  ABAB
                                  ABBA
                                  BAAB
                                  BABA
                                  BBAA
   Teraz podany napis mo¿e zawieraæ powtarzaj±ce
   siê litery. Funkcja rekurencyjna nie powinna
   generowaæ dodatkowych permutacji
 */

#include <stdio.h>
#include <stdlib.h>
#include "strlib.h"

char napis[] = "AABB";

static void ListPermutations(string str);

int main() {
  ListPermutations(napis); 
  return EXIT_SUCCESS;
}

static void ListPermutations(string str) {
  printf("???\n");
}
