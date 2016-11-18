/*  
 *  File: subsets.c
 *
 *  $Revision: 1.1.1.1 $
 *  $Date: 2004/01/24 10:39:04 $
 *
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

char napis[] = "ABCDE";

static void ListSubsets(string str);
static void gen_subsets(string set, string current, int k);

int main() {
  ListSubsets(napis); 
  return EXIT_SUCCESS;
}

static void ListSubsets(string str) {
      gen_subsets(napis, "", 0);
}

static void gen_subsets(string set, string current, int k)
{
      int setlen = StringLength(set);
      int i;
      string newcur;

      printf("{%s}\n", current);
      for (i = k; i < setlen; ++i) {
            newcur = Concat(current, CharToString(IthChar(set, i)));
            gen_subsets(set, newcur, i + 1);
      }
}
