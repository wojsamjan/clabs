/*  
 *  File: nim.c
 *
 *  $Revision: 1.3 $
 *  $Date: 2004/01/12 09:40:01 $
 *
    Implementacja interfejsu do gry w NIM.
 */

#include "nim.h"

/*  Funkcja zwraca TRUE je¶li ze stosu, który zawiera 
    nCoins ¿etonów mo¿na pobraæ nTaken ¿etonów. */

static bool MoveIsLegal(int nTaken, int nCoins);

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

static int FindGoodMove(int nCoins);

/*  Funkcja zwraca TRUE je¶li liczba `nCoins' jest 
    z³± pozycj±, gdzie z³± pozycj± jest taka pozycja
    w której nie mo¿na wykonaæ dobrego ruchu.
    Je¶li pozosta³ 1 ¿eton, to taka pozycja oczywi¶cie
    jest z³a. Reprezentuja ona przypadek prostym rekursji.
 */

static bool IsBadPosition(int nCoins);

/* 
 *  Eksportowane funkcje 
 */

void AnnounceWinner(int nCoins, playerT whoseTurn)
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

int GetUserMove(int nCoins)
{
  int nTaken, limit;
  while (TRUE) {
    printf("Ile ¿etonów zabierasz? ");
    nTaken=GetInteger();
    if (MoveIsLegal(nTaken,nCoins))
      break;
    limit=(nCoins<MaxTake) ? nCoins : MaxTake;
    printf("Oszukujesz!\n");
    printf("Mo¿esz zabraæ od 1 do %d ¿etonów.\n",limit);
    printf("Liczba ¿etonów na stosie: %d.\n",nCoins);
  }
  return nTaken;
}

int ChooseComputerMove(int nCoins)
{
  int nTaken;
  nTaken=FindGoodMove(nCoins);
  if (nTaken==NoGoodMove)
    nTaken=1;
  return nTaken;
}

/* 
 *  Prywatne funkcje tego interfejsu.
 */

static bool MoveIsLegal(int nTaken, int nCoins)
{
  return nTaken>0 && nTaken<=MaxTake && nTaken<=nCoins;
}

static int FindGoodMove(int nCoins)
{
  int nTaken;
  for (nTaken=1; nTaken<=MaxTake; nTaken++)
    if (MoveIsLegal(nTaken,nCoins) &&
	IsBadPosition(nCoins-nTaken))
      return nTaken;
  return NoGoodMove;
}

static bool IsBadPosition(int nCoins)
{
  if (nCoins==1) 
    return TRUE;
  return (FindGoodMove(nCoins)==NoGoodMove);
}
