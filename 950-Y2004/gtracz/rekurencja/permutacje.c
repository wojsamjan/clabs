/*  
 *  File: permutacje3.c
 *
 *  $Revision: 1.1.1.1 $
 *  $Date: 2004/01/24 10:40:47 $
 *
   Wersja 3.
   Tym razem chcemy otrzymaæ co¶ takiego:
      ListPermutations("AABB") => AABB
                                  ABAB
                                  ABBA
                                  BAAB
                                  BABA
                                  BBAA
   Teraz podany napis mo¿e zawieraæ powtarzaj±ce
   siê litery. Funkcja rekurencyjna nie powinna
   generowaæ dodatkowych permutacji
 */

#include<stdio.h>
#include<string.h>

//text gdzie szukamy znaku
//i - index, gdzie w texcie jest aktualny znak
int FindNextChar(char *text,int i) 
{
  char c=text[i];//aktualny znak
  char *lastchr=strrchr(text,c);//ostatnie wystapienie tego znaku
  if(lastchr[1]==0) return -1;//jesli dalej nic nie ma-to byl ostatni znak
  return (int)(lastchr-text)+1; //zwraca index nastepnego znaku
}

//usuwa znak z textu z miejsca o indexie i i przesowa pozostale znaki na
//jego miejsce
char UsunZnak(char *text,int i)
{
  char c=text[i]; //usuwany znak
  while(text[i]!=0) {
    text[i]=text[i+1];
    ++i;
  }
  return c;
}

//"wsowa" znak ch do textu na i-ta pozycje
void DodajZnak(char *text,char ch,int i)
{
  int j;
  for(j=strlen(text);j>=i;--j) {
    text[j+1]=text[j];
  }
  text[i]=ch;
}

//generoje rekorsywnie permutacje bez powtozen na takiej zasadzie,
//ze wywoluje siebie tyle razy, ile jest roznych liter w zbiorze
//za kazdym razem dopisujac do napisu ta litere i jednoczesnie 
//usuwajac ja ze zbioru
void GenPermutation(char *napis,char *zbior)
{
  int i=0,len;
  char c;
  if(strlen(zbior)==0) { //koniec rekurencji - zuzyto wszystkie elementy
    printf("%s\n",napis);
    return;
  }
  len=strlen(napis);
  napis[len]=zbior[0]; //dopisanie na koniec napisu pierwszej litery
  napis[len+1]=0; //koniec napisu
  GenPermutation(napis,zbior+1);//podawany zbior jest bez pierwszej litery
  while( (i=FindNextChar(zbior,i))!=-1 ) { //dopoki sa nastepne inne litery
    napis[len]=zbior[i];
    c=UsunZnak(zbior,i);
    GenPermutation(napis,zbior); //opis jak we wstepie do tej funkcji
    DodajZnak(zbior,c,i);
  }
  napis[len]=0;  //koncowe skrocenie napisu (cofanie sie w rekurencji)
}

//zalozenie dla mojego algorytmu jest takie, ze zbior musi byc jakos
//uporzadkowany - tak, zeby te same litery byly obok siebie. 
//wiec je sortuje (babelkowo)
void SortujZbior(char *zbior)
{
  int i,chg=1;
  int len=strlen(zbior);
  char tmp;
  while(chg==1) {
    chg=0;
    for(i=1;i<len;++i) {
      if(zbior[i]<zbior[i-1]) {
	chg=1;
	tmp=zbior[i];
	zbior[i]=zbior[i-1];
	zbior[i-1]=tmp;
      }
    }
  }
}

int main(int l,char *arg[])
{
  char napis[10]="";
  char *zbior;
  char przyklad[]="AABB";
  if(l==1) zbior=przyklad;
  else zbior=arg[1];
  SortujZbior(zbior);
  GenPermutation(napis,zbior);
  return 0;
}
