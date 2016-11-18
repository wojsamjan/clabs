#ifndef NIM_INCLUDED
#define NIM_INCLUDED

#include<stdio.h>
#include"main.h"

extern int rek_depth;

int GameIsOver(void);
int MoveIsLegal(moveT ruch);
void MakeMove(moveT move);
moveT ChooseComputerMove();

#endif
