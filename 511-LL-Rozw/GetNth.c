/*   Plik: GetNth.c
   Wersja: 22 X 2002

 Zadanie 2:
   Napisaæ funkcjê GetNth, która dla podanej listy i indeksu
   zwraca warto¶æ przechowywan± w wê¼le na pozycji podanej
   w indeksie. Pierwszy wêze³ ma pozycjê `0', drugi -- `1' itd.
   Na przyk³ad, dla listy {3,44,1,17} funkcja GetNth wywo³ana
   z indeksem 1 powinna zwróciæ 44.
   Indeks powinien byæ w zakresie [0..d³ugo¶æ_listy). */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "utils.h"

int GetNth(struct node* head, int index) {
  struct node* current=head;
  int count=0;
  while (current!=NULL) {
    if (count==index)
      return current->data;
    count++;
    current=current->next;
  }
  assert(0); /* funkcja wo³aj±ca ¿±da nie istniej±cego wêz³a */
}

void BasicCaller() {
  struct node* myList=BuildOneTwoThree();
  int nodeIndex;
  int nodeData;
  nodeIndex=1;
  nodeData=GetNth(myList,nodeIndex); /* nodeData==2 */
  ShowLinkedList(myList);
  printf("\tW %d. wê¼le znajduje siê %d.\n", nodeIndex, nodeData);
}

int main() {
  BasicCaller();
  return EXIT_SUCCESS;
}
