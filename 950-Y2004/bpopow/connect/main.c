/*  
 *  File: main.c
 *
 *  $Revision: 1.1.1.1 $
 *  $Date: 2004/01/24 10:40:30 $
 *
    Program graj±cy w CONNECT 4.
    W tej implementacji analizowane s± wszystkie ruchy.
 */

#include <stdio.h>
#include <stdlib.h>
#include "connect.h" 
#include "ui-connect.h"
#include "minimax.h"
#include <ncurses/curses.h>
 /*#include <genlib.h>*/

int main()
{
  stateT state;
  moveT move;
  int wybor;

  /*initscr();
  start_color();
  init_pair(1, COLOR_YELLOW, COLOR_BLACK);
  init_pair(2, COLOR_RED, COLOR_BLACK);
  init_pair(3, COLOR_WHITE, COLOR_BLACK);

  color_set(3,0);*/
  system("clear");
  GiveInstructions();

  printf("\n\n1. Gra z komputerem.\n");
  printf("2. Dwóch graczy.\n\n");
  printf("Wybór: ");
  wybor = WezLiczbe();

  /*  refresh();*/
  state=NewGame();
  while (!GameIsOver(state)) {
    DisplayGame(state);
    /*    refresh();*/
    switch (WhoseTurn(state)) {
    case Human: 
      move=GetUserMove(state); 
      break;
    case Computer:
      switch(wybor){
      case 1:
	move=ChooseComputerMove(state);
	DisplayMove(move);
	break;
      case 2:
	move = GetUserMove(state);     
	break;
      }
      /*refresh();*/
      break;
    }
    MakeMove(state,move);
  }
  AnnounceResults(state);
  /* endwin();*/
  return 0;
}
