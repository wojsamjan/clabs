/*  
 *  File: subsets.c
 *
 *  $Revision: 1.1.1.1 $
 *  $Date: 2004/01/24 10:40:48 $
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

char napis[] = "wxyz";
static void ListSubsets(string str);
static void zrobto(string in, string biez, int i);
string podaj_z(string in,int j);
static void wypisz(string co);

int main() {
  ListSubsets(napis); 
  return EXIT_SUCCESS;
}

static void ListSubsets(string str) {
      zrobto(str, "", 0);
}

static void zrobto(string in, string biez, int i){
      int j,dl = StringLength(in);
      string nowy;

      wypisz(biez);  
      
      for (j = i; j < dl; j++) {
            nowy  = Concat(biez, podaj_z(in,j));
            zrobto(in, nowy, j + 1);   
      }
}

string podaj_z(string in,int j){
 return CharToString(IthChar(in,j));
 }
 
static void wypisz(string co){
int i;
printf("{");
for(i=0;i<StringLength(co);i++){
    printf("%c",co[i]);
    }
printf("}\n");
}