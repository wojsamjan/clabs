/*  
 *  File: main.c
 *
 *  $Revision: 1.2 $
 *  $Date: 2003/10/20 07:12:50 $
 *
    Program graj±cy w kó³ko i krzy¿yk.
    W tej implementacji analizowane s± wszystkie ruchy.
 */

#include <stdio.h>
#include <stdlib.h>
#include "kik.h" 
#include "ui-kik.h"
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
