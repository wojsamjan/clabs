/*  
    $Revision: 1.5 $
    $Date: 2004/12/02 16:03:56 $

    Napisaæ funkcjê rekurencyjn± C(n,k) obliczaj±c±
                          / n \
    wspó³czynnik Newtona  \ k /  (czyli liczbê podzbiorów 
    k-elementowych zbioru n-elementowego).

    Skorzystaæ z w³asno¶ci Trójk±ta Pascala:

        / n+1 \   =  /  n  \  +  / n \ 
        \  k  /      \ k-1 /     \ k /

        / n \  =  / n \  =  1
        \ 0 /     \ n /
 */

#include <stdio.h>
#include <stdlib.h>
#include "genlib.h"
#include "simpio.h"
#include "strlib.h"

int C(int n, int k);

int main()
{
  int x, y;
  printf("\tx = ? ");
  x = GetInteger();
  printf("\ty = ? ");
  y = GetInteger();
  printf("\tC(%d, %d) = %d\n", x, y, C(x,y));

  return EXIT_SUCCESS;
}

int C(int n, int k)
{

  return 0;
}
