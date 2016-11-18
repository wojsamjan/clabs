/*  
 *  File: nim.h
 *
 *  $Revision: 1.1.1.1 $
 *  $Date: 2004/01/24 10:39:46 $
 *
    Interfejs do gry NIM.
 */

#ifndef NIM_INCLUDED
#define NIM_INCLUDED

/* Zaprojektowaæ. */
#include<stdio.h>
#include <ncurses/ncurses.h>

typedef enum {Computer, Human} stateT;

int stos[3+1];

typedef struct {
	int nr_stosu, liczba;
} moveT;

#define zetony1 3
#define zetony2 4
#define zetony3 5
#define kto_zaczyna Human
//#define kto_zaczyna Computer
#define rek_depth 9  /* tu definiujemy glebokosc rekursji*/

void GiveInstructions(void);

stateT NewGame(void);

int GameIsOver(void);

void DisplayGame(void);

moveT GetUserMove(void);

int MoveIsLegal(moveT ruch);

void DisplayMove(moveT move);

void MakeMove(moveT move);

void AnnounceResults(stateT state);

moveT ChooseComputerMove();

#endif
