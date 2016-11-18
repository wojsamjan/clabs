%{
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
int yyerror(char *s)
{
  fprintf(stderr, "%s\n", s);
}
int main()
{
  yyparse();
}
