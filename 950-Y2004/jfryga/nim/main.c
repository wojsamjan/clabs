
#include <stdio.h>
#include "nim.h"


void GiveInstructions(void);


int main() {
 
  stos.r[1]=3;
  stos.r[2]=4;
  stos.r[3]=5;
  GiveInstructions();
  whoseTurn=Human;
  while ((stos.r[1] + stos.r[2] + stos.r[3])>1) {
    pokaz(stos.r);
    switch (whoseTurn) {
    case Human:
      ile = GetUserMove(stos.r);
      whoseTurn = Computer;
      break;
    case Computer:
      ile = ChooseComputerMove(stos.r);
      printf("\nZe stosu %d, zabieram %d zetonow.\n",ile.nKtory, ile.nTaken);
      whoseTurn = Human;
      break;
    }
    stos.r[ile.nKtory] -= ile.nTaken;
  }
  AnnounceWinner((stos.r[1] + stos.r[2] + stos.r[3]), whoseTurn);
  return 0;
}

void GiveInstructions(void) 
{
  printf("Witam w grze w NIM!\n");
  printf("Zetony ulozone sa w nastepujacy sposob:\n\n");
  printf("rzad 1:  o o o \n");
  printf("rzad 2:  o o o o\n");
  printf("rzad 3:  o o o o o\n\n");
  printf("W jednym ruchu mozna zabrac dowolna liczbe zetonow, pod warunkiem,\n");
  printf("ze wszystkie zabierane zetony znajduja sie w tym samym rzedzie.\n");
  printf("\n");
  printf("Gracz, ktory zabierze ostatni zeton przegrywa.\n");
  }

