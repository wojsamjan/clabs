/* ----------------------------------------------------------
   $Source: /home/nls/WEB/mfcalc/RCS/common.h,v $
   $Date: 2000/01/02 13:55:40 $
   $Revision: 1.1 $
   ----------------------------------------------------------
   This Makefile belongs to the MFCALC package.
   It is distributed WITHOUT ANY WARRANTY, express or implied.
   Copyright (C) 2000 Wlodek Bzyl
   ----------------------------------------------------------
   This file contains declarations common for:
     mfcalc.y, lex.c, init.c
 */

#ifndef _common_h
#define _common_h
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

/* This function initializes the input variables and fills the
   buffer. */
void init_input(void);

#endif
