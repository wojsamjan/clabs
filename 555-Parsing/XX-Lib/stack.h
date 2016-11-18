/* ----------------------------------------------------------
   $Source: /home/nls/WEB/zjp/XX-Lib/RCS/stack.h,v $
   $Date: 2000/01/08 14:20:16 $
   $Revision: 1.1 $

   This file provides a STACK interface.
   It is distributed WITHOUT ANY WARRANTY, express or implied.
   Copyright (C) 2000 Wlodek Bzyl

   This interface defines an abstraction for stacks.
   In any single application that uses this interface, the values
   in the stack are constrained to a single type, although it is
   easy to change that type by changing the definition of
   |stack_elementT| in this interface.
 */

#ifndef _stack_h
#define _stack_h

#include "genlib.h"  /* type |bool| */

/* This type is used in this interface to indicate the type of values
   that can be stored in the stack. Here the stack is used to store
   values of type |void *|, but that can be changed by editing the
   definition line below.
 */

typedef void *stackElementT;

/* The type |stackADT| represents the abstract type used to store the
   elements that have been pushed. Because |stackADT| is defined only
   as a pointer to a concrete structure that is not itself defined in
   the interface, clients have no access to underlying structure.
 */
typedef struct stackCDT *stackADT;

/* This function allocates and returns a new stack, which is
   initially empty.
 */
stackADT new_stack(void);

/* This function frees the storage associated with the stack.
 */
void free_stack(stackADT stack);

/* This function pushes the specified element onto the stack.
 */
void push(stackADT stack, stackElementT element);

/* This function pops the top element from the stack and returns that
   value. The first value popped is always the last one that was
   pushed. If the stack is empty when |pop| is called, the function
   calls |Error| with an appropriate message.
*/
stackElementT pop(stackADT stack);

/* This functions test whether the stack is empty.
 */
bool stack_is_empty(stackADT stack);

/* This function returns the number of elements currently pushed on
   the stack.
 */
int stack_depth(stackADT stack);

/* This function pops all elements from the stack.
 */
void clear_stack(stackADT stack);

/* This function returns the element at the specified index |n|
   in the stack, where the top of the stack is defined as index 0. 
   This function is provided principally to facilitate debugging.
 */
stackElementT get_stack_element(stackADT stack, int n);

#endif
