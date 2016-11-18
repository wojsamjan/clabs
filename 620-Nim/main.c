/*  
 *  File: main.c
 *
 *  $Revision: 1.2 $
 *  $Date: 2004/01/12 09:40:01 $
 *
    Program ten symuluje grê w NIM, w której
    stos sk³ada siê z 13 ¿etonów.
    Dwaj gracze wykonuj± na przemian ruchy usuwaj±c
    ze stosu 1, 2 lub 3 ¿etony. Gracz, który
    zabiera ostatni ¿eton przegrywa. Drugim
    graczem jest komputer.
 */

#include <stdio.h>
#include <stdlib.h>
#include "nim.h"

#define InitialCoins 64
void GiveInstructions(void);

int main() 
{
  int nCoins, nTaken;
  playerT whoseTurn;

  GiveInstructions();
  nCoins=InitialCoins;
  whoseTurn=Human;
  while (nCoins>1) {
    printf("Liczba ¿etonów na stosie: %d.\n",nCoins);
    switch (whoseTurn) {
    case Human:
      nTaken=GetUserMove(nCoins);
      whoseTurn=Computer;
      break;
    case Computer:
      nTaken=ChooseComputerMove(nCoins);
      printf("Biorê %d.\n",nTaken);
      whoseTurn=Human;
      break;
    }
    nCoins-=nTaken;
  }
  AnnounceWinner(nCoins,whoseTurn);
  return EXIT_SUCCESS;
}

void GiveInstructions(void) 
{
  printf("Witam w grze w NIM!\n");
  printf("Zaczynamy grê ze stosem %d ¿etonów.\n",InitialCoins);
  printf("Ruchy wykonywane s± na przemian.\n");
  printf("W ka¿dym ruchu mo¿na zabraæ ze stosu od 1 do %d ¿etonów.\n",MaxTake);
  printf("Gracz, który zabierze ostatni ¿eton przegrywa.\n");
  printf("\n");
}
