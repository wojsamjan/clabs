/*  
    $Revision: 1.7 $
    $Date: 2004/12/05 23:21:30 $
  
    Napisaæ funkcjê rekurencyjn± odwracaj±c± kolejno¶æ
    liter w napisie podanym na wej¶ciu.
 */

#include <stdio.h>
#include <stdlib.h>
#include "genlib.h"
#include "simpio.h"
#include "strlib.h"

string Reverse(string str);

int main()
{
  string str;
  str = GetLine();
  printf("\tstr = `%s'\n", str);
  Reverse(str);
  printf("\treverse(str) = `%s'\n", str);

  return EXIT_SUCCESS;
}

int Reverse(string str)
{
  return 0;
}
