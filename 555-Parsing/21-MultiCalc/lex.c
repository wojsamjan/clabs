/* ----------------------------------------------------------
   $Source: /home/nls/WEB/mfcalc/RCS/lex.c,v $
   $Date: 2000/01/03 18:48:09 $
   $Revision: 1.6 $
   ----------------------------------------------------------
   This Makefile belongs to the MFCALC package.
   It is distributed WITHOUT ANY WARRANTY, express or implied.
   Copyright (C) 2000 Wlodek Bzyl
   ----------------------------------------------------------
   This file implements lexical analyzer for multi-function 
   calculator `mfcalc'.
 */

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "genlib.h" /* |repeat| */
#include "input.h"
#include "common.h" /* |symrecT|, |sym_table| */
#include "mfcalc.h" /* |YYSTYPE|, |yylval|, tokens */

/* |MAXTOKEN| aplies to all tokens except identifiers, and
   string literals, and numeric constants; occurrences of these
   tokens that are longer than |MAXTOKEN| are handled explictly
   in the code for those tokens. */
#define MAXTOKEN 32

int yylex(void) {
  repeat {
    /* Get the first nonwhite character and ensure that the whole 
       next token is in the buffer */
    while (*cp==' ' || *cp=='\t') cp++;
    if (limit-cp<MAXTOKEN) fill_buffer();

    /* Now find the next token. */

    /* ID token */
    if (isalpha(*cp)) {
      char *token=(char *)cp; /* remember where the token begins */
      unsigned char nchar; /* the first character after ID token */
      symrecT s;
      /* ensure that there are at least |MAXLINE| characters */
      if (limit-cp<MAXLINE) fill_buffer();
      token=(char *)cp;
      while (isalnum(*cp) || *cp=='_') cp++;
      nchar=*cp;
      *cp='\0';
      s=lookup(sym_table,token);
      if (s==UNDEFINED) {
	s=New(symrecT);
	s->type=VAR;
	s->value.var=0.0; /* initialize new variable to 0.0 */
	enter(sym_table,token,s);
      }
      //      printf("[v:%s]",token);
      *cp=nchar;
      yylval.tptr=s;
      return s->type;
    }
    /* NUM token */
    if (isdigit(*cp)) {
      char *endnum;
      /* ensure that there are at least |MAXLINE| characters */
      if (limit-cp<MAXLINE) fill_buffer();
      yylval.val=strtod((char *)cp,&endnum);
      /* move |cp| over the number */
      if (endnum!=(char *)cp) cp=(unsigned char *)endnum;
      //      printf("[n:%g]",yylval.val);
      return NUM;
    }
    switch (*cp) {
    case '\n': case '\v': case '\r': case '\f':
      /* skip over a newline or one of its synonyms */
      next_line();
      /* return, if end of input */
      if (cp==limit) return 0;
      /* move to the next character and return */
      //      printf("[nl]");
      return *cp++; 
      break;
    default: /* any other character is a token by itself */
      /* move to the next character and return */
      //      printf("[s:%c]",*cp);
      return *cp++;
    }
  }
}
