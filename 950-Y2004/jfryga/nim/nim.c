

#include "nim.h"

/*  Funkcja zwraca TRUE jeli ze stosu, ktry zawiera 
    nCoins etonw mona pobra�nTaken etonw. */

static int MoveIsLegal(moveT ile, int tab[]);

/*  Dla podanej liczby etonw `nCoins' funkcja ta 
    szuka dobrego ruchu. Jeli w tej dla stosu
    etonw skadajcego si�z nCoins mona wykona�
    wygrywajcy ruch, to funkcja zwraca TRUE.
    W przeciwnym wypadku funkcja zwraca sta
    `NoGoodMove'.
    Jest to funkcja rekurencyjna. Rekurencja jest 
    tu wykorzystana do znalezienia dobrego ruchu,
    czyli ruchu stawiajcego przeciwnika w zej
    pozycji, gdzie za pozycja to taka pozycja
    w ktrej nie mona wykona�dobrego ruchu.
 */

static moveT FindGoodMove(int tab[]);

/*  Funkcja zwraca TRUE jeli liczba `nCoins' jest 
    z pozycj, gdzie z pozycj jest taka pozycja
    w ktrej nie mona wykona�dobrego ruchu.
    Jeli pozosta 1 eton, to taka pozycja oczywicie
    jest za. Reprezentuja ona przypadek prostym rekursji.
 */

static int IsBadPosition(int tab[]);

/* 
 *  Eksportowane funkcje 
 */


 
void AnnounceWinner(int nCoins , playerT whoseTurn)
{
  if (nCoins==0) {
    printf("Zabrales ostatni zeton i przegrales!\n");
  } else {
    printf("Pozostal jeden zeton.\n");
    switch (whoseTurn) {
    case Human: printf("Wygralem ;)\n\n"); break;
    case Computer: printf("Przegralem ;(\n\n"); break;
    }
  }
}

moveT GetUserMove(int tab[]) {
  moveT ruch;
  ruch.nKtory=0;
  ruch.nTaken=0;
  while (1) {
    while( (ruch.nKtory<1) || (ruch.nKtory>3) || (tab[ruch.nKtory]==0))
     {
      printf("ktory stos ? ");
      ruch.nKtory=GetInteger();
     }
    printf("ile zetonow ? ");
    ruch.nTaken=GetInteger();
    if (MoveIsLegal(ruch, tab))
      break;
    printf("nie mozesz tyle wziac\n");
  }
  return ruch;
}

moveT ChooseComputerMove(int tab[])
{
  moveT ruch;
  ruch = FindGoodMove(tab);
  if (ruch.nTaken == NoGoodMove)
  {
    while(tab[ruch.nKtory]==0) 
     {
       ruch.nKtory++;
       if(ruch.nKtory>3) ruch.nKtory=0;
     }
    ruch.nTaken = 1;
  }
  return ruch;
}

/* 
 *  Prywatne funkcje tego interfejsu.
 */

static int MoveIsLegal(moveT ile, int tab[]) {
  if ((ile.nKtory>0) && (ile.nKtory<=3) && (ile.nTaken>0) && (tab[ile.nKtory]-ile.nTaken>=0))
   return 1;
  else
  return 0; 
}

static moveT FindGoodMove(int tab[])
{
  int nKtory,nTaken;
  moveT ruch;
  int temp;
   for (nKtory = 1; nKtory<=3; nKtory++)
   {
    for (nTaken = 1; nTaken<=5; nTaken++)
    {
      ruch.nKtory = nKtory;
      ruch.nTaken = nTaken;
      temp = tab[ruch.nKtory]; 
      if (MoveIsLegal(ruch, tab))
      {
        tab[ruch.nKtory] -= ruch.nTaken;
        if(IsBadPosition(tab))
        {
          tab[ruch.nKtory] = temp;
          return ruch;
        }
      tab[ruch.nKtory] = temp;
      }
      tab[ruch.nKtory] = temp;
    }
  }
  ruch.nKtory = 1;
  ruch.nTaken = NoGoodMove;
  return ruch;
}

void pokaz(int tab[])
{
    printf("\nLiczba zetonow na stosach:\n%d\n%d\n%d\n",stos.r[1], stos.r[2], stos.r[3]);
    
}

static int IsBadPosition(int tab[]){
  moveT n,ruch;
  n.nKtory = 1;
  n.nTaken = NoGoodMove;
  if ((tab[1] + tab[2] + tab[3])== 1) 
    return 1;
  ruch = FindGoodMove(tab);
  if((ruch.nKtory==n.nKtory) && (ruch.nTaken==n.nTaken))
   return 1;
  else
   return 0;
}


