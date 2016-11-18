/*
    $URL: http://manta.univ.gda.pl/svn/wb/labs/c/550-ParsingElementarz/main.c $
    $Revision: 183 $
    $Date: 2006-11-19 16:29:41 +0100 (nie, 19 lis 2006) $
 */

#include <stdlib.h>

#include "parser.h"    /* AST_node */
#include "backend.h"   /* process() */
#include "error.h"     /* error() */

int main ()
{
  AST_node *icode;

  if (!parse_program(&icode))
    error("no top-level expression");
  process(icode);

  return EXIT_SUCCESS;
}
