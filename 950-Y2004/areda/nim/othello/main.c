/*  
 *  File: main.c
 *
 *  Program graj±cy w Othello. 
 */

#include <stdio.h>
#include <stdlib.h>
#include "othello.h" 
#include "ui-othello.h"
#include "minimax.h"

int main()
{
  stateT state;
  moveT move;
  GiveInstructions();
  state=NewGame();
  while (!GameIsOver(state)) {
    DisplayGame(state);
    switch (WhoseTurn(state)) {
    case Human: 
      move=GetUserMove(state); 
      break;
    case Computer:
      move=ChooseComputerMove(state);
      DisplayMove(move);
      break;
    }
    MakeMove(state,move);
  }  
  AnnounceResults(state);
  return EXIT_SUCCESS;
}
