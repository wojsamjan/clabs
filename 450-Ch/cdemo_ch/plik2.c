/* 
   Plik: plik2.c 
*/

#include <stdio.h>
#if _CH_
#pragma import "cdemo_ch/cdemo.h"
#else
#include "cdemo.h"
#endif

static int s_i = 902;

float fun2(int i)
{
   float retval;
   retval = 2*fun1(i);
   return retval;
}
