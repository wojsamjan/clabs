

#include <stdio.h>
#include <stdlib.h>
/*#include "strlib.h"*/

static void GenerateGrayCode(int nBits, int nBits2);
static void  int2gray(int i,int dl);

int main() {
  int ile;
  printf("\n ile bitow : ");
  scanf("%d",&ile);
  GenerateGrayCode(ile,ile); 
  return EXIT_SUCCESS;
}

static void GenerateGrayCode(int nBits, int nBits2) {

  int l;
  int high=2;
  int low=2;
  
  int pom=nBits;
  
  if(pom<=0) exit(1);
  if(pom>1){
      l = pom-1;
  for(;l!=0;l--){
    high*=2;
  }
  l=pom-2;
   for(;l!=0;l--){
    low*=2;
  }
    }

 if(pom==1){
   int2gray(1,nBits2);
   int2gray(0,nBits2);
}
  else {
      for(--high;high>=low;high--){
	int2gray(high,nBits2);  /* funkcja bierze liczbe dziesietna i wyswietla binarnie na okreslonej liczbie bitow */
      }                         
      GenerateGrayCode(pom-1, nBits2);   
   }
}



void int2gray(int i,int dl){  /* funkcja do wyswietlania liczby 10 w kodzie graya */
  int j,k=0;
  int tab[dl];

  for(j=0;j<dl;j++) { tab[j]=0;}  

/* tutaj konwersja z dziesietnej na binarna */
   while(i!=0){
    tab[k++]=i % 2;
    i/=2;
  }

   /* tutaj konwersja z kodu binarnego na kod greya */
   for(j=0;j<dl-1;j++){        
     tab[j]=tab[j]^tab[j+1];   /* a[n]=a[n]^a[n-1]  (liczac od najmlodszych)*/
   }
   tab[dl-1]=tab[dl-1]^0;  /* najstarszy bit^0 */

 
   for(j=dl-1;j>=0;j--){    printf("%d",tab[j]);  }  
 printf("\n"); 
}
