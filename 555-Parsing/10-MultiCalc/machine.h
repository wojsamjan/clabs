/* $Source: /home/nls/WEB/zjp/10-MultiCalc/RCS/machine.h,v $
   $Date: 2000/01/10 00:30:32 $
   $Revision: 1.3 $

   This file is distributed WITHOUT ANY WARRANTY, express or implied.
   Copyright (C) 2000 Wlodek Bzyl

   An intermediate step for an simple "stack machine".
 */

#ifndef _machine_h
#define _machine_h
#include "init.h"

/* This the data type of a machine instruction --
   a pointer to a procedure. */
typedef void (*machine_instT)(void);

/* The machine is an array of pointers that point either to
   routines like |mul| that perform operations, or to data in the
   symbol table. */
extern machine_instT program[];

/* This function installs one instruction or operand.
   Notice that the arguments to |code| are function names, that is,
   pointers to function names, or other values that are coerced to
   function pointers. */
machine_instT *code(machine_instT f);

#define code2(c1,c2)     code(c1); code(c2)
#define code3(c1,c2,c3)  code(c1); code(c2); code(c3)

/* Initialize for code generation. */
void init_code(void);

/* This function runs the machine. */
void execute(machine_instT *p);

/* Machine instructions. */

void stop(void); /* end of instruction sequence */

void constpush(void); /* push constant onto stack */
void varpush(void); /* push variable onto stack */

void add(void); /* add top two elements on stack */
void sub(void); /* subtract */
void mul(void); /* multiply */
void divide(void);
void power(void); /* exponentiation */
void negate(void);

void eval(void); /* evaluate variable on stack */
void assign(void); /* assign top value to next value */
void display(void); /* pop top value from stack and display it */
void bltin(void); /* evaluate built-in on top of stack */

#endif
