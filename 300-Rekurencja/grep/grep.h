/*
   $Date: 2004/10/08 09:46:08 $
   $Revision: 1.1 $
*/

#ifndef GREP_H_INCLUDED
#define GREP_H_INCLUDED

/* szukanie wyra¿enia `regexp' w napisie `text' */

int match(char *regexp, char *text);

/* szukanie wyra¿enia `regexp' OD pocz±tku napisu `text' */

int matchhere(char *regexp, char *text);

/* szukanie `c*regexp' od pocz±tku napisu `text' */

int matchstar(int c, char *regexp, char *text);

/* szukanie `regexp' w pliku */

int grep(char *regexp, FILE *f, char *name);

#endif
