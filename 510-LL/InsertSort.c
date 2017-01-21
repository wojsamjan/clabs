/*
  Zadanie 7:
    Napisa� funkcj� InsertSort, kt�ra przestawiaj�c w�z�y
    podanej listy uporz�dkuje je rosn�co. Funkcja ta powinna
    korzysta� z funkcji SortedIndex z zadania 6. */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "utils.h"

/* funkcja skopiowana z SortedIndex.c */
void SortedInsert(struct node** headRef, struct node* newNode);

void InsertSort(struct node** headRef) {
  // tw�j kod
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
}
