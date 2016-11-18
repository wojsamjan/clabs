/*  
 *  File: ui-kik.c
 *
 *  $Revision: 1.1 $
 *  $Date: 2003/10/20 07:12:50 $
 *
    Implementacja interfejsu u¿ytkownika do gry w kó³ko i krzy¿yk.
 */

#include "kik.h"
#include "ui-kik.h"

/*  
 *  Funkcja prywatna.
 */

/*  Funkcja zwraca TRUE je¶li w podanym stanie mo¿na 
    wykonaæ poprawny ruch. */

static bool MoveIsLegal(moveT move, stateT state);

/*  
 *  Funkcje ekportowane.
 */

void DisplayGame(stateT state)
{
  int row, col;
  if (GameIsOver(state)) {
    printf("\nPozycja koñcowa gry:\n\n");
  } else {
    printf("\nStan gry:\n\n");
  }
  for (row=0; row<3; row++) {
    if (row!=0)
      printf("---|---|---\n");
    for (col=0; col<3; col++) {
      if (col!=0)
	printf("|");
      printf(" %c ",state->board[row*3+col+1]);
    }
    printf("\n");
  }
  printf("\n");
}

void DisplayMove(moveT move)
{
  printf("Stawiam `%c' na polu %d.\n",
	 PlayerMark(Computer),move);
}

char PlayerMark(playerT player)
{
  if (player==FirstPlayer)
    return 'x';
  else
    return 'o';
}

static bool MoveIsLegal(moveT move, stateT state)
{
  return move>=1 && move<=9 && state->board[move]==' ';
}

moveT GetUserMove(stateT state)
{
  moveT move;
  printf("Twój ruch.\n");
  while (TRUE) {
    printf("Na jakie pole? ");
    move=GetInteger();
    if (MoveIsLegal(move,state))
      break;
    printf("Tego ruchu nie mo¿esz wykonaæ. Spróbuj jeszcze raz.\n");
  }
  return move;
}

void AnnounceResults(stateT state)
{
  DisplayGame(state);
  if (CheckForWin(state,Human)) {
    printf("Wygra³e¶;(\n");
  } else if (CheckForWin(state,Computer)) {
    printf("Wygra³em;)\n");
  } else {
    printf("Remis.\n");
  }
}

void GiveInstructions(void) 
{
  printf("Witam w grze w kó³ko i krzy¿yk.\n");
}
