/*
    $URL: http://manta.univ.gda.pl/svn/wb/labs/c/550-ParsingElementarz/lex.h $
    $Revision: 183 $
    $Date: 2006-11-19 16:29:41 +0100 (nie, 19 lis 2006) $
 */

#ifndef lex_included
#define lex_included

/* Define class constants: */

/* values 0--255 are reserved for ASCII characters */
#define  EOP    256
#define  DIGIT  257

typedef struct {
  int class;
  char repr;
} tokenT;

extern tokenT token;  /* global variable */

int yylex(void);

#endif

