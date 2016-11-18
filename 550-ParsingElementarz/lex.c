/*
    $URL: http://manta.univ.gda.pl/svn/wb/labs/c/550-ParsingElementarz/lex.c $
    $Revision: 183 $
    $Date: 2006-11-19 16:29:41 +0100 (nie, 19 lis 2006) $
 */

#include <stdio.h>
#include <ctype.h>

#include "lex.h"


static int layout_char(int ch) {
  switch (ch) {
  case ' ': case '\t': case '\n': return 1;
  default: return 0;
  }
}

tokenT token;

int yylex(void) {
  int ch;
  
  /* get a non-layout character */
  do {
    ch=getchar();
    if (ch==EOF) {
      token.class=EOP;
      token.repr='#';
      return 0;
    }
  } while (layout_char(ch));

  /* classify it */
  if (isdigit(ch)) {
    token.class=DIGIT;
  } else {
    token.class=ch;
  }
  token.repr=ch;

  return ch;
}
