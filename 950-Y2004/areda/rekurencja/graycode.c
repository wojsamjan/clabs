/*  
 *  File: graycode.c
 *
 *  $Revision: 1.1.1.1 $
 *  $Date: 2004/01/24 10:38:52 $
 *
    Liczby z przedzia³u [0..7], mo¿emy ponumerowaæ inaczej
    ni¿ w `binarycode.c'. Na przyk³ad w taki sposób:

      000 -> 0   110 -> 4
      001 -> 1   111 -> 5
      011 -> 2   101 -> 6
      010 -> 3   100 -> 7
 
    Zauwa¿my, ¿e przy takiej numeracji kolejne liczby
    ró¿ni± siê tylko na jednym bicie, np. reprezentacje
    bitowe liczb 3 i 4 ró¿ni± siê pierwszym bitem.
    Taki kodowanie liczb nazywamy kodowaniem Gray'a.
    Napisz funkcjê `GenerateGrayCode(nBits)' wypisuj±c±
    dla podanej liczby `nBits' kody Gray'a dla kolejnych
    liczb naturalnych od 0 do 2^N-1.
    Czy wiesz do czego takie kodowanie mo¿e siê przydaæ?
    UWAGA: jest wiele rozwi±zañ.
 */

#include <stdio.h>
#include <stdlib.h>
#include "strlib.h"

static void GenerateGrayCode(string s, int nBits, int nr);

int main() {
  GenerateGrayCode("",3,1); 
  printf("\n");
  return EXIT_SUCCESS;
}

static void GenerateGrayCode(string s,int nBits,int nr) 
{
	if (nBits==0) 
		printf("%s ",s);
	else
	{
		nBits--;
		if (nr==1)
		{
			GenerateGrayCode(Concat(s,"0"),nBits,1);
			GenerateGrayCode(Concat(s,"1"),nBits,2);
		}
		else 
		{
			GenerateGrayCode(Concat(s,"1"),nBits,1);
			GenerateGrayCode(Concat(s,"0"),nBits,2);
		}
	}

}
