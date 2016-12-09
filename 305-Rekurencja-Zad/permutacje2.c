/*
    Napisz funkcję rekurencyjną `ListPermutations'
    wypisującą wszystkie permutacje liter podanego napisu.
    Funkcja nie powinna korzystać z notacji tablicowej
    do wybierania lub zamiany znaków wewnątrz napisu.
 */

#include <stdio.h>
#include <stdlib.h>
#include "strlib.h"

char napis[] = "123";

static void ListPermutations(string str);
static void RecursivePermute(string prefix, string suffix);

int main() {
  ListPermutations(napis);
}

static void ListPermutations(string str) {
  RecursivePermute("", str);
}

static void RecursivePermute(string prefix, string suffix) {
  int i, suffix_len;
  string newprefix, newsuffix;

  suffix_len = StringLength(suffix);

  if (suffix_len == 0)
    printf("%s\n", prefix);
  else {
    for (i = 0; i < suffix_len; i++) {
      newprefix = Concat(prefix, SubString(suffix, i, i));
      newsuffix = Concat(SubString(suffix, 0, i - 1), SubString(suffix, i + 1, suffix_len));
      RecursivePermute(newprefix, newsuffix);
    }
  }
}
