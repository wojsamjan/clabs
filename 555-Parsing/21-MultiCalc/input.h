/* ----------------------------------------------------------
   $Source: /home/nls/WEB/mfcalc/RCS/input.h,v $
   $Date: 2000/01/03 18:48:16 $
   $Revision: 1.2 $
   ----------------------------------------------------------
   This Makefile belongs to the MFCALC package.
   It is distributed WITHOUT ANY WARRANTY, express or implied.
   Copyright (C) 2000 Wlodek Bzyl
   ----------------------------------------------------------
   The input module reads the source in large chunks, usually
   much larger than individual lines. The purpose of this
   module is to minimize the amount of character movement.

   Remark:
   The pointer variables below reference unsigned characters
   so that |*cp|, for example, won't sign-extend a character
   whose value is greater than 127. 
 */

#ifndef _input_h
#define _input_h
#include "genlib.h"

/* The size of the input buffer into which characters are read. */
#define BUFSIZE 4096

/* The maximum number of characters allowed in an unconsumed tail
   of the input buffer. This implies that tokens may not exceed
   that many characters. */
#define MAXLINE 512

/* To minimize the overhead of accessing the input, the
   input, the input module exports pointers that permit
   direct access to the input buffer. */

/* Points to the current input character */
extern unsigned char *cp; 

/* Points one character past the end of the characters in the
   input buffer, and |*limit| is always |\n| and acts as a
   sentinel. */
extern unsigned char *limit; 

/* The variables shown below could be used to compute the
   coordinates of the token which begins at |cp|: 
     column number: cp-line
       line number: lineno. */

/* Gives the location of the beginning of the current line,
   if it were to fit in the buffer. */
extern char *line;

/* The line number of the current line. */
extern int lineno;

/* Input is read from this file descriptor.
   The default is zero, which is |stdin|. */
extern int infd; 

/* This function does all the buffer management and the actual
   input. */
void fill_buffer(void);

/* This function is called whenever |*cp| reads a newline. */
void next_line(void);

#endif
