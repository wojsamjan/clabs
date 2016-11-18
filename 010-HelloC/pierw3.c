#!/bin/ch

/* 
   Ponieważ plik ten ma ustawione prawa wykonania
   i pierwszy wiersz rozpoczynają dwa znaki
   `#!' (w powłoce znak `#' rozpoczyna komentarz),
   to powłoka przekaże wykonanie tego pliku programowi
   wymienionemu po tych znakach, czyli `/bin/ch'.

   Zatem plik `hello.c' można uruchomić z wiersza poleceń.

   W terminologii języka Ch pliki napisane w C 
   nazywamy `poleceniami'. Dlatego 
   plik ten jest poleceniem języka Ch.
*/

#include <stdio.h>
#include <math.h>
#include <complex.h>

int main() {
  double complex a=1, b=-4, c=13, x1, x2;
  x1=(-b-sqrt(b*b-4*a*c))/(2*a);
  x2=(-b+sqrt(b*b-4*a*c))/(2*a);
  printf("x1 = %f\n",x1);
  printf("x2 = %f\n",x2);
  return 0;
}
