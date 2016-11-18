%{
  /*  $URL: http://manta.univ.gda.pl/svn/wb/labs/c/551-Bison/calc0.y $
      $Revision: 89 $
   */

#include <stdio.h>
#include <ctype.h>

void yyerror (char const *s);
%}

%union { int num ; }

%token <num> LICZBA
%type  <num> E
%type  <num> T
%type  <num> F

%%
S :  E '\n'     { printf("\twynik: %d\n", $1); }
  ;

E :  E '+' T    { $$ = $1 + $3; }
  |  T     
  ;
T :  T '*' F    { $$ = $1 * $3; }
  |  F     
  ;
F :  '(' E ')'  { $$ = $2; } 
  |  LICZBA
  ;
%%

int yylex(void) {
  int c;
  while ((c=getchar())==' ')
    ;
  if (isdigit(c)) {
    ungetc(c,stdin);
    scanf("%d",&yylval);
    return LICZBA;
  }
  return c;
}

void yyerror (char const *s) {
  fprintf (stderr, "%s\n", s);
}

int main() {
  return yyparse();
}
