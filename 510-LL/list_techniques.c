/*   Plik: list_techniques.c
   Wersja: 22 X 2002

   Kilka technik do wykorzystania w zadaniach. */

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"


/* Buduj listę dodając węzły na początku listy (head). */

struct node* AddAtHead() {
  struct node* head=NULL;
  int i;
  for (i=1; i<5; i++)
    Push(&head,i);
  return head; /* head={4,3,2,1} */
};

/* Buduj listę korzystając ze wskaźnika na koniec listy (tail).
   Pierwszy węzeł na liście musi być potraktowany inaczej
   niż węzły wewnętrzne. Poniżej zaprezentowane są trzy
   sposoby potraktowania pierwszego węzła. */

/* Sposób 1: przypadek specjalny. */

struct node* BuildWithSpecialCase() {
  struct node* head=NULL;
  struct node* tail;
  int i;
  /* dodaj pierwszy węzeł do pustej listy i ustaw wskaźnik tail */
  Push(&head,1);
  tail=head;
  /* pozostałe węzły dodajemy wykorzystując wskaźnik tail */
  for (i=2; i<5; i++) {
    Push(&(tail->next),i); /* dodaj węzeł w tail->next */
    tail=tail->next;
  }
  return head; /* head={1,2,3,4} */
}

/* Sposób 2: pseudowęzeł (dummy node). */

struct node* BuildWithDummyNode() {
  struct node dummy = {0, NULL}; /* pierwszy węzeł */
  struct node* tail=&dummy;
  int i;
  for (i=1; i<5; i++) {
    Push(&(tail->next),i+10); /* dodaj węzeł w tail->next */
    tail=tail->next;
  }
  return dummy.next; /* head={1,2,3,4} */
}

/* Sposób 3: lokalny odnośnik (local reference). */

struct node* BuildWithLocalReference() {
  struct node* head=NULL;
  struct node** lastPtrRef=&head;
  int i;
  for (i=1; i<6; i++) {
    Push(lastPtrRef,i+20);
    lastPtrRef=&((*lastPtrRef)->next);
  }
  return head; /* head={21,22,23,24,25} */
}


int main() {
  struct node* head;
  printf("Dodawaj węzły do początku listy.\n");
  head=AddAtHead();
  ShowLinkedList(head);
  printf("Dodawaj węzły na końcu listy.\n");
  printf("  1. Przypadek specjalny.\n");
  head=BuildWithSpecialCase();
  ShowLinkedList(head);
  printf("  2. Pseudowęzeł.\n");
  head=BuildWithDummyNode();
  ShowLinkedList(head);
  printf("  3. Lokalny odnośnik.\n");
  head=BuildWithLocalReference();
  ShowLinkedList(head);
  return EXIT_SUCCESS;
}
