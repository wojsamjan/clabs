%{
/* $Source: /home/nls/WEB/zjp/40-Java/RCS/sr-2.y,v $
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

   sr-2.output
   -----------
   State 1 contains 1 shift/reduce conflict.
   State 5 contains 1 reduce/reduce conflict.
   Grammar
     rule 1    start -> x1
     rule 2    start -> x2
     rule 3    start -> y R
     rule 4    x1 -> A R
     rule 5    x2 -> A z
     rule 6    y -> A
     rule 7    z -> R
   state 1
     x1  ->  A . R   (rule 4)
     x2  ->  A . z   (rule 5)
     y  ->  A .   (rule 6)
     R   	shift, and go to state 5
     R   	[reduce using rule 6 (y)]
     $default	reduce using rule 6 (y)
     z   	go to state 6
   state 5
     x1  ->  A R .   (rule 4)
     z  ->  R .   (rule 7)
     $   	reduce using rule 4 (x1)
     $   	[reduce using rule 7 (z)]
     $default	reduce using rule 4 (x1)

   Example of the token stream that will produce the shift/reduce conflict.

     start -> x1 -> A R          # ambiguity
     start -> x2 -> A z -> A R

     A R  -s->  A . R            # shift/reduce conflict (R -- lookahead)
          -r->  y . R
          -s->  y R .
          -r->  start

   Example of the token stream that will produce the reduce/reduce conflict.
  
     A R =s=>   A R .            # reduce/reduce conflict 
         -r_7-> A z .            # ($ (eof) -- lookahead)
         ->     x2
         ->     start 
 */
%}
%token A R
%%
start:  x1 
  |     x2  ;
  |     y R ;
x1:     A R ;
x2:     A z ;
y:      A   ;
z:      R   ;
%%
