/*
    $URL: http://manta.univ.gda.pl/svn/wb/labs/c/550-ParsingElementarz/code_gen.c $
    $Revision: 183 $
    $Date: 2006-11-19 16:29:41 +0100 (nie, 19 lis 2006) $
 */

#include <stdio.h>

#include "parser.h"   /* for types AST_node and expressionT */
#include "backend.h"


static void code_gen_expression(expressionT *expr)
{
  switch (expr->type) {
  case 'D':
     printf("%d\n", expr->value);
     break;
  case 'P':
     code_gen_expression(expr->left);
     code_gen_expression(expr->right);
     switch (expr->oper) {
     case '+': printf("add\n"); break;
     case '*': printf("mul\n"); break;
     }
     break;
  }
}

void process(AST_node *icode) 
{
  code_gen_expression(icode);
  printf("==\n");
}
