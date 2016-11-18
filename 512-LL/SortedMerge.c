/*   Plik: SortedMerge.c
   Wersja: 31 X 2002

 Zadanie 14:
   Napisaæ funkcjê SortedMerge, która ³±czy dwie listy
   uporz±dkowane rosn±co w jedn± listê uporz±dkowan± rosn±co. */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "utils.h"

void MoveNode(struct node** destRef, struct node** sourceRef) { 
  // rozwi±zanie zadania
}

struct node* SortedMerge(struct node* a, struct node* b) { 
  // twój kod
}

void BasicCaller() {
  struct node* myA=NULL;
  struct node* myB=NULL;
  struct node* myList=NULL;
  Push(&myA,5);
  Push(&myA,2);
  Push(&myA,1);
  Push(&myB,4);
  Push(&myB,3);
  ShowLinkedList(myA); /* myA={1,2,5} */
  ShowLinkedList(myB); /* myB={4,3} */
  myList=SortedMerge(myA,myB);
  ShowLinkedList(myList); /* myList={1,2,3,4,5} */
}

int main() {
  BasicCaller();
  return EXIT_SUCCESS;
}
