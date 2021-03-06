/*   Plik: RemoveDuplicates.c
   Wersja: 31 X 2002

 Zadanie 10:
   Napisz funkcj�, kt�ra z listy posortowanej rosn�co usuwa
   powtarzaj�ce si� w�z�y. */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "utils.h"

void RemoveDuplicates(struct node* head) { 
  struct node* current=head;
  if (current==NULL)
    return;
  while (current->next!=NULL) {
    if (current->data==current->next->data) {
      struct node* nextNext=current->next->next;
      free(current->next);
      current->next=nextNext;
    } else {
      current=current->next;
    }
  }
}

void BasicCaller() {
  struct node* myList=NULL;
  Push(&myList,11);
  Push(&myList,11);
  Push(&myList,7);
  Push(&myList,3);
  Push(&myList,3);
  ShowLinkedList(myList); /* myList={3,3,7,11,11} */
  RemoveDuplicates(myList);
  ShowLinkedList(myList); /* myList={3,7,11} */
}

int main() {
  BasicCaller();
  return EXIT_SUCCESS;
}
