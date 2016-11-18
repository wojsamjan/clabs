
#include "minimax.h"
#include "connect.h"
#include "ui-connect.h"
#include <stdio.h>
#include <stdlib.h>
#include <ncurses/curses.h>

static int EvaluateStaticPosition(stateT state);

static int GenerateMoveList(stateT state, moveT moveArray[]);

moveT FindBestMove(stateT state, int depth, int *pRating) {
  
  moveT moveArray[10], move, bestMove = 4;
  int i, nMoves, rating, minRating;

    if(state->turnsTaken == 0){
    bestMove = 4;
    rating = 1000;
    goto yo;
    }
  
  if(state->turnsTaken == 2){
    bestMove = 5;
    rating = 1000;
    goto yo;
    }


     
  nMoves=GenerateMoveList(state,moveArray);
  minRating=WinningPosition+900023;
  for (i=1; i<=nMoves && minRating!=LosingPosition; i++) {
    move=moveArray[i];
    MakeMove(state,move);
    rating=EvaluatePosition(state,depth+1);

    if(rating == LosingPosition && depth == 0)
      rating += -10;
    if(rating == LosingPosition && depth == 2)
      rating += -5;
    /*if(rating == LosingPosition && depth == 2)
      rating += -9996;
    if(rating == LosingPosition && depth == 3)
      rating += -9992;
    if(rating == LosingPosition && depth == 4)
      rating += -9988;
    if(rating == LosingPosition && depth == 5)
    rating += -9984;*/

    if(rating == WinningPosition && depth == 0)
      rating += 30;
    /*if(rating == WinningPosition && depth == 1)
    rating += 6;*/
    /*    if(rating == WinningPosition && depth == 2)
      rating += 10000;
    if(rating == WinningPosition && depth == 3)
      rating +=100;
    if(rating == WinningPosition && depth == 4)
    rating +=10;*/
         
    if (rating<minRating) {
      bestMove = move;
      minRating = rating;
     }
     RetractMove(state,move);

     /*if(bestMove <4 && rating == 0)
       bestMove +=3;*/
   }
   *pRating=-minRating;
   yo:
   return bestMove;
}

moveT EvaluatePosition(stateT state, int depth)
{
  int rating;

  if (GameIsOver(state) || depth>=MaxDepth) {
    return EvaluateStaticPosition(state);
  }
  (void) FindBestMove(state,depth,&rating);
  return rating;
}

static int GenerateMoveList(stateT state, moveT moveArray[])
{
  int i, nMoves;
  nMoves=1;
  for (i=1; i<=7; i++) {
    if (state->board[i][WhereInCol(state, i)]==' ') {
      moveArray[nMoves++]=(moveT) i;
    }
  }
  if(nMoves == 0) nMoves = 1;
  return nMoves-1;
}

moveT ChooseComputerMove(stateT state)
{
  int rating;
  printf("Mój ruch.\n");
  return FindBestMove(state,0,&rating);
}


static int EvaluateStaticPosition(stateT state)
{
  if (CheckForWin(state,state->whoseTurn)) {
    return WinningPosition;
  }
  if (CheckForWin(state,Opponent(state->whoseTurn))) {
    return LosingPosition;
  }
  return NeutralPosition;
}
