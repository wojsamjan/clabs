/* $Source: /home/nls/WEB/zjp/10-MultiCalc/RCS/init.h,v $
   $Date: 2000/01/10 00:05:33 $
   $Revision: 1.1 $

   This file is distributed WITHOUT ANY WARRANTY, express or implied.
   Copyright (C) 2000 Wlodek Bzyl

   An intermediate step for an simple "stack machine".
 */

#ifndef _init_h
#define _init_h
#include "symtab.h"

typedef struct {
  int type; /* type of symbol; either VAR, BLTIN, UNDEF */
  char *name; /* symbol name */
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
