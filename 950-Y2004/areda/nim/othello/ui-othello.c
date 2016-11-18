/*  
 *  File: ui-othello.c
 *
    Implementacja interfejsu u¿ytkownika do gry w "Othello".
 */

#include "othello.h"
#include "ui-othello.h"

/*  
 *  Funkcje ekportowane.
 */

void DisplayGame(stateT state)
{
  int row;
  if (GameIsOver(state)) {
    printf("\nPozycja koñcowa gry:\n\n");
  } else {
    printf("\nStan gry:\n\n");
  }
  
  printf("   ABCDEFGH\n");
  for (row=0; row<=9; row++) 
	  printf("%d %s\n", row,state->board[row]);
  printf("\n");
}

void DisplayMove(moveT move)
{
	if(move.x != -1)
		printf("Stawiam `%c' na polu (%d,%d).\n", PlayerMark(Computer),move.x, move.y);
	else
		printf("Nie moge wykonaæ ruchu");
}

moveT GetUserMove(stateT state)
{
  moveT move={-1,-1};

  if (NoLegalMoves(state))
  {
	  printf("Przykro mi ale nie mo¿esz wykonaæ ¿adnego ruchu.\n");
	  return move;
  }
  printf("Twój ruch.\n");
  while (TRUE) {
    printf("Na jakie pole? ");
    move.x=GetInteger();
    move.y=GetInteger();
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
  printf("Witam w grze Othello.\n");
}
