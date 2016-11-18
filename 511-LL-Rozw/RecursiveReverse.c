/*   Plik: RecursiveReverse.c
   Wersja: 22 X 2002

*Zadanie 18:
   Napisaæ rekurencyjn± funkcjê RecursiveReverse odwracaj±c±
   kolejno¶æ elementów na podanej li¶cie. */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "utils.h"

void RecursiveReverse(struct node** headRef) {
  struct node* first;
  struct node* rest;
  if (*headRef==NULL)
    return;
  first=*headRef;
  rest=first->next;
  if (rest==NULL)
    return;
  RecursiveReverse(&rest);
  first->next->next=first;
  first->next=NULL; /* ! zrób rysunek */
  *headRef=rest;
}

void BasicCaller() {
  struct node* myList=NULL;
  Push(&myList,17);
  Push(&myList,15);
  Push(&myList,13);
  Push(&myList,11);
  ShowLinkedList(myList); /* myList={11,13,15,17} */
  RecursiveReverse(&myList);
  printf("\tRecursiveReverse(&myList)\n");
  ShowLinkedList(myList); /* myList={17,15,13,11} */
}

int main() {
  BasicCaller();
  return EXIT_SUCCESS;
}
