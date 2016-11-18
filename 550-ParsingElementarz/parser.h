/*
    $URL: http://manta.univ.gda.pl/svn/wb/labs/c/550-ParsingElementarz/parser.h $
    $Revision: 183 $
    $Date: 2006-11-19 16:29:41 +0100 (nie, 19 lis 2006) $
 */

#ifndef parser_included
#define parser_included

typedef int operatorT;

typedef struct expression_ {
  char type;       /* 'D' or 'P' */
  int value;       /* for 'D' */
  operatorT oper;  /* for 'P' */
  struct expression_ *left, *right;
} expressionT;

typedef expressionT AST_node;  /* the top node is an expression */

int parse_program(AST_node **);

#endif
