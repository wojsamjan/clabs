/*   Plik: SortedInsert.c
   Wersja: 22 X 2002

 Zadanie 8:
   Napisaæ funkcjê Append o dwóch argumentach `dest' i `src' 
   bêd±cych listami, która listê `src' dopisze na koñcu listy `dest'
   i ustawi `src' na NULL (,,wyzeruje'' listê `src'). */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "utils.h"

void Append(struct node** dest, struct node** src) {
  struct node* current;
  if (*dest==NULL)
    *dest=*src;
  else {
    current=*dest;
    while (current->next!=NULL)
      current=current->next;
    current->next=*src;
  }
  *src=NULL;
}

void BasicCaller() {
  struct node* a=NULL;
  struct node* b=NULL;
  Push(&a,2);
  Push(&a,1);
  ShowLinkedList(a); /* a={1,2} */
  Push(&b,17);
  Push(&b,15);
  Push(&b,13);
  Push(&b,11);
  ShowLinkedList(b); /* b={11,13,15,17} */
  printf("\tAppend(&a, &b)\n");
  Append(&a,&b);
  ShowLinkedList(a); /* a={1,2,11,13,15,17} */
  ShowLinkedList(b); /* b={} */
}

int main() {
  BasicCaller();
  return EXIT_SUCCESS;
}
