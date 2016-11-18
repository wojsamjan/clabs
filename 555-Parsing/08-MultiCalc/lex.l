%{
/* $Source: /home/nls/WEB/zjp/08-MultiCalc/RCS/lex.l,v $
   $Date: 2000/01/10 00:58:08 $
   $Revision: 1.2 $

   This file is distributed WITHOUT ANY WARRANTY, express or implied.
   Copyright (C) 2000 Wlodek Bzyl

   This file implements the lexical analyzer for multi-function
   calculator with arbitrary variable names and built-in functions 
   and constants.
 */

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "genlib.h"
#include "init.h"
#include "grammar.h"

%}

%option noyywrap

%%
([0-9]+|[0-9]*\.[0-9]+)  { 
        yylval.val=atof(yytext); return NUM; }
[ \t] { /* skip whitespace characters */ }
([a-zA-Z]+) { 
        symrecT s;
        s=lookup(sym_table,yytext);
        if (s==UNDEFINED) {
          s=New(symrecT);
	  s->type=VAR;
	  s->value.var=0.0; /* initialize new variable to 0.0 */
	  enter(sym_table,yytext,s);
        }
        yylval.tptr=s;
        return s->type; }
.|\n  { return yytext[0]; }
%%
