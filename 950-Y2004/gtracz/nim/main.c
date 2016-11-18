/*  
 *  Plik: main.c
 *
 *  $Revision: 1.1.1.1 $
 *  $Date: 2004/01/24 10:40:46 $
 *
    Funkcja g³ówna do gry NIM.
 
    Zadanie:
      Zaimplementowaæ interfejs `minimax.h' oraz 
      zaprojektowaæ i zaimplementowaæ interfejs `nim.h',
      tak aby po skonsolidowaniu z funkcj± main
      powsta³ dzia³aj±cy program.
 */
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
//#include "nim.h"
#include "minimax.h"

static void MakeParity(void);

int main()
{
  stateT state;
  moveT move;
  initscr();
  if (has_colors()==1){
    start_color();
    MakeParity();
    attrset(COLOR_PAIR(1));
  }
  GiveInstructions();
  clear();
  state=NewGame();
  DisplayGame(state);
  while (GameIsOver(state)==0) {
    switch (WhoseTurn(state)) {
    case Human: 
      move=GetUserMove(state); 
      break;
    case Computer:
      move=ChooseComputerMove(state);
      DisplayMove(move);
      break;
    }
    state=MakeMove(state,move);
  }  
  AnnounceResults(state);
  getch();
  endwin();
  return EXIT_SUCCESS;
}

static void MakeParity(void){
  init_pair(1, COLOR_WHITE, COLOR_BLACK);
  init_pair(2, COLOR_BLUE, COLOR_BLACK);
  init_pair(3, COLOR_BLACK, COLOR_YELLOW);
  init_pair(4, COLOR_BLACK, COLOR_GREEN);
  init_pair(5, COLOR_BLACK, COLOR_RED);
}
