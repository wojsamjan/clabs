%{
/* $Source: /home/nls/WEB/zjp/40-Java/RCS/java-yacc.y,v $
   $Date: 2000/03/28 11:00:54 $
   $Revision: 1.2 $

   This file is distributed WITHOUT ANY WARRANTY, express or implied.
   Copyright (C) 2000 Wlodek Bzyl

   This grammar was derived from the experimental Pretzel grammar 
   for Java by Lee Wittenberg.
   The Pretzel homepage is:
      http://www.iti.informatik.th-darmstadt.de/~gaertner/pretzel
   The pretzel was written by Felix Gaertner <fcg@acm.org>
 */
%}
%token	BINOP
%token	BREAK_LIKE
%token	CASE_LIKE
%token	CATCH_LIKE
%token	CHUNK
%token	COLON
%token	COMMA
%token	COMMENT
%token	DEFAULT_LIKE
%token	DOT
%token	DOT_STAR
%token	DO_LIKE
%token	ELSE_LIKE
%token	EXTENDS_LIKE
%token	FINALLY_LIKE
%token	FOR_LIKE
%token	ID_LIKE
%token	IF_LIKE
%token	IGNORE
%token	IMPORT_LIKE
%token	INCROP
%token	LBRACE
%token	LBRACK
%token	LPAR
%token	NUM
%token	QUESTION
%token	RBRACE
%token	RBRACK
%token	RPAR
%token	SEMI
%token	STRING
%token	SYNC_LIKE
%token	TRY_LIKE
%token	UNOP
%token	UNORBINOP
%%

final: exp 
  | decl_list
  | IGNORE
  | COMMENT
  | IGNORE final
  | COMMENT final
  ;
decl_list: decl
  | decl_list decl
  ;
decl: exp block
  ;
block: lbrace rbrace
  | lbrace decl_list rbrace
  ;
exp: expr
  | exp dot expr
  | exp comma expr
  | exp expr
  ;
expr: term
  | expr binop term
  | expr unorbinop term
  | expr extends_like idlist  
  | expr brack_exp
  ;
binop: question exp colon
  ; 
idlist:	ident
  | idlist comma ident
  ;
ident: id_like
  | sync_like id_like
  | ident id_like
  ;
brack_exp: lbrack rbrack
  | lbrack exp rbrack
  | brack_exp ident
  ;
term: factor
  | unop term
  | unorbinop term
  | incrop term
  | term incrop
  ;
factor: ident
  | num
  | string 
  | lpar rpar
  | lpar exp rpar
  ;
decl: block
  | non_block_stmt
  ;
non_block_stmt: semi
  | exp semi
  | break_like semi
  | break_like exp semi 
  | sync_like lpar exp rpar decl
  | import_head semi
  | label colon decl
  | try_stmt
  | if_block
  | if_simple
  | else_head block
  | else_head non_block_stmt
  | for_stmt
  | do_stmt
  ;
import_head: import_like id_like
  | import_head dot id_like
  | import_head dot_star
  ;
if_head: if_like lpar exp rpar
  ;
if_block: if_head block
  ;
if_simple: if_head non_block_stmt
  ;
else_head: else_like
  | if_block else_like
  | if_simple else_like
  ;
try_stmt: try_like block
  | try_stmt finally_like block
  | try_stmt catch_like lpar exp rpar block
  ;
label: default_like
  | case_like exp
  | id_like
  ;
do_stmt: do_like block if_head semi
  | do_like non_block_stmt if_head semi
  ;
for_head: for_like lpar for_control rpar
  ;
for_control: opt_exp semi opt_exp semi opt_exp
  ;
opt_exp: /* empty */
  | exp
  ;
for_stmt: for_head block
  | for_head non_block_stmt
  ;
/* rules to pass comments and ignores through unnoticed */
binop: BINOP
  | binop IGNORE
  | binop COMMENT 
  ;
break_like: BREAK_LIKE
  | break_like IGNORE
  | break_like COMMENT
  ;
case_like: CASE_LIKE
  | case_like IGNORE
  | case_like COMMENT
  ;
catch_like: CATCH_LIKE
  | catch_like IGNORE
  | catch_like COMMENT	
  ;
colon: COLON
  | colon IGNORE
  | colon COMMENT 
  ;
comma: COMMA
  | comma IGNORE
  | comma COMMENT 
  ;
default_like: DEFAULT_LIKE
  | default_like IGNORE
  | default_like COMMENT	
  ;
dot: DOT
  | dot IGNORE
  | dot COMMENT 
  ;
dot_star: DOT_STAR
  | dot_star IGNORE
  | dot_star COMMENT
  ;
do_like: DO_LIKE
  | do_like IGNORE
  | do_like COMMENT 
  ;
else_like: ELSE_LIKE
  | else_like IGNORE
  | else_like COMMENT  
  ;
extends_like: EXTENDS_LIKE
  | extends_like IGNORE
  | extends_like COMMENT  
  ;
finally_like: FINALLY_LIKE
  | finally_like IGNORE
  | finally_like COMMENT
  ;
for_like: FOR_LIKE
  | for_like IGNORE
  | for_like COMMENT 
  ;
id_like: ID_LIKE
  | CHUNK
  | id_like IGNORE
  | id_like COMMENT 
  ;
if_like: IF_LIKE
  | if_like IGNORE
  | if_like COMMENT  
  ;
import_like: IMPORT_LIKE
  | import_like IGNORE
  | import_like COMMENT  
  ;
incrop: INCROP
  | incrop IGNORE
  | incrop COMMENT  
  ;
lbrace:	LBRACE
  | lbrace IGNORE
  | lbrace COMMENT  
  ;
lbrack:	LBRACK
  | lbrack IGNORE
  | lbrack COMMENT  
  ;
lpar: LPAR
  | lpar IGNORE
  | lpar COMMENT  
  ;
num: NUM
  | num IGNORE
  | num COMMENT  
  ;
question: QUESTION
  | question IGNORE
  | question COMMENT  
  ;
rbrace:	RBRACE
  | rbrace IGNORE
  | rbrace COMMENT  
  ;
rbrack:	RBRACK
  | rbrack IGNORE
  | rbrack COMMENT  
  ;
rpar: RPAR
  | rpar IGNORE
  | rpar COMMENT  
  ;
semi: SEMI
  | semi IGNORE
  | semi COMMENT  
  ;
string:	STRING
  | string IGNORE
  | string COMMENT  
  ;
sync_like: SYNC_LIKE
  | sync_like IGNORE
  | sync_like COMMENT  
  ;
try_like: TRY_LIKE
  | try_like IGNORE
  | try_like COMMENT  
  ;
unop: UNOP
  | unop IGNORE
  | unop COMMENT  
  ;
unorbinop: UNORBINOP
  | unorbinop IGNORE
  | unorbinop COMMENT  
  ;
%%
