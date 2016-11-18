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
static void RecursivePermute(string prefix, string suffix);

int main() {
  ListPermutations(napis); 
  return EXIT_SUCCESS;
}

static void ListPermutations(string str) {
  RecursivePermute("",str);
}

static void RecursivePermute(string prefix, string suffix) {
  int i, plen, slen;
  string newprefix, newsuffix, used="";
  plen=StringLength(prefix);
  slen=StringLength(suffix);
  if (slen==0) 
    printf("%s\n",prefix);
  else {
    for (i=0; i<slen; i++) {
      if (FindString(SubString(suffix,i,i),used,0)==-1) {
	used=Concat(used,SubString(suffix,i,i));
	newprefix=Concat(prefix,SubString(suffix,i,i));
	newsuffix=Concat(SubString(suffix,0,i-1),SubString(suffix,i+1,slen));
	RecursivePermute(newprefix,newsuffix);
      }
    }
  }
}
