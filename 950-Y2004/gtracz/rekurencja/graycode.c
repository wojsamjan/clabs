//Grzegorz Tracz
/*  
 *  File: graycode.c
 *
 *  $Revision: 1.1.1.1 $
 *  $Date: 2004/01/24 10:40:47 $
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


void Generate(int nBits,int y,int *a, int *q){
  int *z,x,Q[nBits+1];
  if(y==nBits){
    z=a;
    for (x=0;x<nBits;x++){
      Q[x+1]=*z;
      z++;
    }
    Q[0]=0;
    Q[nBits]='\0';
    z=a;
    for (x=0;x<nBits;x++){
      Q[x]=Q[x]^(*z);
      z++;
    }
    z=a;
    for (x=0;x<nBits;x++){
      printf("%d",Q[x]);
      //  z++;
    }
    printf("\n");
  }else{
    *q=0;
    Generate(nBits,y+1,a,q+1);
    *q=1;
    Generate(nBits,y+1,a,q+1);
  }
}

static void GenerateGrayCode(int nBits) {
int A[nBits+1];
 A[nBits+1]='\0';
 Generate(nBits,0,A,A);
}


int main() {
  GenerateGrayCode(3); 
  return EXIT_SUCCESS;
}

