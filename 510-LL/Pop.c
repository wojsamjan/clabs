/*
  Zadanie 4:
    Napisa� funkcj� Pop -- przeciwie�stwo Push.
    Pop powinna z niepustej listy usun�� jej pocz�tkowy
    w�ze� i zwr�ci� warto�� przechowywan� w tym w��le.
    Wykorzystaj standardow� funkcj� `assert', je�li nie
    b�dzie w�z�a do usuni�cia (lista jest pusta). */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "utils.h"

int Pop(struct node** headRef) {
  // tw�j kod
}

void BasicCaller() {
  struct node* myList=BuildOneTwoThree();
  int a, b, c;
  ShowLinkedList(myList);
  a=Pop(&myList);
  b=Pop(&myList);
  c=Pop(&myList);
  printf("\tUsuni�to elementy: %d %d %d z listy.\n",a,b,c);
  a=Pop(&myList); /* pr�ba usuni�cia elementu z pustej listy */
}

int main() {
  BasicCaller();
}
