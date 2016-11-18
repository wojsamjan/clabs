%{
/* $Source: /home/nls/WEB/mfcalc/MFCALC3/RCS/lex.l,v $
   $Date: 2000/01/04 20:35:46 $
   $Revision: 1.1 $

   This file is distributed WITHOUT ANY WARRANTY, express or implied.
   Copyright (C) 2000 Wlodek Bzyl

   This file implements the lexical analyzer for multi-function 
   calculator with one-letter variables.
 */
#include <stdlib.h>
#include "grammar.h"
extern double vtable[26];
%}

%option noyywrap

%%
([0-9]+|[0-9]*\.[0-9]+)  { yylval.val=atof(yytext); return NUMBER; }
[ \t]                    { /* skip whitespace characters */ }
[a-z]                    { yylval.var=yytext[0]-'a'; return NAME; }
.|\n                     { return yytext[0]; }
%%
