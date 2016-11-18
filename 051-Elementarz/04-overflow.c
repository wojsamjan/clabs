/*  Przyklad pokazujacy przekroczenie zakresu
    dla zmiennych calkowitych */

#include <stdio.h>
#include <limits.h>

int main(void) {
  unsigned int x = UINT_MAX - 1;
  signed int y = INT_MAX - 1;

  printf("x: unsigned int, zajmuje %lu bajty(ow).\n\n", sizeof(x));

  printf("Poczatkowa wartosc x : %u\n", x);
  x++;
  printf("Dodaj 1. Nowa wartosc x: %u\n", x);
  x++;
  printf("Dodaj 1. Nowa wartosc x: %u\n", x);
  x++;
  printf("Dodaj 1. Nowa wartosc x: %u\n", x);

  printf("\ny: signed int, zajmuje %lu bajty(ow).\n\n", sizeof(y));

  printf("Poczatkowa wartosc y: %i\n", y);
  y++;
  printf("Dodaj 1. Nowa wartosc y: %i\n", y);
  y++;
  printf("Dodaj 1. Nowa wartosc y: %i\n", y);
  y++;
  printf("Dodaj 1. Nowa wartosc y: %i\n", y);
}
