/*   Plik: AlternatingSplit.c
   Wersja: 31 X 2002

 Zadanie 12:
   Napisz funkcjê AlternatingSplit, która podan± listê dzieli
   na dwie krótsze listy. Jedna lista powinna zawieraæ wêz³y
   o indeksach nieparzystych, a druga o indeksach parzystych. */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "utils.h"

void AlternatingSplit(struct node* source,
		      struct node** aRef, struct node** bRef) { 
  // twój kod
}

void BasicCaller() {
  struct node* myList=NULL;
  struct node* myOdd=NULL;
  struct node* myEven=NULL;
  Push(&myList,1);
  Push(&myList,2);
  Push(&myList,1);
  Push(&myList,2);
  Push(&myList,1);
  ShowLinkedList(myList); /* myList={1,2,1,2,1} */
  AlternatingSplit(myList,&myOdd,&myEven);
  ShowLinkedList(myOdd); /* myOdd={1,1,1} */
  ShowLinkedList(myEven); /* myEven={2,2} */
}

int main() {
  BasicCaller();
  return EXIT_SUCCESS;
}
