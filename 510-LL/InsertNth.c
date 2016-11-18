/*   Plik: InsertNth.c
   Wersja: 22 X 2002

 Zadanie 5:
   Napisaæ funkcjê InsertNth, która wstawia na podanej pozycji
   nowy wêze³ do listy. Indeks powinien byæ liczb± z zakresu
   [0..length]. */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "utils.h"

void InsertNth(struct node** headRef, int index, int data) {
  // twój kod
}

void BasicCaller() {
  struct node* myList=NULL;
  InsertNth(&myList, 0, 13);
  InsertNth(&myList, 1, 31);
  InsertNth(&myList, 1, 17);
  ShowLinkedList(myList); /* myList={13,17,31} */
  InsertNth(&myList, 5, 99); /* b³±d: lista ma d³ugo¶æ 3 */
}

int main() {
  BasicCaller();
  return EXIT_SUCCESS;
}
