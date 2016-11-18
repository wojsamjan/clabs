/* Plik: colors.c
 * -------------
 * enum, tablice
 * inicjalizacja
 *
 * Wersja z dnia: 16.X.1999
 */

#include <stdio.h>

enum spektrum { 
  red, orange, yellow, green, 
  blue, indigo, violet 
} kolor;

char *tecza[] = {
  "czerwony", "pomaranczowy", "zolty", "zielony", 
  "niebieski", "indygo", "fioletowy" 
};

/* 
   enum budowa_ciala {
   chudeusz=65, szczuply=70, ok=80, gruby=95, tluscioch=135 
   } typ_budowy;
*/

int main()
{
  for (kolor=red; kolor<=violet; kolor++) printf("%s ", tecza[kolor]);
  printf("\n");

  return 0;
}
