/*
    $URL: http://manta.univ.gda.pl/svn/wb/labs/c/550-ParsingElementarz/parser.c $
    $Revision: 183 $
    $Date: 2006-11-19 16:29:41 +0100 (nie, 19 lis 2006) $
 */

#include <stdlib.h>

#include "lex.h"
#include "error.h"
#include "parser.h"

#define DEBUG

static int parse_operator(operatorT *oper_p);
static int parse_expression(expressionT **expr_p);

int parse_program(AST_node **icode_p) 
{
  expressionT *expr;

  yylex();  /* start the lexical analyzer */
  DEBUG;
  if (parse_expression(&expr)) {
    if (token.class != EOP) {
      error("garbage after the end of program");
    }
    *icode_p = expr;
    return 1;
  }

  return 0;
}


static expressionT *new_expression(void) 
{
  return malloc(sizeof(expressionT));
}


static void free_expression(expressionT *e) 
{
  free(e);
}


static int parse_operator(operatorT *oper) 
{
  if (token.class=='+') {
    *oper='+';
    yylex(); DEBUG;
    return 1;
  }
  if (token.class=='*') {
    *oper='*';
    yylex(); DEBUG;
    return 1;
  }
  return 0;
}


static int parse_expression(expressionT **expr_p) 
{
  expressionT *expr = *expr_p = new_expression();

  /* try to parse a digit */
  if (token.class==DIGIT) {
    expr->type = 'D';
    expr->value = token.repr-'0';
    yylex(); DEBUG;
    return 1;
  }
  /* try to parse a parenthesized expression */
  if (token.class=='(') {
    expr->type = 'P';
    yylex(); DEBUG;
    if (!parse_expression(&expr->left))
      error("missing expression");
    if (!parse_operator(&expr->oper))
      error("missing operator");
    if (!parse_expression(&expr->right))
      error("missing expression");
    if (token.class!=')')
      error("missing )");
    yylex(); DEBUG;
    return 1; 
  }
  /* failed on both attempts */
  free_expression(expr);
  return 0;
}

