%{/*
   $Source: /home/nls/WEB/zjp/10-MultiCalc/RCS/grammar.y,v $
   $Date: 2000/01/10 00:30:32 $
   $Revision: 1.6 $

   This file is distributed WITHOUT ANY WARRANTY, express or implied.
   Copyright (C) 2000 Wlodek Bzyl

   Intermediate step for an simple "stack machine".
   The grammar is the same as for `mfcalc' version 09, but the actions 
   are different. Each action generates machine instructions and any
   arguments that go with them.
   For example, to handle an assigments
      x = 2 * y
   the following code is generated:
      constpush      push a constant onto stack
        2              the constant 2
      varpush        push symbol table pointer onto stack
        y              for the variable y
      eval           evaluate: replace pointer by value
      mul            multiply top two items; product replaces them
      varpush        push symbol table pointer onto stack
        x              for the variable y
      assign         store top value from stack
      display        pop top value from stack and print it
      stop           end of instruction sequence.
   For descripton of other operands an operators see `machine.h'
  */
#include "init.h"
#include "machine.h"
%}

%union {
  symrecT sym;  /* symbol table pointer */
  machine_instT *inst;  /* machine instruction; not used in this version */
}

%token <sym> NUMBER VAR BLTIN UNDEF
%right '='
%left '-' '+'
%left '*' '/'
%left UNARYMINUS
%right '^'  /* exponentiation */

%%

input: /* empty */
  | input '\n'
  | input asgn '\n'    { code2(display, stop); return 1; } 
  | input exp '\n'     { code2(display, stop); return 1; }
  | input error '\n'   { yyerrok; }
  ;
asgn: VAR '=' exp      { code3(varpush, (machine_instT)$1, assign); }
  ;
exp: NUMBER            { code2(constpush, (machine_instT)$1); }
  | VAR                { code3(varpush, (machine_instT)$1, eval); }
  | asgn               
  | BLTIN '(' exp ')'  { code2(bltin, (machine_instT)$1); }
  | '(' exp ')'        
  | exp '+' exp        { code(add); }
  | exp '-' exp        { code(sub); }
  | exp '*' exp        { code(mul); }
  | exp '/' exp        { code(divide); }
  | '-' exp %prec UNARYMINUS  {
                         code(negate); }
  | exp '^' exp        { code(power); }
%%
