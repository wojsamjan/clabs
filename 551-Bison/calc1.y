%{
  /*  $URL: http://manta.univ.gda.pl/svn/wb/labs/c/551-Bison/calc1.y $
      $Revision: 89 $
   */

#include <stdio.h>
#include <ctype.h>

void yyerror (char const *s);
%}

%union { int num ; }

%token <num> LICZBA
%type  <num> wyr

%left '+'
%left '*'

%%
wiersze :  wiersze wyr '\n'  { printf("\twynik: %d\n",$2); }
        |  wiersze '\n'
        |  /* epsilon */ 
        ;
wyr     :  wyr '+' wyr  { $$ = $1 + $3; }
        |  wyr '*' wyr  { $$ = $1 * $3; } 
        |  '(' wyr ')'  { $$ = $2; } 
        |  LICZBA       /* domy¶lna akcja $$ = $1 */
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
