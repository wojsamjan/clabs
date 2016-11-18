%{
/* Hopcroft JE, Ullman Jd. 
   Wprowadzenie do teorii automatów.. 
   przyk³ad 4.9, s. 113. 
   L -- napisy sk³adaj±ce siê z jednakowej liczby symboli a i b.
 */

#include <stdio.h>
%}
%%
input: /* pusty */
  | input line
  ;
line: '\n'
  | S '\n' { printf("\tOK!\n"); }
  ;
S: C_b A | C_a B ;
A: C_a S | C_b D_1 | 'a' ;
B: C_b S | C_a D_2 | 'b' ;
D_1: A A ;
D_2: B B ;
C_a: 'a' ;
C_b: 'b' ;
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
