/*   Plik: DeleteList.c
   Wersja: 22 X 2002

 Zadanie 3:
   Napisaæ funkcjê DeleteList, która dla podanej listy zwalnia
   pamiêæ jej przydzielon± oraz zeruje wska¼nik na pocz±tek
   listy (pusta lista). */

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

void DeleteList(struct node** headRef) {
  struct node* current=*headRef;
  struct node* next;
  while (current!=NULL) {
    next=current->next;
    free(current);
    current=next;
  }
  *headRef=NULL;
}

void BasicCaller() {
  struct node* myList=BuildOneTwoThree();
  DeleteList(&myList);
  ShowLinkedList(myList);
}

int main() {
  BasicCaller();
  return EXIT_SUCCESS;
}
