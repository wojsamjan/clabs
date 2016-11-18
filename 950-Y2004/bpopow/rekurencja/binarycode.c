#include <stdio.h>
#include <stdlib.h>
#define MAX 100

int **tab;

void BinaryCode(int nBits, int min, int max, int b){
   int polowa, i, licznik;
   polowa = min + (max-min-1)/2;
   licznik = b+1-nBits;

   if (nBits>1){
     for(i = min; i<=polowa; i++)
       tab[i][licznik] = 0;
     BinaryCode(nBits-1, min, polowa, b);
     for(i = polowa+1; i<=max; i++)
       tab[i][licznik] = 1;
     BinaryCode(nBits-1, polowa+1, max, b);
   }
   else{
     tab[min][licznik] = 0;
     tab[max][licznik] = 1;
   }
}

/*F-a podnosi liczbê x do potêgi y*/
int Power(int x, int y){
  int i,a;
  if (y == 0) return 1;
  else if (y == 1) return x;
  else {
    a = x;
    for(i = 2; i<=y; i++) x = x*a;
    return x;
  }
}


int main(){

  int i,j,liczba;

  liczba = 5;
  tab = malloc(sizeof(int*)*Power(2,liczba));
  for(i = 0; i<=Power(2,liczba); i++){
    tab[i] = malloc(sizeof(int)*liczba);
  }
  
  printf("\n");
  BinaryCode(liczba, 1,Power(2,liczba),liczba);
  for(i = 1; i<=Power(2,liczba); i++){
    for(j = 1; j<=liczba; j++)
      printf("%d",tab[i][j]);
    printf("\n");
  }

  return 0;
}
