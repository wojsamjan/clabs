/*  
 *  File: subsets.c
 *
 *  $Revision: 1.1.1.1 $
 *  $Date: 2004/01/24 10:40:27 $
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

static void ListSubsets();
static void generator(int n, int liczba, int i, string s);

int main()
{
    ListSubsets();
    return EXIT_SUCCESS;
}

static void ListSubsets()
{
    int n;
    for (n = 0; napis[n] != '\0'; n++);
    if (n == 0)
	printf("{}\nZbiór nie zawiera ¿adnego elementu!\n");
    else {
	printf("{}\n{%s}\n", napis);
	generator(n - 1, n - 1, 0, "");
    }
}
static void generator(int n, int liczba, int i, string s)
{
    string temp;
    if (n == 0);
    else {
	for (; i <= n; i++) {
	    temp = CopyString(s);
	    s = Concat(s,
		       SubString(napis, liczba - n + i, liczba - n + i));
	    printf("{%s}\n", s);
	    generator(n - 1, liczba, i, s);
	    s = CopyString(temp);
	}
    }
}
