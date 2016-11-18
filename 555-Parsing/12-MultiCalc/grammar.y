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

   3. Procedura:
   
   Kiedy napotykamy na definicjê procedury (procedure <nazwa>) to w
   tablicy programu umieszczane s± kolejno:
     -- wska¼nik do funkcji procdef,
     -- wska¼nik do pierwszej instrukcji po definicji procedury,
     -- lista instrukcji procedury zakoñczona stop-em.
   Dodatkowo do tablicy symboli (rozszerzonej o nowy typ wpisu) pod nazw±
   zdefiniowanej procedury wpisywany jest jej adres w tablicy programu.

   W czasie dalszego parsowania po natrafieniu na wywo³ania procedury
   (<nazwa>;) do tablicy programu wpisywany jest wska¼nik do funkcji
   procexec oraz zaraz za nim adres kodu procedury wyci±gniêty z tablicy 
   symboli.
   
   Wykonanie programu z procedur±:

   Je¿eli program natrafi na funkcjê procdef to przeskoczy od razu pod adres
   wskazuj±cy za definicjê procedury.
   
   Je¿eli program natrafi na wywo³anie procedury wykona rekurencyjnie podprogram
   pod wskazanym adresem (nastêpna rzecz w kodzie programu).

   Uwaga: rozpoznanie ci±gu "procedure <nazwa>" jest wykonywane przez lex-a,
   zwracany jest token PROCEDURE a w yylval wska¼nik do jej nazwy.

   Drzewko zakodowanej procedury i jej wywo³ania wygl±da mniej wiêcej tak:
   
              ...
              procdef
	      *------------+
	      pstmt1 <--+  |
	      pstmt2    |  |
	      ...       |  |
	      stop      |  |
              ... <-----+--+
	      ...       |
	      ...       |
	      procexec  |
	      *---------+
	      ...
	      ...
  */
  
#include "init.h"
#include "machine.h"
#include "genlib.h"
%}

%union {
  symrecT sym;  /* symbol table pointer */
  machine_instT *inst;  /* machine instruction pointer */
  char *name;   /* ewentualna nazwa procedury */
}

%token <sym> NUMBER VAR BLTIN UNDEF IF ELSE WHILE PRINT RUN STRING
%token <name> PROCEDURE
%token <inst> PROC
%type <inst> exp asgn stmt stmt.exp stmt.if stmt.block stmt.proc stmt.loop stmt.list
%type <inst> print.list
%type <inst> if else while cond end exec procedure
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
  | stmt.proc
  ;
stmt.exp: exp ';'        { code(clear); /* pop top value from stack */ }
  | PRINT print.list ';' { $$=$2; }
  | PROC ';'             { 
     /* Umie¶æ w tablicy kodu procexec i adres kodu procedury do wykonania */
     $$=code2(procexec,(machine_instT)($1[0]));
    }
  ;
stmt.block: '{' stmt.list '}' { $$=$2; }
  ;

stmt.proc: procedure stmt end  {
   ($1)[1]=(machine_instT)$3;   /* Program za procedur± */
   ($1)[2]=(machine_instT)$2;   /* Procedura jako taka */
}
;

procedure: PROCEDURE {
   symrecT s;
   $$ = code3(procdef,stop,stop);
   /* Sprawd¼ czy procedura o nazwie nie jest ju¿ zdefiniowana */
   s = lookup(sym_table, ($1));
   if(s != UNDEFINED)
     { printf("Procedura %s ju¿ zdefiniowana", ($1)); exit(1); }
   /* Dodaj nowy wpis do tablicy symboli ze wska¼nikiem do miejsca, gdzie jest umieszczony 
      adres programu procedury :-)))))) (ale dzia³a bez zarzutu) */
   s = New(symrecT);
   s->type=3; /* procedura */
   s->name=xstrdup($1);
   s->u.procpointer=$$+2;
   enter(sym_table,$1,s);
};

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
