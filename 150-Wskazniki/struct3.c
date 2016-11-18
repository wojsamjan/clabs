#include <stdio.h>
#include <stdlib.h>  /* funkcja malloc */
#include <string.h>

typedef struct dane_os {
  char nazwisko[64];
  char imie[64];
  unsigned int wiek ;
} *daneOsT;

int main()
{
  daneOsT ja = malloc(sizeof(struct dane_os));

  printf("Zarezerwowano `%ld' bajty na strukturę dane_os.\n", sizeof(struct dane_os));

  // nie działa!
  // ja->nazwisko = "Nowak";
  strcpy(ja->nazwisko, "Nowak");
  strcpy(ja->imie, "Adam");
  ja->wiek = 32;

  printf("Nazwisko: %s\tImie: %s\tWiek: %d\n", ja->nazwisko, ja->imie, ja->wiek);
}
