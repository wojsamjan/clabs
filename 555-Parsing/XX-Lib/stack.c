/* $Source: /home/nls/WEB/zjp/XX-Lib/RCS/stack.c,v $
   $Date: 2000/01/08 14:20:16 $
   $Revision: 1.1 $

   This file implements the STACK interface.
   It is distributed WITHOUT ANY WARRANTY, express or implied.
   Copyright (C) 2000 Wlodek Bzyl
 */

#include <stdio.h>
#include "genlib.h"
#include "stack.h"

/* This constant specifes the initial amount of space to allocate
   for the array that holds the stack elements. Attempts to pus
   more than this many values will result in doubling the stack
   size. 
 */
#define InitialStackSize 101

/* This type is the concrete representation of the type |stackADT|
   defined in the `stack.h' interface.
 */
struct stackCDT {
  stackElementT *elements;
  int count;
  int size;
};

static void expand_stack(stackADT);

/* Eksportowane functions. */

stackADT new_stack(void) {
  stackADT stack;

  stack=New(stackADT);
  stack->elements=NewArray(InitialStackSize, stackElementT);
  stack->count=0;
  stack->size=InitialStackSize;
  return stack;
}

void free_stack(stackADT stack) {
  FreeBlock(stack->elements);
  FreeBlock(stack);
}

void push(stackADT stack, stackElementT element) {
  if (stack->count==stack->size) expand_stack(stack);
  stack->elements[stack->count++]=element;
}

static void expand_stack(stackADT stack) {
  stackElementT *array;
  int i, newSize;

  newSize=stack->size*2;
  array=NewArray(newSize, stackElementT);
  for (i=0; i<stack->size; i++) array[i]=stack->elements[i];
  FreeBlock(stack->elements);
  stack->elements=array;
  stack->size=newSize;
}

stackElementT pop(stackADT stack) {
  if (stack_is_empty(stack)) Error("pop of an empty stack");
  return stack->elements[--stack->count];
}

bool stack_is_empty(stackADT stack) {
  return stack->count==0;
}

int stack_depth(stackADT stack) {
  return stack->count;
}

stackElementT get_stack_element(stackADT stack, int index) {
  if (index<0 || index>=stack->count) Error("non-existent stack element");
  return stack->elements[stack->count-index-1];
}

void clear_stack(stackADT s) {
  while(!stack_is_empty(s)) pop(s);
}
