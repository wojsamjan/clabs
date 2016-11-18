/* $Source: /home/nls/WEB/zjp/08-MultiCalc/RCS/init.h,v $
   $Date: 2000/01/10 00:58:08 $
   $Revision: 1.1 $

   This file is distributed WITHOUT ANY WARRANTY, express or implied.
   Copyright (C) 2000 Wlodek Bzyl

   This file contains declarations common for: mfcalc.y, lex.c, init.c
 */

#ifndef _init_h
#define _init_h
#include "symtab.h"

typedef struct {
  int type; /* type of symbol; either VAR or FNCT */
  union {
    double var;  /* value of VAR */
    double (*fnctptr)();  /* value of FNCT */
  } value;
} *symrecT;

/* The symbol table created and initialized in |init_table| and
   used by |yylex|. */
extern symtabADT sym_table;

/* This function initializes |sym_table| with builts-ins arithmetic
   function and constants. */
void init_sym_table(void);

#endif
