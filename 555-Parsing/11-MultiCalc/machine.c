/* $Source: /home/nls/WEB/zjp/11-MultiCalc/RCS/machine.c,v $
   $Date: 2000/01/22 00:12:20 $
   $Revision: 1.4 $

   This file is distributed WITHOUT ANY WARRANTY, express or implied.
   Copyright (C) 2000 Wlodek Bzyl
   
   Stack machine with relational operators and control flow.
 */
#include <stdio.h>
#include <math.h> /* |pow| */
#include "machine.h"
#include "genlib.h" /* |Error| */
#include "grammar.h"

#define NPROG 2048
machine_instT program[NPROG]; /* the machine */
machine_instT *progp; /* next free spot for code generation */
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
   in the array |program|. It returns the location of the instruction. */
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

/* Machine instructions 1. */

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

/* Machine instructions 2. */

void clear(void) {
  if (stackp<=stack) Error("stack underflow");
  --stackp;
}
void lt(void) {
  machine_stackT d1, d2;
  d2=pop();
  d1=pop();
  d1.val=(double)(d1.val<d2.val);
  push(d1);
}
void le(void) {
  machine_stackT d1, d2;
  d2=pop();
  d1=pop();
  d1.val=(double)(d1.val<=d2.val);
  push(d1);
}
void gt(void) {
  machine_stackT d1, d2;
  d2=pop();
  d1=pop();
  d1.val=(double)(d1.val>d2.val);
  push(d1);
}
void ge(void) {
  machine_stackT d1, d2;
  d2=pop();
  d1=pop();
  d1.val=(double)(d1.val>=d2.val);
  push(d1);
}
void eq(void) {
  machine_stackT d1, d2;
  d2=pop();
  d1=pop();
  d1.val=(double)(d1.val==d2.val);
  push(d1);
}
void ne(void) {
  machine_stackT d1, d2;
  d2=pop();
  d1=pop();
  d1.val=(double)(d1.val!=d2.val);
  push(d1);
}
void factorial(void) {
  machine_stackT d=pop();
  int f, n=(int) d.val;
  if (n<0) 
    Error("factorial called with negative argument");
  else 
    for(f=1; n>1; n--) f*=n;
  d.val=f;
  push(d);
}

void print_exp(void) {
  machine_stackT d;
  d=pop();
  printf("%.4g\n",d.val);
}
void print_string(void) {
  printf("%s", (char *) *pc++);
}

/* To understand |whilecode| and |ifcode| it is critical to realize
   that |execute| marches along a sequence of instructions until it
   finds a |stop|, whereupon it returns. Code generation during
   parsing has carefullly arranged that a |stop| terminates each
   sequence of instructions that should be handled by a single call of
   |execute|. The body of a |while|, and the condition, |then| and
   |else| parts of an |if| are handled by recursive calls to |execute|
   that return to the parent level when they have finished their task.
   The control of these recursive tasks is done by code in |whilecode|
   and |ifcode| that corresponds directly to |while| and |if|
   statements. */

/* When |whilecode| is called, |pc| has already been incremented, so
   it points to the loop body pointer. Thus |pc+1| points to the
   following statement, and |pc+2| points to the condition. */
void whilecode(void) {
  machine_instT *savepc=pc; /* loop body */
  machine_stackT d;
  execute(savepc+2); /* condition */
  d=pop();
  while (d.val) {
    execute(*((machine_instT **)(savepc))); /* body */
    execute(savepc+2);
    d=pop();
  }
  pc=*((machine_instT **)(savepc+1)); /* next statement */
}

/* |ifcode| is similiar; in this case, upon entry |pc| points to
   |then| part, |pc+1| to the |else|, |pc+2| to the next statement,
   and |pc+3| is the condition. */
void ifcode(void) {
  machine_stackT d;
  machine_instT *savepc=pc; /* then part */
  execute(savepc+3); /* condition */
  d=pop();
  if (d.val) 
    execute(*((machine_instT **)(savepc)));
  else if (*((machine_instT **)(savepc+1))!=0) /* else part? */
    execute(*((machine_instT **)(savepc+1)));
  pc=*((machine_instT **)(savepc+2)); /* next stmt */
}
