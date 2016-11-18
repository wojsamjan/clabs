/*   Plik: skeleton.c
   Wersja: 22 X 2002

   Przyk³adowy kod, pokazuj±cy jak przygotowaæ
   rozwi±zania zadañ dotycz±cych list powi±zanych.

 Zadanie 0:
   Zbudowaæ listê {13, 1, 2, 3}. Nastêpnie, korzystaj±c
   z Push, wstawiæ element `42' na drugiej pozycji
   otrzymuj±c listê {13, 42, 1, 2, 3}. */

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"


void BasicCaller() {
  struct node* head;

  head=BuildOneTwoThree();
  Push(&head,13);
  Push(&head->next,42);
  ShowLinkedList(head);
}

int main() {
  BasicCaller();
  return EXIT_SUCCESS;
}
