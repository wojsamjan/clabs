/*   Plik: SortedInsert.c
   Wersja: 22 X 2002

 Zadanie 6:
   Napisaæ funkcjê SortedInsert, która dla listy o danych 
   uporz±dkowanych rosn±co i wêz³a, wstawia ten wêze³
   do listy zachowuj±c jej uporz±dkowanie. */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "utils.h"

void SortedInsert(struct node** headRef, struct node* newNode) {
  if (*headRef==NULL || (*headRef)->data>=newNode->data) {
    newNode->next=*headRef;
    *headRef=newNode;
  } else {
    struct node* current=*headRef;
    while (current->next!=NULL && current->next->data<newNode->data)
      current=current->next;
    newNode->next=current->next;
    current->next=newNode;
  }
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
  ShowLinkedList(myList); /* myList={1,3,4,5,7} */
}

int main() {
  BasicCaller();
  return EXIT_SUCCESS;
}
