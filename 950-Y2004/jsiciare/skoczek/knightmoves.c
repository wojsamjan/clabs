/*
 * Plik: knightmoves.c
 * Wersja: 1.0
 * Data: 19.01.2004
 * Implementacja interfejsu do generowania ruchów skoczka na szachownicy.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define MOVES 40

static int PUSTE = 888;
static int chessboard[64];

typedef struct {
    int position;
    int abilities[8];
} skoczekT;

static skoczekT skoczek = { 0, {0, 0, 0, 0, 0, 0, 0, 0} };
static skoczekT stack[64];

static int *sPointer;
static int sPtr;
static int tmpP;

static int direction = -1, wybiera = 1;
static int ile_ruchow = MOVES;

static void Hetta(int *stackPointer);
static void CreateBoard(int position);
static int CheckAbilities(int *stackPointer);
static int MakeMove(int *stackPointer);


int * Wio(int start)
{
    int poczatek=start;
    sPtr = 0;
    sPointer = &sPtr;
	ile_ruchow-=1;

    CreateBoard(poczatek);

    stack[*sPointer].position = poczatek;
    CheckAbilities(sPointer);

    Hetta(sPointer);
    return chessboard;
}



static void Hetta(int *stackPointer)
{
    if (*stackPointer <= ile_ruchow) {
	if (CheckAbilities(stackPointer)) {
	    MakeMove(stackPointer);
	} else {
	    tmpP = *stackPointer;
	    while (*stackPointer > tmpP - (tmpP / 3)) {
		chessboard[stack[*stackPointer].position] = PUSTE;
		(*stackPointer)--;
	    }
	}

	Hetta(stackPointer);

   } else {
	return;
   }

}


static int MakeMove(int *stackPointer)
{
    int x, y;
    x = stack[*stackPointer].position % 8;
    y = stack[*stackPointer].position / 8;

    skoczek = stack[*stackPointer];

    if (CheckAbilities(stackPointer) == 0)
	return 0;

    srand(time(NULL));

    wybiera = 1;
    while (wybiera) {
	direction = (int) (8.0 * rand() / (RAND_MAX + 1.0));
	if (skoczek.abilities[direction])
	    wybiera = 0;
    }

    switch (direction) {
    case 0:
	chessboard[(x + 2) + (y + 1) * 8] = *stackPointer + 1;
	stack[*stackPointer].abilities[0] = 0;
	skoczek.position = (x + 2) + (y + 1) * 8;
	break;
    case 1:
	chessboard[(x + 2) + (y - 1) * 8] = *stackPointer + 1;
	stack[*stackPointer].abilities[1] = 1;
	skoczek.position = (x + 2) + (y - 1) * 8;
	break;
    case 2:
	chessboard[(x + 1) + (y - 2) * 8] = *stackPointer + 1;
	stack[*stackPointer].abilities[2] = 0;
	skoczek.position = (x + 1) + (y - 2) * 8;
	break;
    case 3:
	chessboard[(x - 1) + (y - 2) * 8] = *stackPointer + 1;
	stack[*stackPointer].abilities[3] = 0;
	skoczek.position = (x - 1) + (y - 2) * 8;
	break;
    case 4:
	chessboard[(x - 2) + (y - 1) * 8] = *stackPointer + 1;
	stack[*stackPointer].abilities[4] = 0;
	skoczek.position = (x - 2) + (y - 1) * 8;
	break;
    case 5:
	chessboard[(x - 2) + (y + 1) * 8] = *stackPointer + 1;
	stack[*stackPointer].abilities[5] = 0;
	skoczek.position = (x - 2) + (y + 1) * 8;
	break;
    case 6:
	chessboard[(x - 1) + (y + 2) * 8] = *stackPointer + 1;
	stack[*stackPointer].abilities[6] = 0;
	skoczek.position = (x - 1) + (y + 2) * 8;
	break;
    case 7:
	chessboard[(x + 1) + (y + 2) * 8] = *stackPointer + 1;
	stack[*stackPointer].abilities[7] = 0;
	skoczek.position = (x + 1) + (y + 2) * 8;
	break;
    }

    stack[++(*stackPointer)].position = skoczek.position;
    return 1;
}

static int CheckAbilities(int *stackPointer)
{
    int dir, x, y, stan = 0;
    x = stack[*stackPointer].position % 8;
    y = stack[*stackPointer].position / 8;

    for (dir = 0; dir < 8; dir++) {
	switch (dir) {
	case 0:
	    if (x + 2 < 8 && y + 1 < 8
		&& chessboard[(x + 2) + (y + 1) * 8] == PUSTE) {
		stack[*stackPointer].abilities[0] = 1;
		stan += 1;
	    } else {
		stack[*stackPointer].abilities[0] = 0;
	    }
	    break;
	case 1:
	    if (x + 2 < 8 && y - 1 >= 0
		&& chessboard[(x + 2) + (y - 1) * 8] == PUSTE) {
		stack[*stackPointer].abilities[1] = 1;
		stan += 1;
	    } else {
		stack[*stackPointer].abilities[1] = 0;
	    }
	    break;
	case 2:
	    if (x + 1 < 8 && y - 2 >= 0
		&& chessboard[(x + 1) + (y - 2) * 8] == PUSTE) {
		stack[*stackPointer].abilities[2] = 1;
		stan += 1;
	    } else {
		stack[*stackPointer].abilities[2] = 0;
	    }
	    break;
	case 3:
	    if (x - 1 >= 0 && y - 2 >= 0
		&& chessboard[(x - 1) + (y - 2) * 8] == PUSTE) {
		stack[*stackPointer].abilities[3] = 1;
		stan += 1;
	    } else {
		stack[*stackPointer].abilities[3] = 0;
	    }
	    break;
	case 4:
	    if (x - 2 >= 0 && y - 1 >= 0
		&& chessboard[(x - 2) + (y - 1) * 8] == PUSTE) {
		stack[*stackPointer].abilities[4] = 1;
		stan += 1;
	    } else {
		stack[*stackPointer].abilities[4] = 0;
	    }
	    break;
	case 5:
	    if (x - 2 >= 0 && y + 1 < 8
		&& chessboard[(x - 2) + (y + 1) * 8] == PUSTE) {
		stack[*stackPointer].abilities[5] = 1;
		stan += 1;
	    } else {
		stack[*stackPointer].abilities[5] = 0;
	    }
	    break;
	case 6:
	    if (x - 1 >= 0 && y + 2 >= 0
		&& chessboard[(x - 1) + (y + 2) * 8] == PUSTE) {
		stack[*stackPointer].abilities[6] = 1;
		stan += 1;
	    } else {
		stack[*stackPointer].abilities[6] = 0;
	    }
	    break;
	case 7:
	    if (x + 1 < 8 && y + 2 < 8
		&& chessboard[(x + 1) + (y + 2) * 8] == PUSTE) {
		stack[*stackPointer].abilities[7] = 1;
		stan += 1;
	    } else {
		stack[*stackPointer].abilities[7] = 0;
	    }
	    break;
	}
    }

    return stan;

}



static void CreateBoard(int position)
{
    int i;
    for (i = 0; i < 64; i++)
	chessboard[i] = PUSTE;
    chessboard[position] = 0;
}

