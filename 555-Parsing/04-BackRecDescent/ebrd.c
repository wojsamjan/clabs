/* $Source: /home/nls/WEB/mfcalc/MFCALC2/RCS/main.c,v $
   $Date: 2000/01/04 20:08:53 $
   $Revision: 1.1 $

   This file implements an exhaustive backtracking recursive-descent
   parser that will correctly parse according to the grammar
   described below. The parser implements backtracking by only
   checking one symbol at a time and passing the rest of the
   alternative as a parameter for evaluation on a lower level.

   It is distributed WITHOUT ANY WARRANTY, express or implied.
   Copyright (C) 2000 Wlodek Bzyl
 
   The language recognized by the parser is described by the
   grammar:
      S: D C | A B
      A: a | a A
      B: b c | b B c
      D: a b | a D b
      C: c | c C
 */

#include <stdlib.h>
#include "erbd.h"

int main() {


  return EXIT_SUCCESS;
}
