#include <stdio.h>
#include <stdlib.h>  /* funkcja malloc */

typedef struct dane_os {
  char *nazwisko;
  char *imie;
  unsigned int wiek ;
} *daneOsT;

int main() {
  daneOsT ja = malloc(sizeof(struct dane_os));
  printf("Zarezerwowano `%ld' bajtów na strukturę dane_os.\n", sizeof(struct dane_os));

  ja->nazwisko = "Nowak";
  ja->imie = "Adam";
  ja->wiek = 32;

  printf("Nazwisko: %s\tImie: %s\tWiek: %d\n", ja->nazwisko, ja->imie, ja->wiek);
}

/* Wersja z tablicami: zob. struct3.c */
