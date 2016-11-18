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
static void RecursiveSubsets(string prefix, string suffix);

int main() {
  ListSubsets(napis); 
  return EXIT_SUCCESS;
}

static void ListSubsets(string str) {
  RecursiveSubsets("",str);
}
static void RecursiveSubsets(string prefix, string suffix) {
  string newprefix;
  int len=StringLength(suffix);
  if (len==0) 
    printf("{%s}\n",prefix);
  else {
      newprefix=Concat(prefix,SubString(suffix,0,0));
      RecursiveSubsets(newprefix,SubString(suffix,1,len));
      RecursiveSubsets(prefix,SubString(suffix,1,len));
  }
}
