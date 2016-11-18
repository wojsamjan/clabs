#include <stdio.h>
#include "genlib.h"
#include "strlib.h"

void ListPermutations(string in);
void RecursivePermute(string out, string in);

int main() {
  char *str = "123";
  printf("Program wypisuje wszystkie permutacje znaków: %s\n",str);
  ListPermutations(str);
  return EXIT_SUCCESS;
}

void ListPermutations(string in) {
  RecursivePermute("",in);
}

void RecursivePermute(string out, string in) {
  int i, len;
  len=StringLength(in);
  if (len==0)
    printf("\t%s\n",out);
  else 
    for (i=0; i<len; i++) {
      string newout, newin;
      newout=Concat(out,CharToString(IthChar(in,i)));
      newin=Concat(SubString(in,0,i-1),SubString(in,i+1,len));
      RecursivePermute(newout,newin);
    }
}
