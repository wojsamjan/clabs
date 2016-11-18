#ifndef utils_h
#define utils_h

struct node {
  int data;
  struct node* next;
};

/* Zwróæ liczbê wêz³ów na li¶cie. */
int Length(struct node* head);

/* Dodaj nowy wêze³, do listy *headRef
   i umie¶æ w wê¼le w polu .data liczbê newData. */
void Push(struct node** headRef, int newData);

/* Zbuduj listê {1, 2, 3} i zwróæ wska¼nik do niej. */
struct node* BuildOneTwoThree(void);

/* Wypisz wszystkie elementy listy head. */
void ShowLinkedList(struct node* head);

#endif
