/*
  Zadanie 6:
    Napisa� funkcj� SortedInsert, kt�ra dla listy o danych
    uporz�dkowanych rosn�co i w�z�a, wstawia ten w�ze�
    do listy zachowuj�c jej uporz�dkowanie. */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "utils.h"

void SortedInsert(struct node** headRef, struct node* newNode) {
  // tw�j kod
}

void BasicCaller() {
  struct node* myList=NULL;
  struct node* myNode=malloc(sizeof(struct node));
  myNode->data=4;
  myNode->next=NULL;
  Push(&myList,7);
  Push(&myList,5);
  Push(&myList,3);
  Push(&myList,1);
  SortedInsert(&myList,myNode);
  ShowLinkedList(myList); /* myList={13,17,31} */
}

int main() {
  BasicCaller();
}
