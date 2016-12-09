/* Tym razem chcemy otrzymać coś takiego:
ListPermutations("AABB") =>
    AABB
    ABAB
    ABBA
    BAAB
    BABA
    BBAA
Teraz podany napis może zawierać powtarzające
się litery. Funkcja rekurencyjna nie powinna
generować dodatkowych permutacji */

#include <stdio.h>
#include <stdlib.h>
#include "strlib.h"

char napis[] = "AABB";

static void ListPermutations(string str);

int main() {
  ListPermutations(napis);
}

static void ListPermutations(string str) {
  printf("???\n");
}
