/* Plik: build123.c
         22 X 2002
 */

#include <stdio.h>
#include <stdlib.h>
#include "build123.h"

int Length(struct node* head) {
  int count=0;
  struct node* current=head;
  while (current!=NULL) {
    count++;
    current=current->next;
  }
  return count;
}

void ShowLinkedList(struct node* head) {
  struct node* current=head;
  printf("\tLista:");
  while (current!=NULL) {
    printf(" %d",current->data);
    current=current->next;
  }
  printf("\n");
  printf("\tDługość listy: %d\n",Length(head));
}
