/* $Source: /home/nls/WEB/zjp/09-MultiCalc/RCS/init.h,v $
   $Date: 2000/01/10 00:53:41 $
   $Revision: 1.1 $

   This file contains declarations common for: grammar.y, lex.l, and init.c
   It is distributed WITHOUT ANY WARRANTY, express or implied.
   Copyright (C) 2000 Wlodek Bzyl
 */

#ifndef _init_h
#define _init_h
#include "symtab.h"

typedef struct {
  int type; /* type of symbol; either VAR, BLTIN, UNDEF */
  union {
    double val;  /* if VAR */
    double (*ptr)();  /* if BLTIN */
  } u;
} *symrecT;

/* The symbol table created and initialized in |init_table|.
   It is used used in |yylex|. */
extern symtabADT sym_table;

/* This function initializes |sym_table| with builts-ins 
   arithmetic function and constants. 
   It is used in |main|. */
void init_sym_table(void);

#endif
