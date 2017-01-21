#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

int Length(struct node* head) {
  int count=0;
  struct node* current=head;
  while (current!=NULL) {
    count++;
    current=current->next;
  }
  return count;
}

void Push(struct node** headRef, int newData) {
  struct node* newNode=malloc(sizeof(struct node));
  newNode->data=newData;
  newNode->next=*headRef;
  *headRef=newNode;
}

struct node* BuildOneTwoThree() {
  struct node* head=NULL;
  Push(&head,3);
  Push(&head,2);
  Push(&head,1);
  return head;
}

void ShowLinkedList(struct node* head) {
  struct node* current=head;
  printf("\tLista:");
  while (current!=NULL) {
    printf(" %d",current->data);
    current=current->next;
  }
  printf("\n");
  printf("\tD�ugo�� listy: %d\n",Length(head));

}
