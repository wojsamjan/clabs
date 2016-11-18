/*  
 *  File: minimax.c
 *
    Uniwersalne funkcje do ka¿dej gry zaimplementowanej
    za pomoc± algorytmu minimax.
 */

#include "minimax.h"

#define GAME_OVER 0
#define END 1

/*
 *  Funkcja prywatna.
 */

/*  Funkcja zwracaj±ca ocenê pozycji bez dalszego przegl±dania 
    drzewa gry. */ 

static float EvaluateStaticPosition(stateT state, int option);

/* Dla srednio zaawansowanego gracza ponizsze oceny nie powinny byc zaskoczeniem
 * pochodza one ze strony: http://sequoia.ict.pwr.wroc.pl/~witold/aiuwr/projekty_2001/reversi/ */
float oceny_pol[8][8] = {
	{53.15,	-32.97, 24.61, 24.61, 24.61, 24.61, -32.97, 53.15},
	{-32.97, -43.33, -26.26, -26.26, -26.26, -26.26, -43.33, -32.97},
	{24.61, -26.26, 1.04, 1.04, 1.04, 1.04, -26.26, 24.61},
	{24.61, -26.26, 1.04, 1.04, 1.04, 1.04, -26.26, 24.61},
	{24.61, -26.26, 1.04, 1.04, 1.04, 1.04, -26.26, 24.61},
	{24.61, -26.26, 1.04, 1.04, 1.04, 1.04, -26.26, 24.61},
	{-32.97, -43.33, -26.26, -26.26, -26.26, -26.26, -43.33, -32.97},
	{53.15, -32.97, 24.61, 24.61, 24.61, 24.61, -32.97, 53.15}
};

/*  Funkcja generuj±ca listê poprawnych ruchów mo¿liwych do
    wykonania z podanej pozycji. Lista ruchów zwracana jest
    w tablicy moveArray podanej i zaalokowanej przez
    klienta. Funkcja zwraca liczbê poprawnych ruchów. */

static int GenerateMoveList(stateT state, moveT moveArray[]);

/*
 *  Funkcje ekportowane.
 */

moveT FindBestMove(stateT state, int depth, float *pRating)
{
	moveT moveArray[MaxMoves], move, bestMove={-1,-1};
	int i, nMoves;
	float rating, minRating;
	char changes[8];

	nMoves=GenerateMoveList(state,moveArray);
	minRating=WinningPosition+1;

	if (nMoves==0)
	{   
		SwitchToOpponent(state);
		minRating=EvaluatePosition(state,depth+1);
		SwitchToOpponent(state);
	}
	else   
		for (i=0; i<nMoves && minRating!=LosingPosition; i++) {
			move=moveArray[i];
			MakeMove(state,move,changes);
			rating=EvaluatePosition(state,depth+1);
			if (rating<minRating) {
				bestMove=move;
				minRating=rating;
			}
			RetractMove(state, move, changes);
			//RetractMove(state, boardCopy);
		}

	*pRating=-minRating;
	return bestMove;
}

float EvaluatePosition(stateT state, int depth)
{
  float rating;

  if (GameIsOver(state))
    return EvaluateStaticPosition(state, GAME_OVER);
  if (depth>=MaxDepth) 
    return EvaluateStaticPosition(state, END);

  (void) FindBestMove(state,depth,&rating);
  return rating;
}

static int GenerateMoveList(stateT state, moveT moveArray[])
{
  int nMoves;
  moveT move;
  nMoves=0;
  for (move.y=1; move.y<=8; move.y++)
    for (move.x=1; move.x<=8; move.x++)	
       if (MoveIsLegal(move, state))
	  moveArray[nMoves++]=move;
  return nMoves;
}

moveT ChooseComputerMove(stateT state)
{
  float rating;
  moveT notMove={-1,-1};

  if (NoLegalMoves(state))
	  return notMove;

  return FindBestMove(state,0,&rating);
}

static int intMark(stateT state, moveT move, char mymark)
{
	char mark = BoardXY(state, move);
	if (mark == mymark) return 1;
	if (mark == ' ') return 0;
	return -1;
}


static float EvaluateStaticPosition(stateT state, int option)
{
	moveT move;
	float v=4.1;
	float note = 0;
	int c=0 ,b;
	char mymark = PlayerMark(WhoseTurn(state));
	if (option == GAME_OVER)
	{
		if (CheckForWin(state,state->whoseTurn)) 
			return WinningPosition;
		
		if (CheckForWin(state,Opponent(state->whoseTurn))) 
			return LosingPosition;
		
		return NeutralPosition;
	}
	else {
		for (move.y=1; move.y<=8; move.y++)
			for(move.x=1; move.x<=8; move.x++)
			{
				b=intMark(state, move, mymark);	
				note= note + b*oceny_pol[move.y-1][move.x-1];
			}

		for (move.y=1; move.y<=8; move.y++)
			for(move.x=1; move.x<=8; move.x++)
			{
				if (MoveIsLegal(move, state))
					c++;
			}
			note = note + c*v;		
	}
	return note;
}

