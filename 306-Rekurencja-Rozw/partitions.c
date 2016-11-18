/*  
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
#include "strlib.h"

static int NumberOfPartitions(int sampleSet[], int size, int target);

int sampleSet[] = {1, 3, 4, 5};

int main() {
  printf("Liczba podzia³ów zbioru {<wypisaæ elementy>} sumuj±cych siê do %d to %d\n",
	 4, NumberOfPartitions(sampleSet,4,5));
  return EXIT_SUCCESS;
}

static int NumberOfPartitions(int sampleSet[], int size, int target) {
  return 2;
}
