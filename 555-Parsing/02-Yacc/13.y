%{
/* Knuth DE, Translation from Left to Right.. p.~609
   L -- string `abcde'
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
S: A D;
A: 'a' C;
B: 'b' 'c' 'd' ;
C: B E ;
D: /* empty */ ;
E: 'e' ;
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
