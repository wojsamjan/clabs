%{
/* Hopcroft JE, Ullman Jd. 
   Wprowadzenie do teorii automatów.. 
   przyk³ad 10.5, s. 285. 
   L -- ³añcuchy zrównowa¿onych nawiasów (gdzie '#' jest znacznikiem koñca).
 */

#include <stdio.h>
%}
%%
input: /* pusty */
  | input line
  ;
line: '\n'
  | S '\n' { printf("\tOK!\n"); }
  | error '\n' { yyerrok; }
  ;
S: S '#' ;
S: S A | A ;
A: 'a' S 'b' | 'a' 'b' ;
%%
int yylex()
{
  int c;
 
  while ((c=getchar())==' ' || c=='\t') ;
  yylval=c;
  if (c==EOF) return(0);
  else return(c);
}
int main()
{
//  yydebug=1;
  yyparse();
}
int yyerror(char *s)
{
  fprintf(stderr, "\t%s\n", s);
}
