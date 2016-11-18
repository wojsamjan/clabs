%{
/* Knuth DE, Translation from Left to Right.. p.~618 (24)
   L -- set of all strings on {a,b} having exactly the 
        same total number of a's and b's (LR(1) grammar)
 */

#include <stdio.h>
%}
%%
line: S '\n' { printf("\tOK!\n"); }
  | error '\n' { yyerrok; }
  ;
S: /* empty */ | 'a' A 'b' S | 'b' B 'a' S ;
A: /* empty */ | 'a' A 'b' A ;
B: /* empty */ | 'b' B 'a' B ;
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
