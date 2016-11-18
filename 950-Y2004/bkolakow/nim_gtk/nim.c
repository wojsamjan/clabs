#include"nim.h"

int GameIsOver(void)
{
    if ((stos[1] + stos[2] + stos[3]) > 1)
	return 0;
    return 1;
}

int MoveIsLegal(moveT ruch)
{
    if (stos[ruch.nr_stosu] >= ruch.liczba && 1 <= ruch.liczba)
	return 1;
    else
	return 0;
}

void MakeMove(moveT move)
{
    stos[move.nr_stosu] -= move.liczba;
}
