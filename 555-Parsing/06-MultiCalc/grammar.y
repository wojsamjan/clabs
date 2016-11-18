%{/* 
   $Source: /home/nls/WEB/zjp/06-MultiCalc/RCS/grammar.y,v $
   $Date: 2000/01/21 11:34:35 $
   $Revision: 1.1 $

   This file is distributed WITHOUT ANY WARRANTY, express or implied.
   Copyright (C) 2000 Wlodek Bzyl

   This file contains the Bison grammar for the multi-function 
   calculator.
  */
#include <stdio.h>
#include <math.h> /* |pow| */
#define YYSTYPE double
%}

%token NUM

%%
input: /* empty */
  | input line
  ;
line: '\n'
  | exp '\n'     { printf("\t%.10g\n",$1); }
  ;
exp: NUM         { $$=$1; }
  | exp exp '+'  { $$=$1+$2; }
  | exp exp '-'  { $$=$1-$2; }
  | exp exp '*'  { $$=$1*$2; }
  | exp exp '/'  { $$=$1/$2; }
  | exp exp '^'  { $$=pow($1,$2); }
  | exp     'n'  { $$=-$1; }
  ;
%%
