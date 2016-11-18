%{
/* $Source: /home/nls/WEB/zjp/40-Java/RCS/sr-1.y,v $
   $Date: 2000/03/28 16:50:02 $
   $Revision: 1.1 $

   This file is distributed WITHOUT ANY WARRANTY, express or implied.
   Copyright (C) 2000 Wlodek Bzyl
 
   Identifying a shift/reduce conflict is a little harder.
   To identify the conflict, try:
   (1) find the shift/reduce error in *.output
   (2) pick out the reduce rule
   (3) pick out the relevant shift rules
   (4) see where the reduce rule reduces to
   (5) deduce the token stream that will produce the conflict

   sr-1.output
   -----------
   State 1 contains 1 shift/reduce conflict.
   Grammar
     rule 1    start -> x
     rule 2    start -> y R
     rule 3    x -> A R
     rule 4    y -> A
   state 1
     x  ->  A . R   (rule 3)
     y  ->  A .   (rule 4)
     R   	shift, and go to state 4
     R   	[reduce using rule 4 (y)]
     $default	reduce using rule 4 (y)

   Example of the token stream that will produce the conflict: `A R'.

     start -1-> x   -3-> A R  # ambiguity
     start -2-> y R -4-> A R

     A R  -s->  A . R         # shift/reduce conflict (R -- lookahead)
          -r->  y . R
          -s->  y R .
          -r->  start
 */
%}
%token A R
%%
start:  x ;
  |     y R ;
x:      A R ;
y:      A ;
%%
