%{
#include <stdio.h>
#include <math.h>
#define YYSTYPE double
%}
%token NUM
%%
input:
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
#include <ctype.h>

int yylex()
{
  int c;

  while((c=getchar())==' ' || c=='\t')
    ;
  if (c=='.' || isdigit(c)) {
    ungetc(c,stdin);
    scanf("%lf",&yylval);
    return NUM;
  }
  if (c==EOF) return(0);
  return(c);
}

int yyerror(char *s)
{
  fprintf(stderr, "%s\n", s);
}

int main()
{
  yyparse();
}
