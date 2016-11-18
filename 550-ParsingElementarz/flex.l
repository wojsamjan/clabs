/*  -*- mode: c-mode -*-

    $URL: http://manta.univ.gda.pl/svn/wb/labs/c/550-ParsingElementarz/flex.l $
    $Revision: 183 $
    $Date: 2006-11-19 16:29:41 +0100 (nie, 19 lis 2006) $
 */

%{

/*  C declarations  */

#include <stdio.h>
#include <ctype.h>

#include "lex.h"

tokenT token;

%}

/*  flex definitions  */

digits  [0-9]+

%%

{digits}  { 
     token.class = DIGIT; 
     token.repr = yytext[0];
     return DIGIT;
}

"+"|"*"|"("|")"  { 
     token.class = yytext[0];
     token.repr = yytext[0];
     return yytext[0];
}

<<EOF>> {
     token.class = EOP;
     token.repr = '#';
     return EOP;
}

.   printf( "Unrecognized character: [%s]\n", yytext );  /* skip other characters */

%%
