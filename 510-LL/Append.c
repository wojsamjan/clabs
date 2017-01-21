/*
  Zadanie 8:
    Napisa� funkcj� Append o dw�ch argumentach `dest' i `src'
    b�d�cych listami, kt�ra list� `src' dopisze na ko�cu listy `dest'
    i ustawi `src' na NULL (,,wyzeruje'' list� `src'). */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "utils.h"

void Append(struct node** dest, struct node** src) {
  // tw�j kod
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
}
