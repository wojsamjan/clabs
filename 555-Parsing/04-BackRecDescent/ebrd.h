/* $Source: /home/nls/WEB/mfcalc/MFCALC2/RCS/lex.c,v $
   $Date: 2000/01/04 20:08:53 $
   $Revision: 1.1 $

   It is distributed WITHOUT ANY WARRANTY, express or implied.
   Copyright (C) 2000 Wlodek Bzyl
 */

/* Size of the input buffer */
#define infinity 512+1

/* The input buffer. */
char text[infinity];

/* Index in |text| */
char *tp;

/* This type defines the class of functions that are used to
   parse the grammars. */
typedef void (*parseFnT)(void);

/* Symbolic numbering of rules in the grammar. */
typedef enum { S1, S2, A1, A2, B1, B2, D1, D2, C1, C2 } ruleT;

/* Recognize and report success. */
void endmark(void);

/* Recognize 'a' ('b', 'c') and call |tail|. */
void a(parseFnT tail);
void b(parseFnT tail);
void c(parseFnT tail);


