//Grzegorz Tracz
/*  
 *  File: telefon.c
 *
 *  $Revision: 1.1.1.1 $
 *  $Date: 2004/01/24 10:40:47 $
 *
    Na przyciskach mojego telefonu przy cyfrach wydrukowano
    nastêpuj±ce litery:

       1 -       6 - MNO
       2 - ABC   7 - PRS
       3 - DEF   8 - TUV
       4 - GHI   9 - WXZ
       5 - JKL   0 - 

    Czasami, aby u³atwiæ zapamiêtanie numeru, operator
    podaje s³owo. Na przyk³ad

       767   (SOS)
       4357  (HELP)
 
    itp.

    Napisaæ funkcjê `ListMnemonics' generuj±c± wszystkie
    mo¿liwe kombinacje liter odpowiadaj±ce podanej
    liczbie, podanej jako napis z³o¿ony z cyfr.
    Na przyk³ad, wywo³anie ListMnemonics("723")
    powinno wygenerowaæ nastêpuj±cych 27 trójek:

       PAD PBD PCD RAD RBD RCD SAD SBD SCD
       PAE PBE PCE RAE RBE RCE SAE SBE SCE
       PAF PBF PCF RAF RBF RCF SAF SBF SCF

    Jakie kombinacje liter s± przy cyfrach na telefonie
    komórkowym. Czy w tym wypadku Twoje rozwi±zanie 
    te¿ zadzia³a?
 */

#include <stdio.h>
#include <stdlib.h>

char telephone[] = "ABCDEFGHIJKLMNOPRSTUVWXZ";
int y;

void ListMnemonics(char *s, int *n);

void create(char *a,char *q,char *s, int *n, int *g){
  int z,i; 
  char *r;
  r=q;
  if (*a!='\0'){
    for (z=0;z<3;z++){
      if (*n>=2){
	*a=*(s+(*n-2)*3+z);
	create(a+1,q,s,n+1,g);
      }else {
	*a=' ';
	create(a+1,q,s,n+1,g);
      }
    }
    printf("\n");
  }else{
    for (i=0;i<y;i++){
      if (*r!=' ')
	printf("%c",*r);
      r++;
    }
    printf("\t");
    a--;
  }
      n=g;
      a--;
}


int main() {
  int numer[]={4,7,9,0};
  y=4;
  ListMnemonics(telephone,numer);
  return EXIT_SUCCESS;
}

void ListMnemonics(char *s, int *n) {
  char A[y];
  int x;
  for (x=0;x<y;x++)A[x]=1;
  A[y]='\0';
  create(A,A,s,n,n);
 
}
