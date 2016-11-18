/* $Source: /home/nls/WEB/zjp/03-RecDescent/RCS/grammar.h,v $
   $Date: 2000/02/20 18:50:50 $
   $Revision: 1.1 $

   This file is distributed WITHOUT ANY WARRANTY, express or implied.
   Copyright (C) 2000 Wlodek Bzyl

   This file defines types used by parser and scanner for infix
   to postfix translator.
 */

/* The lexical analyzer routine. */
int yylex(void); 

typedef union {
  int num;     /* for returning numbers */
  char *name;  /* for returning variable names */
} YYSTYPE;

#define	NUM	257
#define	VAR     258
#define	DONE    259

extern YYSTYPE yylval;

/* This function parses and translates expression list. */
void parse (void); 

/* This function parses and translates expressions. */
void expr(void);

/* This function parses and translates rest of expressions. */
void rest(void);

/* This function parses and translates terms. */
void term(void);

/* This function parses and translates factor. */
void match(int);

/* This function generates output. */
void emit(int);
