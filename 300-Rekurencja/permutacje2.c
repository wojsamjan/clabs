/* Plik: .c
 * -------------
 * rekurencja, opakowanie
 * program ten wypisuje wszystkie permutacje
 * liter napisu podanego jako tablica
 */

#include <stdio.h>
#include <stdlib.h> /* EXIT_SUCCESS */
#include <string.h> /* strlen */

char napis[] = "ABC"; /* napis ktorego litery bedziemy przestawiac */

static void ListPermutations(char *s);
static void RecursivePermute(char *s, int k);
static void ExchangeCharacters(char *s, int p1, int p2);

int main() {
  ListPermutations(napis); 
  return EXIT_SUCCESS;
}

static void ListPermutations(char *s) {
  RecursivePermute(s,0);
}
static void RecursivePermute(char *s, int k) {
  int i;
  if (k==strlen(s)) 
    printf("%s\n",s);
  else
    for (i=k; i<strlen(s); i++) {
      ExchangeCharacters(s,k,i);
      RecursivePermute(s,k+1);
      ExchangeCharacters(s,k,i);
    }
}
static void ExchangeCharacters(char *s, int p1, int p2) {
  char tmp;
  tmp=s[p1];
  s[p1]=s[p2];
  s[p2]=tmp;
}
