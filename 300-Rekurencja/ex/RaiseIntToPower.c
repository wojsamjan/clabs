/*  
    $Revision: 1.5 $ 
    $Date: 2004/12/02 14:25:49 $
   
    Napisaæ rekurencyjn± implementacjê funkcji 
    obliczaj±cej n^k (n do potêgi k).
 */

#include <stdio.h>
#include <stdlib.h>
#include "genlib.h"
#include "simpio.h"
#include "strlib.h"

int RaiseIntToPower(int n, int k);

int main()
{
  int x, y;
  printf("\tm = ? ");
  x = GetInteger();
  printf("\tn = ? ");
  y = GetInteger();
  printf("\t%d^%d = %d\n", x, y, RaiseIntToPower(x,y));

  return EXIT_SUCCESS;
}

int RaiseIntToPower(int n, int k)
{
  
  return 0;
}
