%{
#include <stdio.h>
#include <ctype.h>
%}
%%
line: start '\n' { printf("\tOK!\n"); }
  | error '\n' { printf("\tBAD!\n"); } ;
start: x 
  | y 'R' ;
x: 'A' 'R' ;
y: 'A' ;
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
