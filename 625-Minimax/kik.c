/*  
 *  File: kik.c
 *
 *  $Revision: 1.1 $
 *  $Date: 2003/10/20 07:12:50 $
 *
    Implementacja interfejsu do gry w kó³ko i krzy¿yk.
 */

#include "genlib.h"
#include "kik.h"
#include "ui-kik.h"

/*  W tej tablicy zapamiêtujemy wszystkie linie
    wygrywaj±ce. Chocia¿ ³atwo jest je obliczyæ w trakcie
    gry, ale tutaj u³atwiamy sobie nieco kodowanie. */

int winningLines[][3] = {
  { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 },
  { 1, 4, 7 }, { 2, 5, 8 }, { 3, 6, 9 },
  { 1, 5, 9 }, { 3, 5, 7 } 
};

int nWinningLines = sizeof winningLines / sizeof winningLines[0];

stateT NewGame(void)
{
  stateT state;
  int i;

  state=New(stateT);
  for (i=1; i<=9; i++) {
    state->board[i]=' ';
  }
  state->whoseTurn=FirstPlayer;
  state->turnsTaken=0;
  return state;
}

void MakeMove(stateT state, moveT move) {
  state->board[move]=PlayerMark(state->whoseTurn);
  state->whoseTurn=Opponent(state->whoseTurn);
  state->turnsTaken++;
}

void RetractMove(stateT state, moveT move)
{
  state->board[move]=' ';
  state->whoseTurn=Opponent(state->whoseTurn);
  state->turnsTaken--;
}

playerT WhoseTurn(stateT state)
{
  return state->whoseTurn;
}

bool GameIsOver(stateT state)
{
  return state->turnsTaken==9 || CheckForWin(state,state->whoseTurn)
    || CheckForWin(state,Opponent(state->whoseTurn));
}

/*  Sprawdzaj±c czy turnsTaken<5 przyspiesza dzia³anie programu,
    poniewa¿ ¿aden z graczy nie mo¿e wygraæ przed wykonaniem
    pi±tego ruchu. */

bool CheckForWin(stateT state, playerT player)
{
  int i;
  char mark;

  if (state->turnsTaken<5)
    return FALSE;
  mark=PlayerMark(player);
  for (i=0; i<nWinningLines; i++) {
    if (mark==state->board[winningLines[i][0]]
	&& mark==state->board[winningLines[i][1]]
	&& mark==state->board[winningLines[i][2]]) {
	  return TRUE;
	}
  }
  return FALSE;
}

playerT Opponent(playerT player)
{
  switch (player) {
  case Human: return Computer;
  case Computer: return Human;
  }
  return Computer;
}
