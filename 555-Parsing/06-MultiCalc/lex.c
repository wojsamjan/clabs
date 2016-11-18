/* $Source: /home/nls/WEB/zjp/06-MultiCalc/RCS/lex.c,v $
   $Date: 2000/01/08 14:53:54 $
   $Revision: 1.1 $

   This file is distributed WITHOUT ANY WARRANTY, express or implied.
   Copyright (C) 2000 Wlodek Bzyl

   This file implements lexical analyzer for multi-function calculator.
 */

#include <stdio.h>
#include <ctype.h>
#include "grammar.h"

int yylex()
{
  int c;

  while((c=getchar())==' ' || c=='\t')
    ;
  if (c=='.' || isdigit(c)) {
    ungetc(c,stdin);
    scanf("%lf",&yylval);
    return NUM;
  }
  if (c==EOF) return(0);
  return(c);
}
