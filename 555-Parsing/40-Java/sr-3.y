%{
/* $Source: /home/nls/WEB/zjp/40-Java/RCS/sr-3.y,v $
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

   sr-3.output
   -----------
   State 1 contains 1 shift/reduce conflict.
   State 6 contains 1 reduce/reduce conflict.
   Grammar
     rule 1    start -> x1
     rule 2    start -> x2
     rule 3    start -> x3
     rule 4    start -> y R
     rule 5    x1 -> A R
     rule 6    x2 -> A z1
     rule 7    x3 -> A z2
     rule 8    y -> A
     rule 9    z1 -> R
     rule 10   z2 -> S
   state 1
     x1  ->  A . R   (rule 5)
     x2  ->  A . z1   (rule 6)
     x3  ->  A . z2   (rule 7)
     y  ->  A .   (rule 8)
     R   	shift, and go to state 6   # conflict on R
     S   	shift, and go to state 7   # no conflict on S
     R   	[reduce using rule 8 (y)]  # conflict on R
     $default	reduce using rule 8 (y)
     z1  	go to state 8
     z2  	go to state 9

   Example of the token stream that will produce the shift/reduce conflict.

     start -> x1 -> A R          # ambiguity
     start -> x2 -> A z1 -> A R
     start -> y R -> A R

     A R  -s->  A . R            # shift/reduce conflict (R -- lookahead)
          -r->  y . R            # there is no conflict on `S'!
          -s->  y R .
          -r->  start

   Example of the token stream that will produce the reduce/reduce conflict.
      (exercise)
 */
%}
%token A R S
%%
start:  x1 
  |     x2   
  |     x3   
  |     y R  ;
x1:     A R  ;
x2:     A z1 ;
x3:     A z2 ;
y:      A    ;
z1:     R    ;
z2:     S    ;
%%
