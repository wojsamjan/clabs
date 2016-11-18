%{
/* $Source: /home/nls/WEB/zjp/40-Java/RCS/rr-1.y,v $
   $Date: 2000/03/28 16:50:02 $
   $Revision: 1.1 $

   This file is distributed WITHOUT ANY WARRANTY, express or implied.
   Copyright (C) 2000 Wlodek Bzyl
 
   The following grammar contains 1 reduce/reduce conflict.
   Let's review the conflict as described in rr-1.output.

   rr-1.output
   -----------
   State 1 contains 1 reduce/reduce conflict.
   Grammar
     rule 1    start -> a Y
     rule 2    start -> b Y
     rule 3    a -> X
     rule 4    b -> X
     [...]   
   state 1
      a  ->  X .   (rule 3)               # Both rules might be reduced.
      b  ->  X .   (rule 4)               #
      Y   	reduce using rule 3 (a)   # Reduce/reduce conflict between rule
      Y   	[reduce using rule 4 (b)] # 3 and rule 4 when token Y is read.
      $default	reduce using rule 3 (a)   # Yacc chose rule 3, i.e. it resolves
                                          # reduce/reduce conflict by reducing
                                          # the rule that appears earlier in 
                                          # the grammar.

   Example of the token stream that will produce the conflict: `X Y'.

     start -1-> a Y -3-> X Y  # ambiguity
     start -2-> b Y -4-> X Y

     X Y -shift->     X . Y   # reduce/reduce conflict (Y -- lookahead)
         -reduce_3->  a . Y   
         -shift->     a Y . 
         -reduce->    start 
 */
%}
%token X Y
%%
start:  a Y
     |  b Y ;
a:      X ;
b:      X ;
%%
