/* $Source: /home/nls/WEB/zjp/03-RecDescent/RCS/grammar.c,v $
   $Date: 2000/02/20 19:06:49 $
   $Revision: 1.2 $

   This file is distributed WITHOUT ANY WARRANTY, express or implied.
   Copyright (C) 2000 Wlodek Bzyl

   This file contains the recursive descent predicitve parser
   for a infix to postfix translator of simple expresions.

   A grammar for simple expressions consists of following productions:
   
       parse: list EOF
        list: expr ';' list | @
        expr: expr '+' term { print '+' }
            | expr '-' term { print '-' }
            | term
        term: NUM { print NUM } 
            | VAR { print VAR }

   Above grammar could not be used as is. It has to be modified before
   it can be parsed with a predictive parser. In particular, this
   grammar is left recursive and a predicitve parser cannot handle a
   left recursive grammar. By eliminating the left recursion, we can
   obtain a grammar suitable for use in a predictive recursive descent
   translator. Left recursive production of shape:
       A: Aa | Bb | c
   are transformed into
       A: cR
       R: aR | bR | @
   and semantic actions embedded in the productions are carried along
   in the transformation. This transformation when applied to the
   grammar above yields:
 
       parse: list EOF
        list: expr ';' list | @
        expr: term rest
        rest: '+' term { print '+' } rest
            | '-' term { print '-' } rest
            | @
        term: VAR { print VAR } 
            | NUM { print NUM }

  This grammar is used below when building a recursive descent parser.
 */
#include "common.h"

YYSTYPE yylval; /* value of token is stored there */
int lookahead;  /* lookahead token is stored in this variable */

void parse (void) {
  lookahead=yylex();
  while (lookahead!=DONE) {
    expr(); match(';'); printf("\n");
  }
}

void expr(void) {
  term(); rest();
}

void rest(void) {
  int t=lookahead;
  if (t=='+' || t=='-') {
    match(t); term(); emit(t); rest();
  } else ;
}

void term(void) {
  int t=lookahead;
  if (t==NUM || t==VAR) {
    emit(t); match(t);
  } else Error("syntax error");
}

void match(int t) {
  if (lookahead==t) lookahead=yylex();
  else Error("syntax error");
}

void emit(int t) {
  switch(t) {
    case '+': case '-':  printf("%c ",t); break;
    case VAR:  printf("%s ",yylval.name); break;
    case NUM:  printf("%d ",yylval.num); break;
    default:  Error("unrecognized token");
  }
}
