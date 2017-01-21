/*
 Zadanie 1:
   Napisac funkcję Count zliczającą ile razy podana liczba
   całkowita występuje na liście. */

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

int Count(struct node* head, int searchFor) {
  // twój kod
}

void BasicCaller() {
  struct node* head=NULL;
  int k, n;
  Push(&head,13);
  Push(&head,11);
  Push(&head,11);
  Push(&head,13);
  Push(&head,13);
  n=13;
  k=Count(head,n); /* k powinno być równe 3 */
  ShowLinkedList(head);
  printf("\tLiczba %d występuje %d razy na liście.\n", n, k);
}

int main() {
  BasicCaller();
}
