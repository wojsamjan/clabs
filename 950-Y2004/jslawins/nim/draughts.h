/* Jakub S³awiñski 13.12.2003 r.
 * plik nag³ówkowy dla programu graj±cego w warcaby
 * draughts.h
 */

#include <gtk/gtk.h>

#ifndef _JS_TEST_H
#define _JS_TEST_H

typedef struct {
	int x;
	int y;
} pointT;

typedef struct {
	pointT back;
	pointT pos;
	char type;
	char state;
	char legal;
} checkerT;
typedef struct {
	char board[8][8];
	checkerT checkers[24];
	char state;		
	char player;		
	pointT data;
	unsigned int reclevel;
	char newgamepending;
} chessboardT;			

void NewGame(void); /* starting a new game */
int is_outside(int x, int y); /* is this point outside the board */
int is_checker(int x, int y, char type); /* is this a checker of a checked type */
int is_allowed_move(int x, int y, int oldx, int oldy, char type); /* is this move legal? */
pointT square_centre(int x, int y); /* returns the coordinates of a centre of the square */
pointT board_square(int x, int y); /* returns the coordinates of a board square */
int OpponentMove(GtkWidget* widget); /* makes an opponent move */

#endif
