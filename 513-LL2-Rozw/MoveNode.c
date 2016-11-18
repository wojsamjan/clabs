/*   Plik: MoveNode.c
   Wersja: 31 X 2002

 Zadanie 11:
   Funkcja MoveNode dzia³a podobnie do funkcji Push.
   Dla danych dwóch list funkcja ta usuwa pierwszy
   element z drugiej listy i wstawia go na pocz±tek
   drugiej listy. */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "utils.h"

void MoveNode(struct node** destRef, struct node** sourceRef) { 
  struct node* newNode=*sourceRef;
  assert(newNode!=NULL);
  *sourceRef=newNode->next;
  newNode->next=*destRef;
  *destRef=newNode;
}

void BasicCaller() {
  struct node* source=NULL;
  struct node* dest=NULL;
  Push(&dest,3);
  Push(&dest,2);
  Push(&dest,1);
  Push(&source,13);
  Push(&source,11);
  ShowLinkedList(dest); /* dest={1,2,3} */
  ShowLinkedList(source); /* source={11,13} */
  MoveNode(&dest,&source);
  ShowLinkedList(dest); /* dest={11,1,2,3} */
  ShowLinkedList(source); /* source={13} */
}

int main() {
  BasicCaller();
  return EXIT_SUCCESS;
}
