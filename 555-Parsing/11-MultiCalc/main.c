/* $Source: /home/nls/WEB/zjp/11-MultiCalc/RCS/main.c,v $
   $Date: 2000/01/21 16:09:55 $
   $Revision: 1.3 $

   This file is distributed WITHOUT ANY WARRANTY, express or implied.
   Copyright (C) 2000 Wlodek Bzyl

   The multi-functions calculator presented here is a reworking
   of high order calculator `hoc' described in the book
     BW Kernighan, R Pike, The UNIX Programming Environment,
     Prentice Hall 1984 (ISBN 0-13-937681-X)
   Parts of the context free grammar used here were taken from
     BW Kernighan, DM Ritchie, Jezyk ANSI C, Dodatek A13, WNT 1994.

   This file implements the |main| and |yyeror| functions for
   multi-function calculator.
   The |main| function was changed with respect to earlier versions.
   The parser now returns after |exec| keyword; white space characters
   (including newline) are skipped. 
   The code that is generated is executed. 
   Note that the function |yyparse| returns zero at the end of file.

   TODO list:
   1. Debugger: pokazywanie zawartosci tablic |program| i |stack|;
      nowe instrukcje |debug_program| i |debug_stack| do umieszczania
      w akcjach, np. code(debug_program) powinien spowodowac
      wyswietlenie aktualnej zawartosci tablicy |program|.
   2. Wyswietlanie napisow tak jak to robi C printf:
      print "witaj swiecie\n" powinno wpisac napis oraz znak 
      nowego wiersza.
   3. Liczby zespolone (w notacji a+bi; ewentualnie <a,b>).
   4. Wektory (R^2 / R^3 / R^n).
   5. Procedury: przekazywanie parametrow tak jak w powloce przez
      zmienne specjalne $1, $2, ...
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
