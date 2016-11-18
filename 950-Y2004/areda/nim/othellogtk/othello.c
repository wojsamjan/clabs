/*  
 *  File: othello.c
 *
    Implementacja interfejsu do gry w "Othello".
 */

#include "othello.h"
#include <string.h>

stateT NewGame(void)
{
  stateT state;
  state = malloc(sizeof(*((stateT)NULL)));

  strcpy(state->board[0], "##########");
  strcpy(state->board[1], "#        #");	  
  strcpy(state->board[2], "#        #");	  
  strcpy(state->board[3], "#        #");	  
  strcpy(state->board[4], "#   ox   #");	  
  strcpy(state->board[5], "#   xo   #");	  
  strcpy(state->board[6], "#        #");	  
  strcpy(state->board[7], "#        #");	  
  strcpy(state->board[8], "#        #");	  
  strcpy(state->board[9], "##########");
  
  state->whoseTurn=FirstPlayer;
  state->turnsTaken=0;
  return state;
}

void MakeMove(stateT state, moveT move, char *changes) {
	moveT adjMove;
	directionT dir;
	char pointMark;
	char opponentMark = PlayerMark(Opponent(WhoseTurn(state)));
	char myMark = PlayerMark(WhoseTurn(state));

	SwitchToOpponent(state);
	if (move.x == -1)
		return;
	state->turnsTaken++;
	state->board[move.y][move.x]=myMark;
	/* dla ka¿dego z kierunków */
	for (dir=0; dir<8; dir++)
	{
		changes[dir]=0;
		/* we¼ s±ssiednie pole */
		adjMove=AdjacentPoint(move, dir);
		/* je¶li jest to pole zajête przez przeciwnika, sprawdzaj dalej */
		if ( BoardXY(state, adjMove) ==  opponentMark)
		{
			while((pointMark=BoardXY(state, adjMove)) == opponentMark)
				adjMove=AdjacentPoint(adjMove, dir);
			/* je¶li za polami przeciwnika zjajduje sie moje pole, 
			 * zamieñ wszystkie te pola na moje */
			if (pointMark == myMark) 
			{
				adjMove=AdjacentPoint(move, dir);
				while(BoardXY(state, adjMove) == opponentMark)
				{
					state->board[adjMove.y][adjMove.x] = myMark;				
					adjMove=AdjacentPoint(adjMove, dir);
					changes[dir]++;
				}
			}		

		}
	}
}


void RetractMove(stateT state, moveT move, char *changes)
{
	int dir, i;
	char opponentMark;
	moveT adjMove;

	SwitchToOpponent(state);
	state->turnsTaken--;
	opponentMark = PlayerMark(Opponent(WhoseTurn(state)));
	state->board[move.y][move.x]=' ';
	for(dir=0; dir<8; dir++)
	{
		adjMove=AdjacentPoint(move, dir);
		for(i=0; i<changes[dir]; i++)
		{
			state->board[adjMove.y][adjMove.x]= opponentMark;
			adjMove=AdjacentPoint(adjMove, dir);
		}
	}
			
}


playerT WhoseTurn(stateT state)
{
  return state->whoseTurn;
}

bool GameIsOver(stateT state)
{
  bool noMoves1, noMoves2;

  if ((state->turnsTaken) >= MaxMoves) return true;
  noMoves1=NoLegalMoves(state);
  SwitchToOpponent(state);
  noMoves2=NoLegalMoves(state);
  SwitchToOpponent(state);
  
  return (noMoves1 && noMoves2);
}


bool CheckForWin(stateT state, playerT player)
{
  moveT pt;
  char mark;
  int myMarks=0, opponentMarks=0;
  char myMark = PlayerMark(player);
  char opponentMark = PlayerMark(Opponent(player));
  
  for (pt.y=1; pt.y<=8; pt.y++)
	 for(pt.x=1; pt.x<=8; pt.x++)
	 {
		 mark=BoardXY(state, pt);
		 if (mark == myMark)
			 myMarks++;
		 else if (mark == opponentMark)	
			 opponentMarks++;
	 }
  return (myMarks > opponentMarks);
}

playerT Opponent(playerT player)
{
  switch (player) {
  case Human: return Computer;
  case Computer: return Human;
  }
  return Computer;
}

void SwitchToOpponent(stateT state)
{
  state->whoseTurn=Opponent(WhoseTurn(state));
}

bool MoveIsLegal(moveT move, stateT state)
{
  moveT adjMove;
  directionT dir;
  char pointMark;
  char opponentMark = PlayerMark(Opponent(WhoseTurn(state)));
  char myMark = PlayerMark(WhoseTurn(state));

  if (move.x<1 || move.x>8 || move.y<1 || move.y>8)
	  return false;
  /* sprawd¼ czy pole jest wolne */
  if (state->board[move.y][move.x] != ' ')
    return false;
  /* sprawd¿ czy w którymkolwiek z kierunków pola zajête przez przeciwnika znajduj± siê
   * przed moimi */
  for (dir=0; dir<8; dir++)
  {
      /* we¼ s±ssiednie pole */
      adjMove=AdjacentPoint(move, dir);
      /* je¶li jest to pole zajête przez przeciwnika, sprawdzaj dalej */
      if (BoardXY(state, adjMove) ==  opponentMark)
      {
        while((pointMark=BoardXY(state, adjMove)) == opponentMark)
		adjMove=AdjacentPoint(adjMove, dir);
	if (pointMark == myMark) 
		return true;
      }
  }
  return false;
}	    
	  
bool NoLegalMoves(stateT state)
{
	moveT move;

	for(move.y=1; move.y<=8; move.y++)
		for(move.x=1; move.x<=8; move.x++)
	       		if(MoveIsLegal(move, state))
				 return false;
	return true;
}
