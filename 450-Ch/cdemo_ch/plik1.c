/* 
   Plik: plik1.c 
*/

#include <stdio.h>
#if _CH_
#pragma import "cdemo_ch/cdemo.h"
#else
#include "cdemo.h"
#endif

static int s_i = 901; 

static int fun0(int i) 
{
   INT retval;
   retval = 2*i;
   return retval;
}

int fun1(int i) 
{
   int retval;
   retval = 2*fun0(i);
   return retval;
}
