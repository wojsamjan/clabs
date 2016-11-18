/*  
 *  File: main.c
 *
 *  $Revision: 1.1.1.1 $
 *  $Date: 2004/01/24 10:40:34 $
 *
    Program ten symuluje grê w NIM, w której
    stos sk³ada siê z 13 ¿etonów.
    Dwaj gracze wykonuj± na przemian ruchy usuwaj±c
    ze stosu 1, 2 lub 3 ¿etony. Gracz, który
    zabiera ostatni ¿eton przegrywa. Drugim
    graczem jest komputer.
 */

#include <stdio.h>
#include "nim.h"

void GiveInstructions(void);
int tabb[NofRows+1] = {0, NofCoins, NofCoins, NofCoins};

void Kopiuj(int tab[], int tab2[]){
  int i;

  for(i = 0; i<=NofRows; i++)
    tab2[i] = tab[i];
    }

int main() {
  int nCoins, allCoins;
  /*int tab2[NofRows+1];*/
  rowsT ile;
  stosT stos;
  playerT whoseTurn;

  GiveInstructions();
  nCoins = NofCoins;
  allCoins = NofRows * NofCoins;
  Kopiuj(tabb, stos.tab);

  whoseTurn=Human;
  while (allCoins>1) {
    printf("Liczba ¿etonów na stosach: %d, %d, %d.\n",stos.tab[1], stos.tab[2], stos.tab[3]);
    switch (whoseTurn) {
    case Human:
      ile = GetUserMove(stos.tab);
      whoseTurn = Computer;
      break;
    case Computer:
      /*      Kopiuj(tab, tab2);*/
      ile = ChooseComputerMove(stos.tab);
      printf("Biorê z %d stosiku %d ¿eton(y).\n",ile.row, ile.number);
      whoseTurn = Human;
      break;
    }
    stos.tab[ile.row] -= ile.number;
    allCoins-=ile.number;
  }
  AnnounceWinner(allCoins, whoseTurn);
  return 0;
}

void GiveInstructions(void) 
{
  printf("Witam w grze w NIM!\n");
  printf("Zaczynamy grê z %d stosami %d ¿etonami na ka¿dym z nich.\n",NofRows, NofCoins);
  printf("Ruchy wykonywane s± na przemian.\n");
  printf("W ka¿dym ruchu mo¿na zabraæ ze stosu od 1 do %d ¿etonów.\n",MaxTake);
  printf("Gracz, który zabierze ostatni ¿eton przegrywa.\n");
  printf("\n");
}
