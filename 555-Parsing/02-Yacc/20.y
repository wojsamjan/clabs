%{
#include <stdio.h>
#include <ctype.h>
%}
%%
line: start '\n' { printf("\tOK!\n"); }
  | error '\n' { printf("\tBAD!\n"); } ;
start: 'A' 'B' x 'Z'
  | y 'Z' ;
x: 'C' ;
y: 'A' 'B' 'C' ;
%%
int yylex()
{
  int c;
 
  while ((c=getchar())==' ' || c=='\t') ;
  yylval=c;
  if (c==EOF) return(0);
  else return(c);
}

int yyerror(char *s)
{
  fprintf(stderr, "%s\n", s);
}

int main()
{
  yyparse();
}
