%{
/* $Source: /home/nls/WEB/zjp/08-MultiCalc/RCS/grammar.y,v $
   $Date: 2000/01/10 00:58:08 $
   $Revision: 1.3 $

   This file is distributed WITHOUT ANY WARRANTY, express or implied.
   Copyright (C) 2000 Wlodek Bzyl

   This file contains the Bison grammar for the multi-function 
   calculator with arbitrary variable names and built-in functions 
   and constants.
 */

#include <math.h>  /* |pow| */
#include "init.h"  /* |symrecT| */ 

%}

%union {
  double val;  /* For returning numbers. */
  symrecT tptr;  /* For returning symbol-table pointers. */
}

%token <val> NUM  /* Simple double precision number */
%token <tptr> VAR FNCT  /* Variable and Function */
%type <val> exp
%right '='
%left '-' '+'
%left '*' '/'
%left NEG  /* Negation--unary minus */
%right '^'  /* Exponentiation */

%%

input: /* empty */
  | input line
  ;
line: '\n'
  | exp '\n'   { printf("\t%.10g\n",$1); }
  | error '\n' {  yyerrok; }
  ;
exp: NUM               { $$=$1; }
  | VAR                { $$=$1->value.var; }
  | VAR '=' exp        { $$=$3; $1->value.var=$3; }
  | FNCT '(' exp ')'   { $$=(*($1->value.fnctptr))($3); }
  | '(' exp ')'        { $$=$2; }
  | exp '+' exp        { $$=$1+$3; }
  | exp '-' exp        { $$=$1-$3; }
  | exp '*' exp        { $$=$1*$3; }
  | exp '/' exp        { $$=$1/$3; }
  | '-' exp %prec NEG  { $$=-$2; }
  | exp '^' exp        { $$=pow($1,$3); }
  ;
%%
