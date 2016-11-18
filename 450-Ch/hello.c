#!/bin/ch
/* 
   Poniewa¿ plik ten ma ustawione prawa wykonania
   i pierwszy wiersz rozpoczynaj± dwa znaki
   `#!' (w pow³oce znak `#' rozpoczyna komentarz),
   to pow³oka przeka¿e wykonanie tego pliku programowi
   wymienionemu po tych znakach, czyli `/bin/ch'.

   Zatem plik `hello.c' mo¿na uruchomiæ z wiersza poleceñ.

   W terminologii jêzyka Ch pliki napisane w C 
   nazywamy `poleceniami'. Dlatego 
   plik ten jest poleceniem jêzyka Ch.
*/

#include <stdio.h>

int main() {
  printf("Witaj ¶wiecie!\n");
}
