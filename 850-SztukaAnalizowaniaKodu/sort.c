#include <stdio.h>

/*  uwaga: kod funkcji zawiera błędy */

/*  sortuj elementy tablicy a za pomocą algorytmu `selection sort' */

void sort(int a[], int n) {
  int current, j, lowestindex, temp;

  for (current = 0; current < n - 1; current++) {
    lowestindex = current;
    for (j = current + 1; j < n; j++) 
      if (a[j] < a[lowestindex])
	lowestindex = j;
  }

  if (lowestindex != current) {
    temp = a[current];
    a[current] = a[lowestindex];
    a[lowestindex] = temp;
  }
}

int main() {
  int a[] = { 1, 5, 8, 10 };
  //  int a[] = { 4, 2, 3, 4 };
  //  int a[] = { 6, 4, 3, 1 };

  printf("\ta[0] = %d\t\ta[1] = %d\t\ta[2] = %d\t\ta[3] = %d\n", 
	 a[0], a[1], a[2], a[3]);

  sort(a, 4);

  printf("\ta[0] = %d\t\ta[1] = %d\t\ta[2] = %d\t\ta[3] = %d\n", 
	 a[0], a[1], a[2], a[3]);

  return 0;
}
