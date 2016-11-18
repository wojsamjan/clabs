/* Plik: czas.c
 * -------------
 * liczba sekund -> ile to jest
 * 
 *          10^2    2 minuty
 *          10^4    3 godziny 
 *          10^5    1,1 dnia 
 *          10^6    1,5 tygodnia
 *          10^7    4 miesiace
 *          10^8    3 lata
 *          10^9    30 lat
 *          10^10   300 lat
 *          10^11   3000 lat
 *  warto tez wiedziec, ze (2^32 sekund=(2^10)^3.2~(10^3)^3.2~10^9.6~128 lat)
 *           2^32   2^7 lat
 *
 * Wersja z dnia: 17.XII.1999
 */


#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

#define n 500

int main () {
  time_t start, stop;
  int i, j, k; /* liczniki petli */
  int count = 0;
  double elapsed_time;
  double suma;
  i=j=k=n;
  
  time(&start);
  for (i=0; i<n; i++)
    for (j=0; j<n; j++)
      for (k=0; k<n; k++)
	count++;
  time(&stop);
  elapsed_time=difftime(stop,start);
  printf("10^9 obrotow petli trwalo %g sekund\n", elapsed_time);
  printf("Wykonanie instrukcji `count++' trwa %g sekund\n",
	 elapsed_time/(n*n*n));

  time(&start);
  for (i=0; i<n; i++)
    for (j=0; j<n; j++)
      for (k=0; k<n; k++)
	suma+=sin(count++);
  time(&stop);
  elapsed_time=difftime(stop,start);
  printf("10^9 obrotow petli trwalo %g sekund\n", elapsed_time);
  printf("Obliczenie `sin' trwa %g sekund\n",
	 elapsed_time/(n*n*n));

  return EXIT_SUCCESS;
}
