/* ----------------------------------------------------------
   $Source: /home/nls/WEB/mfcalc/RCS/input.c,v $
   $Date: 2000/01/03 18:48:16 $
   $Revision: 1.1 $
   ----------------------------------------------------------
   This Makefile belongs to the MFCALC package.
   It is distributed WITHOUT ANY WARRANTY, express or implied.
   Copyright (C) 2000 Wlodek Bzyl
   ----------------------------------------------------------
   This module is tightly coupled with lex.c module.
 */

#include "genlib.h"
#include "common.h"  /* |init_input| */
#include "input.h"

/* The input buffer. */
static unsigned char buffer[MAXLINE+1 + BUFSIZE+1];

unsigned char *cp; 
unsigned char *limit; 
int lineno;
char *line;
char *file;
int lineno;
int infd=0; /* in `mfcalc' we use only |stdin| */

/* The value of |bsize| encodes three different input states:
     -1: no input has been read or a read error has occurred
      0: the end of input has been reached
      n: this many characters have been just read.
   This rather complicated encoding ensures that we never
   read past the end of the input. */
static int bsize;

/* This function initializes the input variables and fills the
   buffer. Declared in |common.h|. */
void init_input(void) {
  limit=cp=&buffer[MAXLINE+1];
  bsize=-1;
  lineno=0;
  fill_buffer();
  if (cp>=limit) cp=limit;
  next_line();
}

/* This function is called whenever |*cp| reads a newline. 
   If |cp| is grater than or equal to limit, the input buffer is
   empty. If |cp| is still equal to |limit| after filling the
   buffer, the end of file has been reached. 
   The do-while loop advances |cp| to the first nonwhite-space
   character in the line, treating sentinel newlines as white
   space.
*/
void next_line(void) {
  do {
    if (cp>=limit) { /* here we have: |*cp=='\n' && cp==limit| which
                        means that we are at the end of the buffer */
      fill_buffer();
      if (cp>=limit) cp=limit;
      if (cp==limit) return;
    } else
      lineno++; /* next line was read (and probably more lines too */
    for (line=(char *)cp; *cp==' ' || *cp=='\t'; cp++) ;
  } while (*cp=='\n' && cp==limit); /* only white space was read; 
                                       refill the buffer */
}

void fill_buffer(void) {
  if (bsize==0) return; /* all input has been read already */
  if (cp>=limit) 
    cp=&buffer[MAXLINE+1];
  else { /* move the tail portion */
    int n=limit-cp;
    unsigned char *s=&buffer[MAXLINE+1]-n;
    line=(char *)s-((char *)cp-line);
    while (cp<limit) *s++=*cp++;
    cp=&buffer[MAXLINE+1]-n;
  }
  bsize=read(infd,&buffer[MAXLINE+1],BUFSIZE);
  if (bsize<0) Error("read error");
  limit=&buffer[MAXLINE+1+bsize];
  *limit='\n';
}

