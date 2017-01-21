/*
 Zadanie 5:
   Napisa� funkcj� InsertNth, kt�ra wstawia na podanej pozycji
   nowy w�ze� do listy. Indeks powinien by� liczb� z zakresu
   [0..length]. */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "utils.h"

void InsertNth(struct node** headRef, int index, int data) {
  // tw�j kod
}

void BasicCaller() {
  struct node* myList=NULL;
  InsertNth(&myList, 0, 13);
  InsertNth(&myList, 1, 31);
  InsertNth(&myList, 1, 17);
  ShowLinkedList(myList); /* myList={13,17,31} */
  InsertNth(&myList, 5, 99); /* b��d: lista ma d�ugo�� 3 */
}

int main() {
  BasicCaller();
}
