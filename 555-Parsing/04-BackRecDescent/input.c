/* $Source: /home/nls/WEB/mfcalc/MFCALC2/RCS/lex.c,v $
   $Date: 2000/01/04 20:08:53 $
   $Revision: 1.1 $

   This file implements |read_line| function for an exhaustive
   backtracking LL(1) parser.

   It is distributed WITHOUT ANY WARRANTY, express or implied.
   Copyright (C) 2000 Wlodek Bzyl
 */

#include <stdio.h>
#include <string.h>
#include "ebrd.h"

/* Read one line from |stdin| */
void read_line(void) {
  printf("> ");
  if (fgets(buffer,infinity,stdin)==NULL) 
    Error("input error on stdin");
  else { 
    int n=strlen(buffer);
    buffer[n]='#';
    tp=0;
    rp=0;
  }
}
