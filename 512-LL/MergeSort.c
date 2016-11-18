/*   Plik: MergeSort.c
   Wersja: 31 X 2002

 Zadanie 15 (rekurencja):
   Zaimplementowaæ algorytm ,,merge sort''. Skorzystaæ
   z funkcji FrontBackSplit i SortedMerge. */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "utils.h"

void FrontBackSplit(struct node* source, 
		   struct node** frontRef, struct node** backRef) {
  // rozwi±zanie zadania
}

void MoveNode(struct node** destRef, struct node** sourceRef) { 
  // rozwi±zanie zadania
}

struct node* SortedMerge(struct node* a, struct node* b) { 
  // rozwi±zanie zadania
}

void MergeSort(struct node** headRef) {
  // twój kod
}

void BasicCaller() {
  struct node* myList=NULL;
  Push(&myList,4);
  Push(&myList,5);
  Push(&myList,2);
  Push(&myList,1);
  Push(&myList,3);
  ShowLinkedList(myList); /* myList={3,1,2,4,5} */
  MergeSort(&myList);
  ShowLinkedList(myList); /* myList={1,2,3,4,5} */
}

int main() {
  BasicCaller();
  return EXIT_SUCCESS;
}
