/* Plik: ship.c
 * ------------
 * Struktury
 *
 * Wersja z dnia: 16.X.1999
 */

#include <stdio.h>
#include <string.h>  /* strcpy */

struct statek 
{
  char nazwa[30];
  unsigned int liczba_pasazerow;
  unsigned int liczba_zalogi;
};

char *format = "
      nazwa statku: %s
  liczba pasazerow: %d
     liczba zalogi: %d\n\n";

int main()
{
  
  struct statek krazownik;

  strcpy(krazownik.nazwa,"Stefan Batory");
  krazownik.liczba_pasazerow=1001;
  krazownik.liczba_zalogi=512;
  
  printf(format, krazownik.nazwa, 
	 krazownik.liczba_pasazerow, krazownik.liczba_zalogi);
  
  return 0;
}
