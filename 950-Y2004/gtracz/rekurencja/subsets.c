//Grzegorz Tracz
/*  
 *  File: subsets.c
 *
 *  $Revision: 1.1.1.1 $
 *  $Date: 2004/01/24 10:40:47 $
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
#include <string.h>
#include <stdlib.h>
//#include "strlib.h"

char napis[] = "ABCD";

static void ListSubsets(char *str, int y);

void drukuj(char *a,char *q, int y,char *str,int size){
  char *z,x;
  z=a;
  printf("{");
  for (x=0;x<y;x++){
    printf("%c",*z);
    z++;
  }
  printf("}\n");
  for (x=y;x<size;x++){
     if (*str!='\0'){
      if (*q==*str);
      else{
	*q=*str;
	str++;
	//	printf(" x=%d y=%d size=%d q=%c str=%c \n",x,y,size,*q,*str);
	*(q+1)='\0';
	drukuj(a,q+1,y+1,str,size);
      }
    }
  }
}

int main() {
  int e;
  e=strlen(napis);
  napis[e]='\0';
  ListSubsets(napis,e); 
  return EXIT_SUCCESS;
}

static void ListSubsets(char *str, int y) {
  char A[y];
  A[y]='\0';
  drukuj(A,A,0,str,y);

}
