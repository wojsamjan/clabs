%{
/* $Source: /home/nls/WEB/zjp/09-MultiCalc/RCS/lex.l,v $
   $Date: 2000/01/10 00:53:41 $
   $Revision: 1.1 $

   This file is distributed WITHOUT ANY WARRANTY, express or implied.
   Copyright (C) 2000 Wlodek Bzyl

   This file implements the lexical analyzer for multi-function
   calculator with arbitrary variable names and built-in functions 
   and constants.
 */

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "genlib.h" /* |UNDEFINED| */
#include "init.h"
#include "grammar.h"

%}

%option noyywrap

%%
([0-9]+|[0-9]*\.[0-9]+)  { 
        yylval.val=atof(yytext); return NUMBER; }
[ \t] { /* skip whitespace characters */ }
([a-zA-Z]+) { 
        symrecT s;
        if ((s=lookup(sym_table,yytext))==UNDEFINED) {
          s=New(symrecT);
	  s->type=UNDEF;
	  s->u.val=0.0; /* initialize new variable to 0.0 */
	  enter(sym_table,yytext,s);
        }
        yylval.sym=s;
        /* if |UNDEF| let the parser to check the correct use */
        return s->type==UNDEF ? VAR : s->type; }
.|\n  { return yytext[0]; }
%%
