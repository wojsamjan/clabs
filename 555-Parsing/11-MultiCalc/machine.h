/* $Source: /home/nls/WEB/zjp/11-MultiCalc/RCS/machine.h,v $
   $Date: 2000/01/22 00:12:20 $
   $Revision: 1.4 $

   This file is distributed WITHOUT ANY WARRANTY, express or implied.
   Copyright (C) 2000 Wlodek Bzyl

   Stack machine with relational operators and control flow.
 */

#ifndef _machine_h
#define _machine_h
#include "init.h"

/* This the data type of a machine instruction. */
typedef void (*machine_instT)(void);

/* Next free spot for code generation. */
extern machine_instT *progp;

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

/* Machine instructions 1. */

/* Must be NULL; this value is used in |ifcode| when deciding if
   else part was present / should be executed. */
#define stop (machine_instT)0

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

/* Machine instructions 2. */

void clear(void); /* pop top value from the stack (but don't return it) */
void print_exp(void); /* print numeric value */
void print_string(void); /* print string */
void lt(void); /* less than */
void le(void); /* less equal */
void gt(void); /* grater than */
void ge(void); /* grater than or equal */
void eq(void); /* equal */
void ne(void); /* not equal */
void factorial(void);
void whilecode(void); /* while statement */
void ifcode(void); /* if statement */

#endif
