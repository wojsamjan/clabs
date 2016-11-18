
/* Obliczamy liczbę PI -- niespodzianki arytmetyki całkowitej. */

#include <stdio.h>

double metoda_iv(int liczba_iteracji)
{
  int licznik;
  double wynik = 4, znak = -1;

  liczba_iteracji += 3;
  for (licznik = 3; licznik <= liczba_iteracji; licznik = licznik + 2) {
    wynik = wynik + ((4 / licznik) * znak);
    znak = znak * (-1);
  }
  return wynik;
}

int main()
{
  int n;

  printf("Podaj liczbę iteracji: ");
  scanf("%d", &n);
  printf("Obliczona wartość: %f\n",metoda_iv(n));
  return 0;
}
