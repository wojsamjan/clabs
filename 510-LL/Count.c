/*   Plik: Count.c
   Wersja: 22 X 2002

 Zadanie 1:
   Napisaæ funkcjê Count zliczaj±c± ile razy podana liczba
   ca³kowita wystêpuje na li¶cie. */

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

int Count(struct node* head, int searchFor) {
  // twój kod
}

void BasicCaller() {
  struct node* head=NULL;
  int k, n;
  Push(&head,13);
  Push(&head,11);
  Push(&head,11);
  Push(&head,13);
  Push(&head,13);
  n=13;
  k=Count(head,n); /* k powinno byæ równe 3 */
  ShowLinkedList(head);
  printf("\tLiczba %d wystêpuje %d razy na li¶cie.\n", n, k);
}

int main() {
  BasicCaller();
  return EXIT_SUCCESS;
}
