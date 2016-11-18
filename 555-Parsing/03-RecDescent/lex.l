%{
/* $Source: /home/nls/WEB/zjp/03-RecDescent/RCS/lex.l,v $
   $Date: 2000/02/20 18:55:29 $
   $Revision: 1.1 $

   This file is distributed WITHOUT ANY WARRANTY, express or implied.
   Copyright (C) 2000 Wlodek Bzyl

   This file implements the lexical analyzer for infix to postfix
   translator.
 
   The lexical analyzer routine is called |yylex| that is called
   by the parser to find tokens. 
 */
#include <stdio.h>
#include <string.h>    /* |strdup| */
#include <stdlib.h>    /* |atof| */
#include "common.h"
#include "genlib.h"
%}
%option noyywrap

%%
[ \t\n]     { /* skip whitespace characters */ }
([0-9]+)    { yylval.num=atoi(yytext); 
              return NUM; }
([a-zA-Z]+) { if ((yylval.name=strdup(yytext))==NULL) 
                Error("insufficient memory");
              return VAR; }
.           { return yytext[0]; }
<<EOF>>     { return DONE; }
%%
