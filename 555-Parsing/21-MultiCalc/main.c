/* ----------------------------------------------------------
   $Source: /home/nls/WEB/mfcalc/RCS/main.c,v $
   $Date: 2000/01/02 14:14:45 $
   $Revision: 1.3 $
   ----------------------------------------------------------
   This Makefile belongs to the MFCALC package.
   It is distributed WITHOUT ANY WARRANTY, express or implied.
   Copyright (C) 2000 Wlodek Bzyl
   ----------------------------------------------------------
   This file implements the |main| and |yyeror| functions for
   multi-function calculator `mfcalc'.
 */

#include <stdio.h>
#include "genlib.h" /* |string| */
#include "common.h"

int main() {
  init_input();
  init_sym_table();
  yyparse();
  return 0;
}

/* called by |yyparse| on error */

int yyerror(string s) { 
  printf("! Error: %s\n", s);
}
