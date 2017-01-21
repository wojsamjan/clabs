#include <stdio.h>
#include <stdlib.h>
#include "build123.h"

struct node* BuildOneTwoThree() {
  struct node* head, *second, *third;
  head=malloc(sizeof(struct node));
  second=malloc(sizeof(struct node));
  third=malloc(sizeof(struct node));

  head->data=1;
  head->next=second;

  second->data=2;
  second->next=third;

  third->data=3;
  third->next=NULL;

  return head;
}

int main() {
  struct node* head;

  printf("\tBuduję listę {1, 2, 3}\n");
  head=BuildOneTwoThree();
  ShowLinkedList(head);
}
