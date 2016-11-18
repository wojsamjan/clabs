#ifndef MINIMAX_INCLUDED
#define MINIMAX_INCLUDED

#include "connect.h"

moveT FindBestMove(stateT state, int depth, int *pRating);

moveT EvaluatePosition(stateT state, int depth);

moveT ChooseComputerMove(stateT state);

#endif
