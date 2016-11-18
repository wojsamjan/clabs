/*   Plik: InsertSort.c
   Wersja: 22 X 2002

 Zadanie 7:
   Napisaæ funkcjê InsertSort, która przestawiaj±c wêz³y 
   podanej listy uporz±dkuje je rosn±co. Funkcja ta powinna
   korzystaæ z funkcji SortedIndex z zadania 6. */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "utils.h"

/* funkcja skopiowana z SortedIndex.c */
void SortedInsert(struct node** headRef, struct node* newNode);

void InsertSort(struct node** headRef) {
  // twój kod
}

void BasicCaller() {
  struct node* myList=NULL;
  Push(&myList,1);
  Push(&myList,3);
  Push(&myList,5);
  Push(&myList,7);
  ShowLinkedList(myList); /* myList={7,5,3,1} */
  InsertSort(&myList);
  ShowLinkedList(myList); /* myList={1,3,5,7} */
}

int main() {
  BasicCaller();
  return EXIT_SUCCESS;
}
