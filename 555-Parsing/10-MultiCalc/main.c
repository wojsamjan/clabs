/* $Source: /home/nls/WEB/zjp/10-MultiCalc/RCS/main.c,v $
   $Date: 2000/01/10 00:30:32 $
   $Revision: 1.3 $

   This file is distributed WITHOUT ANY WARRANTY, express or implied.
   Copyright (C) 2000 Wlodek Bzyl

   The multi-functions calculator presented here is a reworking
   of high order calculator `hoc' described in the book
     BW Kernighan, R Pike, The UNIX Programming Environment,
     Prentice Hall 1984 (ISBN 0-13-937681-X)
   and the context free C grammar presented in
     BW Kernighan, DM Ritchie, Jezyk ANSI C, WNT 1994.

   This file implements the |main| and |yyeror| functions for
   multi-function calculator.
   The |main| function was changed with respect to earlier versions.
   The parser now returns after each statement or expression; the
   code that is generated is executed. The function |yyparse|
   returns zero at the end of file.
 */

#include <stdio.h>
#include "init.h"
#include "machine.h"

int main() {
  init_sym_table();
  for (init_code(); yyparse(); init_code())
    execute(program);
  return 0;
}

/* called by |yyparse| on error */

int yyerror(char *s) { 
  printf("! Error: %s\n", s);
}
