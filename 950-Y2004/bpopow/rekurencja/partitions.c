/*  
 *  File: graycode.c
 *
 *  $Revision: 1.1.1.1 $
 *  $Date: 2004/01/24 10:40:34 $
 *
    Problem podzia³u (ang. partition problem) polega na podaniu
    wszystkich podzbiorów danego zbioru liczb, których elementy 
    sumuj± siê podanej liczby. 
    Na przyk³ad, mo¿emy wybraæ dwa podzbiory zbioru {1, 3, 4, 5}
    których suma elementów wynosi 5: {1,4} i {5}.
    Zbiór {1, 3, 4, 5} nie zawiera podzbioru, którego suma 
    elementów wynosi 11.

    Napisaæ funkcjê `NumberOfPartitions', która dla podanego
    zbioru i podanej liczby wyliczy ile zawiera on podzbiorów
    których suma elementów równa siê podanej liczbie.
    Na przyk³ad, dla podanego zbioru 
    NumberOfPartitions(sampleSet,4,5) wynosi 2.
    
    Deklaracje i definicje s± podane poni¿ej.
 */

#include <stdio.h>
#include <stdlib.h>

int sampleSet[] = {0, 1, 3, 4, 5};
int wynik;
int *p;

int NumberOfPartitions(int sampleSet[], int size, int target) {
  int i;
  
  for (i = size; i>=1; i--){
    if(sampleSet[i] == target)
      (*p)++;
    else if(sampleSet[i]<target)
      NumberOfPartitions(sampleSet, i-1, target-sampleSet[i]);
  }
  return *p;
}

int main() {
  int liczba;
  wynik = 0;
  p = &wynik;

  liczba = 4;

  printf("\nLiczba podzia³ów zbioru {1,3,4,5} ");
  printf("sumuj±cych siê do %d to %d.\n\n", liczba, NumberOfPartitions(sampleSet,4,liczba));
  return EXIT_SUCCESS;
}

