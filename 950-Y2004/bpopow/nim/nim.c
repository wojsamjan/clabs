/*  
 *  File: nim.c
 *
 *  $Revision: 1.1.1.1 $
 *  $Date: 2004/01/24 10:40:34 $
 *
    Implementacja interfejsu do gry w NIM.
 */

#include "nim.h"

/*  Funkcja zwraca TRUE je¶li ze stosu, który zawiera 
    nCoins ¿etonów mo¿na pobraæ nTaken ¿etonów. */

static int MoveIsLegal(rowsT ile, int tab[]);

/*  Dla podanej liczby ¿etonów `nCoins' funkcja ta 
    szuka dobrego ruchu. Je¶li w tej dla stosu
    ¿etonów sk³adaj±cego siê z nCoins mo¿na wykonaæ
    wygrywaj±cy ruch, to funkcja zwraca TRUE.
    W przeciwnym wypadku funkcja zwraca sta³±
    `NoGoodMove'.
    Jest to funkcja rekurencyjna. Rekurencja jest 
    tu wykorzystana do znalezienia dobrego ruchu,
    czyli ruchu stawiaj±cego przeciwnika w z³ej
    pozycji, gdzie z³a pozycja to taka pozycja
    w której nie mo¿na wykonaæ dobrego ruchu.
 */

static rowsT FindGoodMove(int tab[]);

/*  Funkcja zwraca TRUE je¶li liczba `nCoins' jest 
    z³± pozycj±, gdzie z³± pozycj± jest taka pozycja
    w której nie mo¿na wykonaæ dobrego ruchu.
    Je¶li pozosta³ 1 ¿eton, to taka pozycja oczywi¶cie
    jest z³a. Reprezentuja ona przypadek prostym rekursji.
 */

static int IsBadPosition(int tab[]);

/* 
 *  Eksportowane funkcje 
 */

void AnnounceWinner(int nCoins , playerT whoseTurn)
{
  if (nCoins==0) {
    printf("Zabra³e¶ ostatni ¿eton i przegra³e¶!\n");
  } else {
    printf("Pozosta³ jeden ¿eton.\n");
    switch (whoseTurn) {
    case Human: printf("Wygra³em ;)\n"); break;
    case Computer: printf("Przegra³em ;(\n"); break;
    }
  }
}

rowsT GetUserMove(int tab[]) {
  rowsT ile;

  while (1 == 1) {
    printf("Z którego stosiku? ");
    scanf("%d",&(ile.row));

    printf("Ile ¿etonów zabierasz? ");
    /*    nTaken=GetInteger();*/
    scanf("%d",&(ile.number));

    if (MoveIsLegal(ile, tab))
      break;
    printf("Oszukujesz!\n");
    printf("Mo¿esz zabraæ od 1 do 3 ¿etonów.\n");
    printf("Liczba ¿etonów na stosach: %d, %d, %d.\n",tab[1], tab[2], tab[3]);
  }
  return ile;
}

rowsT ChooseComputerMove(int tab[])
{
  rowsT ile;

  ile = FindGoodMove(tab);
  if (ile.number == NoGoodMove)
    ile.number = 1;
  return ile;
}

/* 
 *  Prywatne funkcje tego interfejsu.
 */

static int MoveIsLegal(rowsT ile, int tab[]) {
  int warunek1, warunek2, warunek3;

  warunek1 = (ile.row>0 && ile.row<=NofRows);
  warunek2 = (ile.number>0 && ile.number<=MaxTake);
  warunek3 = (ile.number<=tab[ile.row]);

  /*  printf("%d\n", watunek3);*/

  return (warunek1 && warunek2 && warunek3);
}

static rowsT FindGoodMove(int tab[])
{
  int i,j;
  rowsT ile;
  int temp;

  for (i = 1; i<=NofRows; i++){
    for (j = 1; j<=MaxTake; j++){
      ile.row = i;
      ile.number = j;
      temp = tab[ile.row]; /*!!!!!!!!!!*/

      if (MoveIsLegal(ile, tab)){
	/*	printf("Legalny dla %d i %d\n",tab[ile.row],ile.number);*/
	tab[ile.row] -= ile.number;
	if(IsBadPosition(tab)){
	/*  && IsBadPosition(tab)){*/
	tab[ile.row] = temp;
	return ile;	
	}
      tab[ile.row] = temp;
      }
      /*      else printf("Nielegalny dla %d i %d\n",tab[ile.row],ile.number);*/
      tab[ile.row] = temp;
    }
  }
  ile.row = 1;
  ile.number = NoGoodMove;
  /*  while(MoveIsLegal(ile, tab)==1)
      (ile.row)++;*/
  return ile;
}

static int IsBadPosition(int tab[]){
  int warunek1, warunek2;
  rowsT wzor,wynik;
  wzor.row = 1;
  wzor.number = NoGoodMove;

  /*  Wypis(tab);*/

  if (tab[1] + tab[2] + tab[3] == 1) 
    return 1;
  /*  return (FindGoodMove(tab) == wzor);*/
  wynik = FindGoodMove(tab);
  warunek1 = (wynik.row == wzor.row);
  warunek2 = (wynik.number == wzor.number);
  return (warunek1 && warunek2);
}

void Wypis(int tab[]){
  int i;

  for(i = 1; i<=3; i++)
    printf("%d: %d   ",i,tab[i]);
  printf("\n");
}
