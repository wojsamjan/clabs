#ifndef UI_KIK_INCLUDED
#define UI_KIK_INCLUDED

#include "connect.h"


void GiveInstructions(void);

void DisplayGame(stateT state);

moveT GetUserMove(stateT state);

void DisplayMove(moveT move);

void AnnounceResults(stateT state);

char PlayerMark(playerT player);

#endif
