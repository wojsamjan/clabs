/* $Source: /home/nls/WEB/zjp/11-MultiCalc/RCS/init.h,v $
   $Date: 2000/01/10 22:10:49 $
   $Revision: 1.1 $

   This file is distributed WITHOUT ANY WARRANTY, express or implied.
   Copyright (C) 2000 Wlodek Bzyl

   An intermediate step for an simple "stack machine".
 */

#ifndef _init_h
#define _init_h
#include "symtab.h"
#include "machine.h"

typedef struct {
  int type; /* type of symbol; either VAR, BLTIN, UNDEF, PROC */
  char *name; /* symbol name */
  union {
    double val;  /* if VAR */
    double (*ptr)();  /* if BLTIN */
    machine_instT *procpointer; /* wska¼nik do programu procedury je¿eli PROC */
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
