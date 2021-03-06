/* ----------------------------------------------------------
   $Source: /home/nls/WEB/mfcalc/RCS/init.c,v $
   $Date: 2000/01/02 12:23:03 $
   $Revision: 1.4 $
   ----------------------------------------------------------
   This Makefile belongs to the MFCALC package.
   It is distributed WITHOUT ANY WARRANTY, express or implied.
   Copyright (C) 2000 Wlodek Bzyl
   ----------------------------------------------------------
   Initialization of symbol table with built-ins and constants.
 */

#include <math.h>
#include "symtab.h"
#include "common.h" /* |symrecT| */
#include "mfcalc.h" /* |YYSTYPE|, |yylval|, tokens */

struct init {
  char *fname;
  double (*fnct)();
};

struct init arith_fncts[]={
  { "sin", sin }, { "cos", cos }, { "atan", atan }, 
  { "ln", log }, { "exp", exp }, { "sqrt", sqrt }, 
  { 0, 0 }
};

/* Public entries */

symtabADT sym_table; /* main symbol table */

void init_sym_table(void) {
  int i;
  sym_table=new_symbol_table();
  for (i=0; arith_fncts[i].fname!=0; i++) {
    symrecT entry=New(symrecT);
    entry->type=FNCT;
    entry->value.fnctptr=arith_fncts[i].fnct;
    enter(sym_table,arith_fncts[i].fname,entry);
  }
}
