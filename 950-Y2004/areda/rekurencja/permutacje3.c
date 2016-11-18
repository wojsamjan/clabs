/*  
 *  File: permutacje3.c
 *
 *  $Revision: 1.1.1.1 $
 *  $Date: 2004/01/24 10:38:52 $
 *
   Wersja 3.
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
static void RecursivePermute(string prefix, string suffix);

int main() {
  ListPermutations(napis); 
  return EXIT_SUCCESS;
}

static void ListPermutations(string str) {
  RecursivePermute("",str);
}

static void RecursivePermute(string prefix, string suffix) {
  int i, len;
  string newprefix, newsuffix;
  len=StringLength(suffix);
  if (len==0) 
    printf("%s\n",prefix);
  else {
    for (i=0; i<len; i++) 
      if(FindChar(IthChar(suffix,i),SubString(suffix,0,i-1),0)==-1)
      { 
	newprefix=Concat(prefix,SubString(suffix,i,i));
        newsuffix=Concat(SubString(suffix,0,i-1),SubString(suffix,i+1,len));
        RecursivePermute(newprefix,newsuffix);
      }
  }
}

	
