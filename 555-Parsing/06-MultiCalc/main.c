/* $Source: /home/nls/WEB/zjp/06-MultiCalc/RCS/main.c,v $
   $Date: 2000/01/08 14:53:54 $
   $Revision: 1.1 $

   This file is distributed WITHOUT ANY WARRANTY, express or implied.
   Copyright (C) 2000 Wlodek Bzyl

   This file implements the |main| and |yyeror| functions for
   multi-function calculator.
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
