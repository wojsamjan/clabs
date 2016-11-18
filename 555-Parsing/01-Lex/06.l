%{
/* W³odek Bzyl <matwb@univ.gda.pl>,       28 lutego 1999.
 ********************************************************
 * Analizator programów napisanych w C.
 * Program zlicza wiersze kodu, komentarzy i odstêpu.
 * Uwaga:
 * Wprowadzamy stan pocz±tkowy `IN_COMMENT' aby unikn±æ
 * przepe³nienia wewnêtrznego bufora w trakcie 
 * czytania d³ugiego komentarza.
 */

#include <stdio.h>

int comments = 0, code = 0, whitespace = 0, total;
int line_num = 1;

//#define debug(s) printf("[%s:%d]", s, line_num) 
#define debug(s)
%}

%x IN_COMMENT
%option noyywrap

WS   [ \t]*
BC   "/*"  
EC   "*/"
IC   {BC}.*{EC}

%%

^{WS}\n   { whitespace++; line_num++; }
^{WS}{BC} { BEGIN(IN_COMMENT); debug("W"); }

<IN_COMMENT>{
  {EC}{WS}\n  { BEGIN(INITIAL); comments++; 
	        debug("I1"); }
  {EC}        { BEGIN(INITIAL); 
	        debug("I2"); }
  \n          { comments++; line_num++; 
	        debug("I3"); }
  .           { debug("I4"); }
}

.+{IC}.*\n        { code++; line_num++; }
.*{IC}.+{BC}.*\n  { code++; line_num++; BEGIN(IN_COMMENT);} 
.*{IC}.+\n        { code++; line_num++; 
                    debug("3"); } 
.+{BC}.*\n        { code++; line_num++; BEGIN(IN_COMMENT); }
.                 { /* skip other character */ }
\n                { code++; line_num++; }

%%

int 
main()
{
  yylex();
  total = code + comments + whitespace;
  printf("
  Liczba wierszy  
  ---------------
  kodu:       %3d
  komentarzy: %3d
  odstêpu:    %3d
  ---------------
  razem:      %3d\n", code, comments, whitespace, total);
}
