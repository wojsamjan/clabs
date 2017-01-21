#ifndef utils_h
#define utils_h

struct node {
  int data;
  struct node* next;
};

/* zwróć liczbę  węzłów na liście */
int Length(struct node* head);

/* dodaj nowy węzeł do listy *headRef
   i umieść w węźle w polu .data liczbę newData */
void Push(struct node** headRef, int newData);

/* zbuduj listę {1, 2, 3} i zwróć wskaźnik do niej */
struct node* BuildOneTwoThree(void);

/* wypisz wszystkie elementy listy head */
void ShowLinkedList(struct node* head);

#endif
