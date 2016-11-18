%{
/* Knuth DE, Translation from Left to Right.. p.~612 (7)
         n  n
   L -- a bc   (LR(0), fails to be of bounded right context)
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
S: 'a' A 'c' | 'b' ;
A: 'a' S 'c' | 'b' ;
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
