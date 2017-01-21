/*
  Przyk�adowy kod, pokazuj�cy jak przygotowa�
  rozwi�zania zada� dotycz�cych list powi�zanych.

  Zadanie 0:
    Zbudowa� list� {13, 1, 2, 3}. Nast�pnie, korzystaj�c
    z Push, wstawi� element `42' na drugiej pozycji
    otrzymuj�c list� {13, 42, 1, 2, 3}. */

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
}
