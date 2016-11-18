/*   Plik: ShuffleMerge.c
   Wersja: 31 X 2002

 Zadanie 13:
   Dla danych dwóch list, po³±cz je bior±c naprzemian wêz³y
   z ka¿dej listy. Na przyk³ad ShuffleMerge zastosowane do
   list {1,2,3} i {11,12,13} powinno daæ listê {1,11,2,12,3,14}. */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "utils.h"

struct node* ShuffleMerge(struct node* a, struct node* b) { 
  struct node dummy;
  struct node* tail=&dummy;
  dummy.next=NULL;
  while (1) {
    if (a==NULL) {
      tail->next=b;
      break;
    } else if (b==NULL) {
      tail->next=a;
      break;
    } else { /* move two nodes to tail */
      tail->next=a;
      tail=a;
      a=a->next;
      tail->next=b;
      tail=b;
      b=b->next;
    }
  }
  return dummy.next;
}

void BasicCaller() {
  struct node* myA=NULL;
  struct node* myB=NULL;
  struct node* myList=NULL;
  Push(&myA,3);
  Push(&myA,2);
  Push(&myA,1);
  Push(&myB,13);
  Push(&myB,11);
  ShowLinkedList(myA); /* myA={1,2,3} */
  ShowLinkedList(myB); /* myB={11,13} */
  myList=ShuffleMerge(myA,myB);
  ShowLinkedList(myList); /* myList={1,11,2,13,3} */
}

int main() {
  BasicCaller();
  return EXIT_SUCCESS;
}
