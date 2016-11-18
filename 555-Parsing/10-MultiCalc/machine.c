/* $Source: /home/nls/WEB/zjp/10-MultiCalc/RCS/machine.c,v $
   $Date: 2000/01/10 00:28:39 $
   $Revision: 1.6 $

   This file is distributed WITHOUT ANY WARRANTY, express or implied.
   Copyright (C) 2000 Wlodek Bzyl

   An intermediate step for an simple "stack machine".
 */

#include <stdio.h>
#include <math.h> /* |pow| */
#include "machine.h"
#include "genlib.h" /* |Error| */
#include "grammar.h"

#define NPROG 2048
machine_instT program[NPROG]; /* the machine */
static machine_instT *progp; /* next free spot for code generation */
static machine_instT *pc; /* program counter during execution */

/* Each element on the interpreter stack is either a floating point
   value or a pointer to a symbol table entry. */
typedef union {
  double val;
  symrecT sym;
} machine_stackT;

#define NSTACK 256
static machine_stackT stack[NSTACK]; /* the stack used by the machine */
static machine_stackT *stackp; /* next free spot on stack */

/* The stack is manipulated by calls to |push| and |pop| */
void push(machine_stackT d) {
  if (stackp>=&stack[NSTACK]) Error("stack overflow");
  *stackp++=d;
}
machine_stackT pop(void) {
  if (stackp<=stack) Error("stack underflow");
  return *--stackp;
}

/* Initialize for code generation. */
void init_code(void) {
  stackp=stack;
  progp=program;
}

/* The machine is generated during parsing by calls to the function
   |code| which simply puts an instruction into the next free spot
   in the array |program|. It returns the location of the
   instruction (note: not used in this version of calculator). */
machine_instT *code(machine_instT f) {
  machine_instT *inst_location=progp;
  if (progp>=&program[NPROG]) Error("program to big");
  *progp++=f;
  return inst_location;
}

/* Each cycle executes the function pointed to by the instruction
   pointed to by the program counter |pc|, and increments |pc| so
   it's ready for the next instruction. An instruction |stop|
   terminates the loop. Instructions |constpush|, |varpush| and
   |bltin| also increment |pc| to step over any arguments that
   follow. */

void execute(machine_instT *p) {
  for (pc=p; *pc!=stop; ) 
    (*(*pc++))();
}

void constpush(void) {
  machine_stackT d;
  d.val=((symrecT)*pc++)->u.val;
  push(d);
}
void varpush(void) {
  machine_stackT d;
  d.sym=(symrecT)(*pc++);
  push(d);
}

/* Arithmetic operations are basically the same. */

void add(void) {
  machine_stackT d1, d2;
  d2=pop();
  d1=pop();
  d1.val+=d2.val;
  push(d1);
}
void sub(void) {
  machine_stackT d1, d2;
  d2=pop();
  d1=pop();
  d1.val-=d2.val;
  push(d1);
}
void mul(void) {
  machine_stackT d1, d2;
  d2=pop();
  d1=pop();
  d1.val*=d2.val;
  push(d1);
}
void divide(void) {
  machine_stackT d1, d2;
  d2=pop();
  d1=pop();
  d1.val/=d2.val;
  push(d1);
}
void power(void) {
  machine_stackT d1, d2;
  d2=pop();
  d1=pop();
  d1.val=pow(d1.val,d2.val);
  push(d1);
}
void negate(void) {
  machine_stackT d;
  d=pop();
  d.val=-d.val;
  push(d);
}

/* The remaining routines are equally simple. */

void eval(void) {
  machine_stackT d;
  d=pop();
  if (d.sym->type==UNDEF) 
    Error("undefined variable %s",d.sym->name);
  d.val=d.sym->u.val;
  push(d);
}

void assign(void) {
  machine_stackT d1, d2;
  d1=pop();
  d2=pop();
  if (d1.sym->type!=VAR && d1.sym->type!=UNDEF) 
    Error("assignment to non-variable %s",d1.sym->name);
  d1.sym->u.val=d2.val;
  d1.sym->type=VAR;
  push(d2);
}

void display(void) {
  machine_stackT d;
  d=pop();
  printf("\t%.10g\n",d.val);
}

/* cdecl> explain (double (*) ()) f */
void bltin(void) {
  machine_stackT d;
  d=pop();
  /* With the rule: 
       BLTIN '(' exp ')' { code2(bltin, (machine_instT)$1->u.ptr);
     we had to cast |*pc| into pointer to function returning double
     with the following code: 
       d.val=(*(double (*)())(*pc))(d.val); */
  d.val=(((symrecT)(*pc++))->u.ptr)(d.val);
  push(d);
}

/* This name shows when debugging. */
void stop(void) {
  Error("this can't happen (function `stop' was executed)");
}
