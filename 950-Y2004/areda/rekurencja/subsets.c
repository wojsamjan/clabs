/*  
 *  File: subsets.c
 *
 *  $Revision: 1.1.1.1 $
 *  $Date: 2004/01/24 10:38:52 $
 *
    Napisz funkcjê `ListSubsets' generuj±c± wszystkie
    mo¿liwe podzbiory podanego zbioru, gdzie zbiór
    sk³ada siê z liter podanych w postaci napisu.
    Na przyk³ad po wywo³aniu `ListSubsets("ABC")'
    na terminalu powinni¶my otrzymaæ (byæ mo¿e 
    w innej kolejno¶ci):

       {ABC}   {BC}  
       {AB}    {B}
       {AC}    {C}
       {A}     {}
 */

#include <stdio.h>
#include <stdlib.h>
#include "strlib.h"

char napis[] = "ABC";

static void ListSubsets(string, string, int);
static void PrintSubset(string);

int main() {
  ListSubsets(napis,"",0); 
  return EXIT_SUCCESS;
}

static void ListSubsets(string str,string subset, int k) 
{
	string subset1;
	int i, subLen=StringLength(str);

	PrintSubset(subset);
	if (k<subLen)
		for(i=k; i<subLen; ++i)
		{
			subset1=Concat(subset,SubString(str,i,i));
			ListSubsets(str,subset1,i+1);		
		}
}

static void PrintSubset(string subset)
{
	printf("{%s}\n",subset);
}
				

