/*   Plik: Pop.c
   Wersja: 22 X 2002

 Zadanie 4:
   Napisaæ funkcjê Pop -- przeciwieñstwo Push.
   Pop powinna z niepustej listy usun±æ jej pocz±tkowy
   wêze³ i zwróciæ warto¶æ przechowywan± w tym wê¼le.
   Wykorzystaj standardow± funkcjê `assert', je¶li nie
   bêdzie wêz³a do usuniêcia (lista jest pusta). */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "utils.h"

int Pop(struct node** headRef) {
  struct node* head=*headRef;
  int result;
  assert(head!=NULL);
  result=head->data;
  *headRef=head->next;
  free(head);
  return result;
}

void BasicCaller() {
  struct node* myList=BuildOneTwoThree();
  int a, b, c;
  ShowLinkedList(myList);
  a=Pop(&myList); 
  b=Pop(&myList);
  c=Pop(&myList);
  printf("\tUsuniêto elementy: %d %d %d z listy.\n",a,b,c);
  a=Pop(&myList); /* próba usuniêcia elementu z pustej listy */  
}

int main() {
  BasicCaller();
  return EXIT_SUCCESS;
}
