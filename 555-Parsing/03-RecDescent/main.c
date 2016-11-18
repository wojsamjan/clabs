/* $Source: /home/nls/WEB/zjp/03-RecDescent/RCS/main.c,v $
   $Date: 2000/02/20 18:55:29 $
   $Revision: 1.1 $

   This file is distributed WITHOUT ANY WARRANTY, express or implied.
   Copyright (C) 2000 Wlodek Bzyl

   Infix to postfix translator for a language consisting of sequences
   of expressions terminated by semicolons.
 */
#include <stdio.h>
#include "common.h"

int main() {
  parse();
  return 0;
}

/* called by |yyparse| on error */

int error(char *s) { 
  fprintf(stderr,"! Error: %s\n", s);
}
