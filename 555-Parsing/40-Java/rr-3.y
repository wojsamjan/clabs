%{
/* $Source: /home/nls/WEB/zjp/40-Java/RCS/rr-3.y,v $
   $Date: 2000/03/28 16:50:02 $
   $Revision: 1.1 $

   This file is distributed WITHOUT ANY WARRANTY, express or implied.
   Copyright (C) 2000 Wlodek Bzyl
 
   The following grammar contains 1 reduce/reduce conflict.
   Let's review the conflict as described in rr-3.output.

   rr-3.output
   -----------
   State 5 contains 1 reduce/reduce conflict.
   Grammar
     rule 1    start -> A B x Z
     rule 2    start -> y Z
     rule 3    x -> C
     rule 4    y -> A B C
   state 5
     x  ->  C .   (rule 3)
     y  ->  A B C .   (rule 4)
     Z   	reduce using rule 3 (x)
     Z   	[reduce using rule 4 (y)]
     $default	reduce using rule 3 (x)

   Example of the token stream that will produce the conflict: `A B C Z'.

     start -1-> A B x Z -3-> A B C Z  # ambiguity
     start -2-> y Z -4-> A B C Z
   
     A B C Z  =s=>    A B C . Z       # reduce/reduce conflict (Z -- lookahead)
              -r_3->  A B x . Z   
              -s->    A B x Z .
              -r->    start
 */
%}
%token A B C Z
%%
start:  A B x Z ;
  |     y Z ;
x:      C ;
y:      A B C ;
%%
