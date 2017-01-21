/*
  Zadanie 18:
    Napisa� rekurencyjn� funkcj� RecursiveReverse odwracaj�c�
    kolejno�� element�w na podanej li�cie. */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "utils.h"

void RecursiveReverse(struct node** headRef) {
  // tw�j kod
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
}
