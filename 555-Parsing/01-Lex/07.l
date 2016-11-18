%{
/* W³odek Bzyl <matwb@univ.gda.pl>,       28 lutego 1999.
 ********************************************************
 * Multiple input buffers
 * Przyk³ad ze strony podrêcznika programu FLEX.
 */

#include <stdio.h>
#include <unistd.h>

#define MAX_INCLUDE_DEPTH 10

YY_BUFFER_STATE include_stack[MAX_INCLUDE_DEPTH];
int include_stack_ptr = 0;

%}

%x INCLUDE
%option noyywrap

%%

^[ \t]*#input  { BEGIN(INCLUDE); }
[a-z]+           { ECHO; }
[^a-z\n]*\n?     { ECHO; }

<INCLUDE>{
  [  \t]*      /* eat the whitespace */
  [^ \t\n]+  { /* got the include file name */
     if (include_stack_ptr>=MAX_INCLUDE_DEPTH) {
       fprintf(stderr, "! Includes nested to deeply\n");
       exit(1);
     }
     include_stack[include_stack_ptr++]=YY_CURRENT_BUFFER;
     yyin = fopen(yytext, "r");
     if (yyin==NULL) {
       fprintf(stderr, "! Cannot open %s\n", yytext);
       exit(1);
     }
     yy_switch_to_buffer(yy_create_buffer(yyin,YY_BUF_SIZE));
     BEGIN(INITIAL);
  }
}
<<EOF>>  {
  if (--include_stack_ptr<0) {
    yyterminate();
  }
  else {
    yy_delete_buffer(YY_CURRENT_BUFFER);
    yy_switch_to_buffer(include_stack[include_stack_ptr]);
  }
}
%%

int 
main()
{
  yylex();
}
