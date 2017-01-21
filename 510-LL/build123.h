#ifndef build123_h
#define build123_h

struct node {
  int data;
  struct node* next;
};

/* Zwróć liczbę węzłów na liście. */
int Length(struct node* head);

/* Wypisz wszystkie elementy listy head. */
void ShowLinkedList(struct node* head);

#endif
