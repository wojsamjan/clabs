%{
/* Knuth DE, Translation from Left to Right.. p.~612 (6)
          2n+1
   L -- ab    c   (not LR(k)) for any k)
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
S: 'a' A 'c' ;
A: 'b' A 'b' | 'b' ;
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
