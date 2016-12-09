/*
    Problem podziału (ang. partition problem) polega na podaniu
    wszystkich podzbiorów danego zbioru liczb, których elementy
    sumują się podanej liczby.
    Na przykład, możemy wybrać dwa podzbiory zbioru {1, 3, 4, 5}
    których suma elementów wynosi 5: {1,4} i {5}.
    Zbiór {1, 3, 4, 5} nie zawiera podzbioru, którego suma
    elementów wynosi 11.

    Napisać funkcję `NumberOfPartitions', która dla podanego
    zbioru i podanej liczby wyliczy ile zawiera on podzbiorów
    których suma elementów równa się podanej liczbie.
    Na przykład, dla podanego zbioru
    NumberOfPartitions(sampleSet,4,5) wynosi 2.

    Deklaracje i definicje są podane poniżej.
 */

#include <stdio.h>
#include <stdlib.h>
#include "strlib.h"

static int NumberOfPartitions(int sampleSet[], int size, int target);

int sampleSet[] = {1, 3, 4, 5};

int main() {
  printf("Liczba podziałów zbioru {<wypisać elementy>} sumujących się do %d to %d\n",
	       4, NumberOfPartitions(sampleSet,4,5));
}

static int NumberOfPartitions(int sampleSet[], int size, int target) {
  return 2;
}
