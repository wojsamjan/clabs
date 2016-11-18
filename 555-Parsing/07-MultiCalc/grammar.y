%{/* 
   $Source: /home/nls/WEB/zjp/07-MultiCalc/RCS/grammar.y,v $
   $Date: 2000/01/21 11:34:46 $
   $Revision: 1.2 $

   It is distributed WITHOUT ANY WARRANTY, express or implied.
   Copyright (C) 2000 Wlodek Bzyl

   This file contains the Bison grammar for the multi-function 
   calculator with one-letter variables.
  */
#include <stdio.h>
double vtable[26];
%}

%union {
  double val;
  int var;
}
%token <var> NAME
%token <val> NUMBER
%left '-' '+'
%left '*' '/'
%nonassoc UMINUS
%type <val> exp
%%
input: /* pusty */
  | input line
  ;
line: NAME '=' exp '\n' { vtable[$1]=$3; }
  | exp '\n'            { printf("\t%.10f\n",$1); }
  ;
exp: NUMBER      { $$=$1; }
  | NAME         { $$=vtable[$1]; }
  | exp '+' exp  { $$=$1+$3; }
  | exp '-' exp  { $$=$1-$3; }
  | exp '*' exp  { $$=$1*$3; }
  | exp '/' exp  { $$=$1/$3; }
  | '-' exp %prec UMINUS { $$=-$2; }
  | '(' exp ')'  { $$=$2; }
  ;
%%
