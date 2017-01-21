/*
 Zadanie 2:
   Napisa� funkcj� GetNth, kt�ra dla podanej listy i indeksu
   zwraca warto�� przechowywan� w w��le na pozycji podanej
   w indeksie. Pierwszy w�ze� ma pozycj� `0', drugi -- `1' itd.
   Na przyk�ad, dla listy {3,44,1,17} funkcja GetNth wywo�ana
   z indeksem 1 powinna zwr�ci� 44.
   Indeks powinien by� w zakresie [0..d�ugo��_listy). */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "utils.h"

int GetNth(struct node* head, int index) {
  // tw�j kod
  assert(0); /* funkcja wo�aj�ca ��da nie istniej�cego w�z�a */
}

void BasicCaller() {
  struct node* myList=BuildOneTwoThree();
  int nodeIndex;
  int nodeData;
  nodeIndex=1;
  nodeData=GetNth(myList,nodeIndex); /* nodeData==2 */
  ShowLinkedList(myList);
  printf("\tW %d. w��le znajduje si� %d.\n", nodeIndex, nodeData);
}

int main() {
  BasicCaller();
}
