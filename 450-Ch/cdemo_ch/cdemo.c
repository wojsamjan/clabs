/* 
   Plik: cdemo.c 
*/

#include <stdio.h>
#if _CH_
#pragma import "cdemo_ch/cdemo.h"
#else
#include "cdemo.h"
#endif

int main() {
   INT i;
   TAG s;
   float f; 

   i = MAGICNUM;
   s.i = i;
   s.j = fun1(i);
   f = fun2(i);
   
   printf("s.i = %d\n", s.i);
   printf("s.j = %d\n", s.j);
   printf("f = %f\n", f);
}
 
