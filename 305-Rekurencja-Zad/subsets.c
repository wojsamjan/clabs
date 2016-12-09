/*
    Napisz funkcję `ListSubsets' generującą wszystkie
    możliwe podzbiory podanego zbioru, gdzie zbiór
    składa się z liter podanych w postaci napisu.
    Na przykład po wywołaniu `ListSubsets("ABC")'
    na terminalu powinniśmy otrzymać (być może
    w innej kolejności):

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
}

static void ListSubsets(string str) {
  printf("???\n");
}
