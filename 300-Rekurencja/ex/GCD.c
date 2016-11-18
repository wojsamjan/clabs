/*  
    $Revision: 1.4 $
    $Date: 2004/12/02 14:21:32 $

    GCD -- najwiêkszy wspólny dzielnik.
    Euklides udowodni³, ¿e GCD liczb x, y mo¿na obliczyæ
    w nastêpuj±cy sposób:
      (1) Je¶li y dzieli x, to najwiêkszym wspólnym dzielnikiem
          jest y.
      (2) W przeciwnym wypadku, najwiêkszym wspólnym dzielnikiem
          jest równy najwiêkszemu wspólnemu dzielnikowi
          y i reszcie dzielenia x przez y. 
 
    Korzystaj±c z twierdzenia Euklidesa, napisaæ program
    obliczaj±cy rekurencyjnie najwiêkszy wspólny dzielnik 
    z liczb podanych na wej¶ciu.
 */

#include <stdio.h>
#include <stdlib.h>
#include "genlib.h"
#include "simpio.h"
#include "strlib.h"

int GCD(int x, int y);

int main()
{
  int m, n;
  printf("\tn = ? ");
  m = GetInteger();
  printf("\tm = ? ");
  n = GetInteger();
  printf("\tGCD(%d, %d) = %d\n", m, n, GCD(m,n));

  return EXIT_SUCCESS;
}

int GCD(int x, int y)
{

  return 0;
}
