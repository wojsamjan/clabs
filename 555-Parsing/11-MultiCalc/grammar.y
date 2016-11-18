%{/*
   $Source: /home/nls/WEB/zjp/11-MultiCalc/RCS/grammar.y,v $
   $Date: 2000/01/22 00:12:20 $
   $Revision: 1.8 $

   This file is distributed WITHOUT ANY WARRANTY, express or implied.
   Copyright (C) 2000 Wlodek Bzyl

   This grammar provides |if.. else|, |while| and |print| statements, 
   statement grouping with |{..}|, |print| statement and full set of 
   relational operators.

   Notice that |stop| instructions are now generated in several places
   to terminate a sequence; |progp| is the location of the next
   instruction that will be generated; when executed these |stop| 
   instructions will terminate the loop in |execute| (`machine.h'). 
   The production for |end| is in effect a subroutine, called from several 
   places, that generates a |stop| and returns the location of the 
   instruction that follows it.

   1. While loop.
      When the keyword |while| is encountered, the operation
   |whilecode| is generated, and its position in the machine is
   returned as the value of the production |while: WHILE|.
   At the same time, the two following positions in the machine are
   also reserved (using |stop|), to be filled later. 
   The value returned by |cond| is the beginning of the code for the
   condition. After the whole |while| statement has been recognized,
   the two extra positios reserved after the |whilecode| instruction
   are filled with locations of the loop body and the statement that
   follows the loop. Code for that statement will be generated next.
   A picture should make this actions clearer.

   2. If conditional.
      The design of |if| is similiar, except that three spots after
   |ifcode| are reserved, for |then| and |else| parts and the
   statement that follows the |if|.

          ....                         ....                       
        whilecode		     ifcode                     
	   *--------+		        *--------+              
           *--------|--+	        *--------|--+           
          cond      |  |	        *--------------+        
                    |  |	       cond      |  |  |        
          ....      |  |	                 |  |  |        
                    |  |	       ....      |  |  |        
          stop      |  |	                 |  |  |        
       loop body <- +  |	       stop      |  |  |        
                       |	    then part <- +  |  |        
          ....         |	                    |  |        
                       |	       ....         |  |        
          stop         |	                    |  |        
        next stmt <----+ 	       stop         |  |        
          ....			     else part <----+  |        
				                       |        
      				       ....            |        
      				                       |        
      				       stop            |        
      				     next stmt <-------+
  */
#include "init.h"
#include "machine.h"
%}

%union {
  symrecT sym;  /* symbol table pointer */
  machine_instT *inst;  /* machine instruction pointer */
}

%token <sym> NUMBER VAR BLTIN UNDEF IF ELSE WHILE PRINT RUN STRING
%type <inst> exp asgn stmt stmt.exp stmt.if stmt.block stmt.loop stmt.list
%type <inst> print.list
%type <inst> if else while cond end exec
%right '='
%left LT LE GT GE EQ NE
%left '-' '+'
%left '*' '/'
%left UNARYMINUS
%nonassoc '!'
%right '^'  /* exponentiation */

%%

input: /* empty */
  | input stmt.list exec  { return 1; }
  | input error ';'       { yyerrok; }
  ;
exec: RUN                 { $$=code(stop); }
  ;
stmt.list: stmt    
  | stmt.list stmt 
  ;		   
stmt: stmt.exp     
  | stmt.block     
  | stmt.if        
  | stmt.loop      
  ;
stmt.exp: exp ';'        { code(clear); /* pop top value from stack */ }
  | PRINT print.list ';' { $$=$2; }
  ;
stmt.block: '{' stmt.list '}' { $$=$2; }
  ;
stmt.if: if cond stmt end  {
                     ($1)[1]=(machine_instT)$3; /* then part */
                     ($1)[3]=(machine_instT)$4; /* end, if cond fails */ }
  | if cond stmt else stmt end {
                     ($1)[1]=(machine_instT)$3; /* then part */
                     ($1)[2]=(machine_instT)$5; /* else part */
                     ($1)[3]=(machine_instT)$6; /* end, if cond fails */ }
  ;
stmt.loop: while cond stmt end {
                     ($1)[1]=(machine_instT)$3; /* loop body */
                     ($1)[2]=(machine_instT)$4; /* end, if cond fails */ }
  ;
if: IF              { $$=code(ifcode); code3(stop,stop,stop); }
  ;
else: ELSE          { code(stop); $$=progp; }
  ;
while: WHILE          { $$=code3(whilecode,stop,stop); }
  ;
cond: '(' exp ')'     { code(stop); $$=$2; }
  ;
end: /* nothing */    { code(stop); $$=progp; }
  ;
asgn: VAR '=' exp     { $$=$3; code3(varpush, (machine_instT)$1, assign); }
  ;
print.list: exp           { code(print_exp); /* pop top value and print it */ }
  | STRING                { $$=code2(print_string, (machine_instT)$1); }
  | print.list ',' exp    { code(print_exp); }
  | print.list ',' STRING { code2(print_string, (machine_instT)$3); }
  ;
exp: NUMBER           { $$=code2(constpush, (machine_instT)$1); }
  | VAR               { $$=code3(varpush, (machine_instT)$1, eval); }
  | asgn              { $$=$1; }               
  | BLTIN '(' exp ')' { $$=code2(bltin, (machine_instT)$1); }
  | '(' exp ')'       { $$=$2; }
  | exp '+' exp       { code(add); }
  | exp '-' exp       { code(sub); }
  | exp '*' exp       { code(mul); }
  | exp '/' exp       { code(divide); }
  | '-' exp %prec UNARYMINUS  {
                        code(negate); }
  | exp '^' exp       { code(power); }
  | exp LT exp        { code(lt); }
  | exp LE exp        { code(le); }
  | exp GT exp        { code(gt); }
  | exp GE exp        { code(ge); }
  | exp EQ exp        { code(eq); }
  | exp NE exp        { code(ne); }
  | exp '!'           { code(factorial); }
  ;
%%
