#include <stdio.h>
#include <stdlib.h>

//#define bignum 2095318  /* OK */
#define bignum 2095319  /* Naruszenie ochrony pamięci */

int main()
{
  unsigned long t[bignum], i;
  unsigned long *tp;

  printf("Zaczynam zapisywać elementy do tablicy..\n");
  for (i=0; i<bignum; i++)
    t[i]=i;
  printf("Zrobione!\n");

  return 0;
}

/* effekt jw.

  tp = malloc(bignum*sizeof(unsigned long));
  printf("Zaczynam zapisywać elementy do tablicy..\n");
  for (i=0; i<bignum; i++)
    tp[i]=i;
  printf("Zrobione!\n");
*/
