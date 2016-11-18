%{
/* $Source: /home/nls/WEB/zjp/40-Java/RCS/rr-2.y,v $
   $Date: 2000/03/28 16:50:02 $
   $Revision: 1.1 $

   This file is distributed WITHOUT ANY WARRANTY, express or implied.
   Copyright (C) 2000 Wlodek Bzyl
 
   The following grammar contains 1 reduce/reduce conflict.
   Let's review the conflict as described in rr-2.output.

   rr-2.output
   -----------
   State 5 contains 1 reduce/reduce conflict.
   Grammar
     rule 1    start -> a Z
     rule 2    start -> b Z
     rule 3    a -> X y
     rule 4    b -> X y
     rule 5    y -> Y
     [...]
   state 5
     a  ->  X y .   (rule 3)              # Both rules might be reduced.
     b  ->  X y .   (rule 4)              #
     Z   	reduce using rule 3 (a)   # Reduce/reduce conflict between rule
     Z   	[reduce using rule 4 (b)] # 3 and rule 4 when token Z is read.
     $default	reduce using rule 3 (a)   # This is the chosen rule.

   Example of the token stream that will produce the conflict: `X Y Z'.

     start -1-> a Z -3-> X y Z -5-> X Y Z  # ambiguity
     start -2-> b Z -4-> X y Z -5-> X Y Z
   
     X Y Z  -s->    X . Y Z 
            -s->    X Y . Z   # reduce/reduce conflict (Z -- lookahead)
            -r_3->  X y . Z   
            -r->    a . Z 
            -s->    a Z .
            -r->    start 
 */
%}
%token X Y Z
%%
start:  a Z ;
  |     b Z ;
a:      X y ;
b:      X y ;
y:      Y   ;
%%
