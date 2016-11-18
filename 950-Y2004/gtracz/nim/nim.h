/*  
 *  File: nim.h
 *
 *  $Revision: 1.1.1.1 $
 *  $Date: 2004/01/24 10:40:46 $
 *
    Interfejs do gry NIM.
 */


#ifndef NIM_INCLUDED
#define NIM_INCLUDED

#include <ncurses.h>

typedef struct{
  int rzad;
  int ile;
  int value;
} moveT;

typedef struct{
  int r1,r2,r3;
  int who;
} stateT;

typedef enum{
  Human, Computer
    } whoT;

//#include "minimax.h"



/* Zaprojektowaæ. */

void GiveInstructions(void);

stateT NewGame(void);

int GameIsOver(stateT state);

void DisplayGame(stateT state);

int WhoseTurn(stateT state);

moveT GetUserMove(stateT state);

void DisplayMove(moveT move);

stateT MakeMove(stateT state,moveT move);

void AnnounceResults(stateT state);

#endif
