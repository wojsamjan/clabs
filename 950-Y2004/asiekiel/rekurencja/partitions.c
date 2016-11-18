/*  
 *  File: graycode.c
 *
 *  $Revision: 1.1.1.1 $
 *  $Date: 2004/01/24 10:39:04 $
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
#include "strlib.h"

static int NumberOfPartitions(int sampleSet[], int size, int target);

/* Wypisz tablicê intów */
static void print_int_tab(int tab[], int size);

int sampleSet[] = { 1, 2, 4, 5 };

int main() {
  int set_size = sizeof(sampleSet) / sizeof(sampleSet[0]);

  printf("Liczba podzia³ów zbioru { ");
  print_int_tab(sampleSet, set_size);
  printf("} sumuj±cych siê do %d to %d\n", 5, NumberOfPartitions(sampleSet, set_size, 5));
  return EXIT_SUCCESS;
}

static void print_int_tab(int tab[], int size)
{
      int i;

      for (i = 0; i < size; ++i)
            printf("%d ", tab[i]);
}

/* Zsumuj liczby w tablicy */
int sum_tab(int tab[], int size)
{
      int acc = 0;
      int i;

      for (i = 0; i < size; ++i)
            acc += tab[i];
      return acc;
}

/* Argumenty:
 *  set, set_size -- tablica reprezentuj±ca zbiór i jej d³ugo¶æ
 *  current_subset, current_length -- tablica reprezentuj±ca ostatnio wygenerowany podzbiór i jej wielko¶æ
 *  target -- zliczamy zbiory, których suma elementów jest równa tej warto¶ci
 *  k -- generuj podziobory o elementach z { set[i]: i >= k }
 *  matched -- wska¼nik na licznik zbiorów spe³niaj±cych warunek opisany przy 'target'
 */
static void subsets_matching(int set[], int set_size,
                            int current_subset[], int current_length,
                            int target, int k, int* matched)
{
      int i;

      if (sum_tab(current_subset, current_length) == target)
            ++*matched;
      for (i = k; i < set_size; ++i) {
            current_subset[current_length] = set[i];
            subsets_matching(set, set_size, current_subset, current_length + 1,
                             target, i + 1, matched);
      }
}

static int NumberOfPartitions(int sampleSet[], int size, int target) {
      int ret = 0;
      int* subset_mem = malloc(size * sizeof(int));

      if (subset_mem == NULL) {
            perror("malloc");
            exit(1);
      }
      subsets_matching(sampleSet, size, subset_mem, 0, target, 0, &ret);
      free(subset_mem);
      return ret;
}
