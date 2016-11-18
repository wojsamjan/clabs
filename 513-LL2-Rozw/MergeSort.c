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
  int len=Length(source);
  int i;
  struct node* current=source;
  if (len<2) {
    *frontRef=source;
    *backRef=NULL;
  } else {
    int hopCount=((len+1)/2)-1;
    for (i=0; i<hopCount; i++) {
      current=current->next;
    }
    *frontRef=source;
    *backRef=current->next;
    current->next=NULL;
  }
}

void MoveNode(struct node** destRef, struct node** sourceRef) { 
  struct node* newNode=*sourceRef;
  assert(newNode!=NULL);
  *sourceRef=newNode->next;
  newNode->next=*destRef;
  *destRef=newNode;
}

struct node* SortedMerge(struct node* a, struct node* b) { 
  struct node* result=NULL;
  struct node** lastPtrRef=&result;
  while (1) {
    if (a==NULL) {
      *lastPtrRef=b;
      break;
    } else if (b==NULL) {
      *lastPtrRef=a;
      break;
    }
    if (a->data<=b->data) {
      MoveNode(lastPtrRef,&a);
    } else {
      MoveNode(lastPtrRef,&b);
    }
    lastPtrRef=&((*lastPtrRef)->next);
  }
  return result;
}

void MergeSort(struct node** headRef) {
  struct node* head=*headRef;
  struct node* a;
  struct node* b;
  if ((head==NULL) || (head->next==NULL))
    return;
  FrontBackSplit(head,&a,&b); /* mo¿na te¿ u¿yæ AlternateSplit */
  MergeSort(&a);
  MergeSort(&b);
  *headRef=SortedMerge(a,b);
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
