/*  
    Napisz funkcjê `ListSubsets' generuj±c± wszystkie
    mo¿liwe podzbiory podanego zbioru, gdzie zbiór
    sk³ada siê z liter podanych w postaci napisu.
    Na przyk³ad po wywo³aniu `ListSubsets("ABC")'
    na terminalu powinni¶my otrzymaæ (byæ mo¿e 
    w innej kolejno¶ci):

       {ABC}   {BC}  
       {AB}    {B}
       {AC}    {C}
       {A}     {}
 */

#include <stdio.h>
#include <stdlib.h>
#include "strlib.h"

char napis[] = "ABC";

static void ListSubsets(string str);

int main() {
  ListSubsets(napis); 
  return EXIT_SUCCESS;
}

static void ListSubsets(string str) {
  printf("???\n");
}
