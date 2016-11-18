/*
    $URL: http://manta.univ.gda.pl/svn/wb/labs/c/550-ParsingElementarz/interpret.c $
    $Revision: 183 $
    $Date: 2006-11-19 16:29:41 +0100 (nie, 19 lis 2006) $
 */

#include <stdio.h>

#include "parser.h"   /* for types AST_node and expressionT */
#include "backend.h"


static int interpret_expression(expressionT *expr)
{
  switch (expr->type) {
  case 'D':
     return expr->value;
     break;
  case 'P': 
     {
       int e_left = interpret_expression(expr->left);
       int e_right = interpret_expression(expr->right);
       switch (expr->oper) {
       case '+': return e_left + e_right;
       case '*': return e_left * e_right;
       }
     }
     break;
  }
  return 0; /* to make cc happy */
}

void process(AST_node *icode) 
{
  printf("\t%d\n", interpret_expression(icode));
}
