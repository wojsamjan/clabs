/* $Source: /home/nls/WEB/zjp/07-MultiCalc/RCS/main.c,v $
   $Date: 2000/01/08 14:57:42 $
   $Revision: 1.2 $

   This file is distributed WITHOUT ANY WARRANTY, express or implied.
   Copyright (C) 2000 Wlodek Bzyl

   This file implements the |main| and |yyeror| functions for
   multi-function calculator with one-letter variables.
 */

#include <stdio.h>

int main()
{
  yyparse();
}

int yyerror(char *s)
{
  fprintf(stderr, "%s\n", s);
}
