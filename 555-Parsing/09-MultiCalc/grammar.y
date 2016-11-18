%{/*
   $Source: /home/nls/WEB/zjp/09-MultiCalc/RCS/grammar.y,v $
   $Date: 2000/01/10 00:53:41 $
   $Revision: 1.2 $

   This file is distributed WITHOUT ANY WARRANTY, express or implied.
   Copyright (C) 2000 Wlodek Bzyl

   This file contains the Bison grammar for the multi-function 
   calculator with arbitrary variable names and built-in functions 
   and constants.

   This grammar contains one ``shift/reduce'' conflict 
   which means that the grammar is ambigous. The single line of input
         x = 1
   can be parsed in two ways:
   (*)   input => @ input => exp => asgn => VAR '=' NUMBER
   (+)   input => @ input => asgn => VAR '=' NUMBER.
   The parser can decide that the |asgn| should be reduced to 
   an |exp| and then to a |input| (*), or it can decide to use
   the following |\n| immediately (shift) and convert the whole 
   thing to |input| without the intermediate rule (+).
   Given the ambiguity, bison chooses to shift, which is the
   right decision. 
  */

#include <math.h>
#include "init.h"

%}

%union {
  double val;  /* actual value */
  symrecT sym;  /* symbol table pointer */
}

%token <val> NUMBER
%token <sym> VAR BLTIN UNDEF
%type <val> exp asgn
%right '='
%left '-' '+'
%left '*' '/'
%left UNARYMINUS
%right '^'  /* exponentiation */

%%

input: /* empty */
  | input '\n'
  | input asgn '\n'
  | input exp '\n'     { printf("\t%.10g\n",$2); }
  | input error '\n'   { yyerrok; }
  ;
asgn: VAR '=' exp      { $$=$3; $1->u.val=$3; $1->type=VAR; }
  ;
exp: NUMBER            { $$=$1; }
  | VAR                { if ($1->type==UNDEF) 
                           Error("undefined variable");
                         $$=$1->u.val; }
  | asgn               { $$=$1; }
  | BLTIN '(' exp ')'  { $$=(*($1->u.ptr))($3); }
  | '(' exp ')'        { $$=$2; }
  | exp '+' exp        { $$=$1+$3; }
  | exp '-' exp        { $$=$1-$3; }
  | exp '*' exp        { $$=$1*$3; }
  | exp '/' exp        { $$=$1/$3; }
  | '-' exp %prec UNARYMINUS  {
                         $$=-$2; }
  | exp '^' exp        { $$=pow($1,$3); }
  ;
%%
