%{
/* $Source: /home/nls/WEB/zjp/11-MultiCalc/RCS/lex.l,v $
   $Date: 2000/01/22 00:12:20 $
   $Revision: 1.4 $

   This file is distributed WITHOUT ANY WARRANTY, express or implied.
   Copyright (C) 2000 Wlodek Bzyl

   This file implements the lexical analyzer for multi-function
   calculator with arbitrary variable names and built-in functions,
   constants, control flow and relational operators.
 */

#include "genlib.h" /* |UNDEFINED| */
#include "init.h" /* |symrecT| */
#include "symtab.h" /* |lookup|, |enter| */
#include "machine.h" /* |machine_instT| for |YYSTYPE| */
#include "grammar.h" /* |NUMBER|, |UNDEF|, |VAR| */

#define install(t,n,v) \
  symrecT s; \
  if ((s=lookup(sym_table,yytext))==UNDEFINED) {\
    s=New(symrecT); \
    s->type=t; \
    s->name=xstrdup(n); \
    s->u.val=v; \
    enter(sym_table,yytext,s); \
  } \
  yylval.sym=s
%}

%option noyywrap

%%
[ \t\n]     { /* skip whitespace characters */ }
"<"       { return LT; }
"<="      { return LE; }
">"       { return GT; }
">="      { return GE; }
"=="      { return EQ; }
"!="      { return NE; }
([0-9]+|[0-9]*\.[0-9]+)  { 
            install(NUMBER,yytext,atof(yytext));
            return NUMBER; }
([a-zA-Z]+)  { 
            install(UNDEF,yytext,0.0);  /* initialize new variable to 0.0 */
            /* if |UNDEF| let the parser to check the correct use */
            return s->type==UNDEF ? VAR : s->type; }
(\"[^\n\"]+\")  {
            yytext[yyleng-1]='\0'; /* remove last `"' */
            yylval.sym=(symrecT) xstrdup(yytext+1);
            return STRING; }
.         { return yytext[0]; }
%%
