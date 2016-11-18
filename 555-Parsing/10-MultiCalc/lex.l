%{
/* $Source: /home/nls/WEB/zjp/10-MultiCalc/RCS/lex.l,v $
   $Date: 2000/01/10 00:30:32 $
   $Revision: 1.4 $

   This file is distributed WITHOUT ANY WARRANTY, express or implied.
   Copyright (C) 2000 Wlodek Bzyl

   This file implements the lexical analyzer for multi-function
   calculator with arbitrary variable names and built-in functions 
   and constants.
   With this version, numbers are installed in the symbol table along
   with the variable names.
 */

#include "genlib.h" /* |UNDEFINED| */
#include "init.h" /* |symrecT| */
#include "symtab.h" /* |lookup|, |enter| */
#include "machine.h" /* |machine_instT| for |YYSTYPE| */
#include "grammar.h" /* |NUMBER|, |UNDEF|, |VAR| */

#define install(t,n,v) \
  if ((s=lookup(sym_table,yytext))==UNDEFINED) {\
    s=New(symrecT); \
    s->type=t; \
    s->name=xstrdup(n); \
    s->u.val=v; \
    enter(sym_table,yytext,s); \
  }

%}

%option noyywrap

%%
([0-9]+|[0-9]*\.[0-9]+)  { 
        symrecT s; 
        install(NUMBER,yytext,atof(yytext));
        yylval.sym=s;
        return NUMBER; }
[ \t] { /* skip whitespace characters */ }
([a-zA-Z]+) { 
        symrecT s;
        install(UNDEF,yytext,0.0);  /* initialize new variable to 0.0 */
        yylval.sym=s;
        /* if |UNDEF| let the parser to check the correct use */
        return s->type==UNDEF ? VAR : s->type; }
.|\n  { return yytext[0]; }
%%
