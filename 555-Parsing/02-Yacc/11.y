%{
/* Hopcroft JE, Ullman Jd. 
   Wprowadzenie do teorii automatów.. 
   Automaty ze stosem,  s. 127. 
           R
   L -- w2w, gdzie w napis (0|1)* 
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
S: '2' | '0' S '0' | '1' S '1' ;
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
