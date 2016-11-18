%{
/* $Source: /home/nls/WEB/zjp/40-Java/RCS/java-lex.l,v $
   $Date: 2000/03/28 11:00:54 $
   $Revision: 1.2 $

   This file is distributed WITHOUT ANY WARRANTY, express or implied.
   Copyright (C) 2000 Wlodek Bzyl
 
   This scanner was derived from the experimental Pretzel scanner
   for Java by Lee Wittenberg.
   The Pretzel homepage is:
      http://www.iti.informatik.th-darmstadt.de/~gaertner/pretzel
   The pretzel was written by Felix Gaertner <fcg@acm.org>
*/
%}
%option noyywrap

ALPH		[a-zA-Z_$]
ALPHNUM		[a-zA-Z0-9_$]
DIGIT		[0-9]
DECDIGIT	[0-9]
OCTDIGIT	[0-7]
HEXDIGIT	[0-9A-Fa-f]
EXP             ([eE][+-]?[0-9]+)

%%

/* Symbols. */

"{"    LBRACE	
"}"    RBRACE	
"("    LPAR
")"    RPAR
"["    LBRACK
"]"    RBRACK
";"    SEMI	
":"    COLON	
","    COMMA	
"."    DOT      
 
"+"    |
"-"    UNORBINOP
"="    BINOP
"<"    |
">"    BINOP
"!"    UNOP	
"~"    UNOP	
"?"    QUESTION	
"=="   BINOP	
"<="   BINOP	
">="   BINOP	
"!="   BINOP	
"||"   BINOP	
"&&"   BINOP	
"++"   |	
"--"   INCROP	
"*"    BINOP	
"/"    BINOP	
"&"    BINOP	
"|"    BINOP	
"^"    BINOP	
"%"    BINOP	
"<<"   BINOP	
">>"   BINOP	
">>>"  BINOP	
"+="   BINOP	
"-="   BINOP	
"*="   BINOP	
"/="   BINOP	
"&="   BINOP	
"|="   BINOP	
"^="   BINOP	
"%="   BINOP	
"<<="  BINOP	
">>="  BINOP	
">>>=" BINOP	

"//".* COMMENT	

/* Keywords. */

"new"        UNOP		
"instanceof" BINOP		
				
"null"       ID_LIKE		

"class"      |
"interface"  |

"void"       |
"boolean"    |
"byte"       |
"char"       |
"double"     |
"float"      |
"int"        |
"long"       |
"short"      |

"abstract"   |
"final"      |
"native"     |
"protected"  |
"private"    |
"public"     |
"static"     |
"transient"  |
"volatile"   |

"true"		|
"false"		|
"super"		|
"this"		ID_LIKE		
				
"case"		CASE_LIKE	
"default"	DEFAULT_LIKE	
				
"synchronized"	SYNC_LIKE	
				
				
"try"		TRY_LIKE	
"catch"		CATCH_LIKE	
"finally"	FINALLY_LIKE	
				
"if"		|		
"switch"	|		
"while"		IF_LIKE		
				
"else"		ELSE_LIKE	
				
"for"		FOR_LIKE	
"do"		DO_LIKE		
				
"break"		|		
"continue"	|		
"return"	|		
"throw"		BREAK_LIKE	
				
"throws"	|		
"extends"	|		
"implements"    EXTENDS_LIKE	
				
"package"	|		
"import"	IMPORT_LIKE	
".*"		DOT_STAR	

/* Misc */

^"@use\ ".*	CHUNK
^"@".*		IGNORE

0[lL]? |
[1-9]{DECDIGIT}*[lL]? NUM
0{OCTDIGIT}+[lL]? NUM    
0[xX]{HEXDIGIT}{HEXDIGIT}*[lL]?  NUM
{DECDIGIT}+"."{DECDIGIT}*{EXP}?[fdFD]?	|
"."{DECDIGIT}+{EXP}?[fdFD]?  |
{DECDIGIT}+{EXP}[fdFD]? NUM  

[a-zA-Z] ID_LIKE

{ALPH}{ALPHNUM}*  ID_LIKE

'([^']|\\')*'		|
\"([^\"]|\\\")*\"	STRING

[\ \t\n]  /* gobble up whitespace */
 
. /* ignore all non-standard chars; */
%%
