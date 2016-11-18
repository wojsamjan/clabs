/* $Source: /home/nls/WEB/zjp/09-MultiCalc/RCS/main.c,v $
   $Date: 2000/01/10 00:53:41 $
   $Revision: 1.2 $

   This file is distributed WITHOUT ANY WARRANTY, express or implied.
   Copyright (C) 2000 Wlodek Bzyl

   This file implements the |main| and |yyeror| functions for
   multi-function calculator.
 */

#include <stdio.h>
#include "init.h"

int main() {
  init_sym_table();
  yyparse();
  return 0;
}

/* called by |yyparse| on error */

int yyerror(char *s) { 
  printf("! Error: %s\n", s);
}
