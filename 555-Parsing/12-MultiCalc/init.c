/* $Source: /home/nls/WEB/zjp/11-MultiCalc/RCS/init.c,v $
   $Date: 2000/01/21 16:09:55 $
   $Revision: 1.3 $

   This file is distributed WITHOUT ANY WARRANTY, express or implied.
   Copyright (C) 2000 Wlodek Bzyl

   Initialization of symbol table with built-ins, constants and keywords.
 */

#include <math.h>
#include "genlib.h" /* |New| */
#include "symtab.h"
#include "init.h"
#include "machine.h" /* |machine_instT| for |YYSTYPE| */
#include "grammar.h"


struct init_func {
  char *name;
  double (*func)();
};

static struct init_func builtins[]={
  { "sin", sin }, { "cos", cos }, { "atan", atan }, 
  { "ln", log }, { "exp", exp }, { "sqrt", sqrt }, 
  { 0, 0 }
};

struct init_consts {
  char *name;
  double cval;
};

static struct init_consts consts[]={
  { "PI", 3.141592 }, 
  { "E", 2.718281 }, 
  { "DEG", 57.2957 },  /* deg/radian */
  { "PHI", 1.618034 }, /* golden ratio */
  { 0, 0 }
};

struct init_keywords {
  char *name;
  int kval;
};

static struct init_keywords keywords[]={
  { "if", IF }, 
  { "else", ELSE },
  { "while", WHILE }, 
  { "print", PRINT }, 
  { "exec", RUN },
  { 0, 0 }
};

/* Public entries */

symtabADT sym_table; /* main symbol table */

void init_sym_table(void) {
  int i;
  symrecT entry;
  sym_table=new_symbol_table();
  for (i=0; builtins[i].name!=0; i++) {
    entry=New(symrecT);
    entry->type=BLTIN;
    entry->u.ptr=builtins[i].func;
    enter(sym_table,builtins[i].name,entry);
  }
  for (i=0; consts[i].name!=0; i++) {
    entry=New(symrecT);
    entry->type=VAR;
    entry->u.val=consts[i].cval;
    enter(sym_table,consts[i].name,entry);
  }
  for (i=0; keywords[i].name!=0; i++) {
    entry=New(symrecT);
    entry->type=keywords[i].kval;
    entry->u.val=0.0;
    enter(sym_table,keywords[i].name,entry);
  }
}
