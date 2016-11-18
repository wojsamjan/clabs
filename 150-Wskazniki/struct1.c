#include <stdio.h>

struct dane_os {
  char nazwisko[64];
  char imie[64];
  unsigned int wiek;
};

int main() {
  struct dane_os ja = { "Nowak", "Adam", 32 };

  printf("Nazwisko: %s\tImie: %s\tWiek: %d\n", ja.nazwisko, ja.imie, ja.wiek);
}
