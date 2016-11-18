/* Jakub S³awiñski 13.12.2003 r.
 * plik implementuj±cy funkcje dla obs³ugi warcabów
 * draugfun.c
 */

#include "draughts.h"
#include <unistd.h>
#include "dramm.h"
#include "dragraph.h"
#include <string.h>

extern chessboardT board;

/* is_checker
 * funkcja zwraca numer piona w tablicy pionów
 */

int
is_checker(int x, int y, char type)
{
	int i;
	for ( i = 0; i < 24; ++i) {
		if (board.checkers[i].type == 0) {
			continue; /* this checker is not on a board */
		}
		if ((x < board.checkers[i].pos.x - 20) || (x > board.checkers[i].pos.x + 20)) {
			continue;
		}
		if ((y < board.checkers[i].pos.y - 20) || (y > board.checkers[i].pos.y + 20)) {
			continue;
		}
		break;
	}
	if (type == 0) {
		return i;
	}
	if (type == 1) {
		if (i < 12) {
			return i;
		}
		else {
			return 24;
		}
	}
	else {
		if (i < 12) {
			return 24;
		}
		else {
			return i;
		}
	}
}

/* is_outside
 * funkcja zwraca, czy dany punkt jest w obszarze drawing_area
 */

int
is_outside(int x, int y)
{
	if (x < 0 || x >= 400)
		return 1;
	if (y < 0 || y >= 400)
		return 1;
	return 0;
}

/* is_white_square
 * funkcja zwraca, czy dany punkt le¿y na bia³ym polu
 */

static int
is_white_square(int x, int y)
{
	if ( ((x / 50)%2) == ((y / 50)%2) )  {
		return 1;
	}
	return 0;
}

/* is_allowed_move
 * funkcja zwraca, czy dany ruch jest dozwolony
 */

int
is_allowed_move(int x, int y, int oldx, int oldy, char type)
{
	nodeT* moves = NULL;
	nodeT* iterator;
	pointT npos, oldpos;
	if (is_outside(x, y))
		return 0;
	if (is_white_square(x, y))
		return 0;
	oldpos = board_square(oldx, oldy);
	npos   = board_square(x, y);
	if (board.board[npos.x][npos.y] != 0)
		return 0;
	if (board.state == 0) {
		board.data = oldpos;
	}
	moves = find_all_moves(board.board, board.player, type);
	sortlist(&moves);
	cutlist(moves);
	iterator = moves;
	while (iterator) {
		if (iterator->move.lmoves) {
			if ((npos.x==iterator->move.moves[1].newx) &&
					 (npos.y==iterator->move.moves[1].newy)){
				return type;
			}
		}
		else {
			if ((npos.x==iterator->move.moves[0].newx) &&
					 (npos.y==iterator->move.moves[0].newy)){
				return type - 1;
			}
		}
		iterator = iterator->next;
	}
	freelist(&moves);
	return 0;
		
}

/* NewGame
 * funkcja doprowadza planszê do stanu pocz±tkowego
 */

void
NewGame()
{
	int i, j;
	int wn, rn;
	nodeT* moves = NULL;
	nodeT* iterator;
	pointT square;
	
	/* state of the game */
	board.state = 0;
	board.player = 2;
	board.newgamepending = 1;
	
	memset(board.board, 0, 8 * 8 * sizeof(char));
	clear_moves_list();
	
	/* red checkers */
	board.board[1][0] = board.board[3][0] = board.board[5][0] = board.board[7][0] =
	board.board[0][1] = board.board[2][1] = board.board[4][1] = board.board[6][1] =
	board.board[1][2] = board.board[3][2] = board.board[5][2] = board.board[7][2] = 1;

	/* white checkers */
	board.board[0][5] = board.board[2][5] = board.board[4][5] = board.board[6][5] =
	board.board[1][6] = board.board[3][6] = board.board[5][6] = board.board[7][6] =
	board.board[0][7] = board.board[2][7] = board.board[4][7] = board.board[6][7] = 2;

	wn = 0;
	rn = 12;
	for (i = 0; i < 8; ++i) {
		for (j = 0; j < 8; ++j) {
			if (board.board[i][j] == 1) { /* red */
				board.checkers[wn].back.x = i * 50 + 25;
				board.checkers[wn].back.y = j * 50 + 25;
				board.checkers[wn].pos = board.checkers[wn].back;
				board.checkers[wn].type = 1; /* normal red checker */
				board.checkers[wn].state = 0;
				board.checkers[wn].legal = 0;
				++wn;
			}
			if (board.board[i][j] == 2) { /* white */
				board.checkers[rn].back.x = i * 50 + 25;
				board.checkers[rn].back.y = j * 50 + 25;
				board.checkers[rn].pos = board.checkers[rn].back;
				board.checkers[rn].type = 2; /* normal white checker */
				board.checkers[rn].state = 0;
				board.checkers[rn].legal = 0;
				++rn;
			}

		}
	}
	moves = find_all_moves(board.board, board.player, 0);
	sortlist(&moves);
	cutlist(moves);
	iterator = moves;
	while (iterator) {
		square.x = iterator->move.moves[0].oldx;
		square.y = iterator->move.moves[0].oldy; 
		legalize_move(square.x, square.y);
		iterator = iterator->next;
	}
	freelist(&moves);
}

/* square_centre
 * funkcja zwraca wspó³rzêdne ¶rodka pola
 */

pointT
square_centre(int x, int y)
{
        pointT centre;
        int xb, yb;
        xb = (x / 50);
        yb = (y / 50);
        centre.x = xb * 50 + 25;
        centre.y = yb * 50 + 25;
        return centre;
}

/* board_square
 * funkcja zwraca wspó³rzêdne pola na szachownicy
 */

pointT
board_square(int x, int y)
{
        pointT centre;
        centre.x = x / 50;
        centre.y = y / 50;
        return centre;
}

/* find_checker_by_square
 * funkcja zwraca numer piona stoj±cego na danym polu
 */

int
find_checker_by_square(int x, int y)
{
	int i;
	for (i = 0; i < 24; ++i) {
		if (board.checkers[i].type == 0)
			continue;
	  if ((board_square(board.checkers[i].back.x, board.checkers[i].back.y).x == x) &&
	     (board_square(board.checkers[i].back.x, board.checkers[i].back.y).y == y)) {
		  break;
	  }
	}
	return i;
}

/* OpponentMove
 * funkcja odpowiedzialna za ruch przeciwnika (komputera)
 */

int
OpponentMove(GtkWidget* widget)
{
	int i, j;
	gchar* msg;
	moveT move;
	pointT testpos;
	pointT delta;
	nodeT* moves = NULL;
	nodeT* iterator;
	pointT square;
	
	unlegalize_moves();
	board.player = (board.player % 2) + 1; /* computer move */
	if (!are_legal_moves()) {
		announce_result( widget, board.player + 4);
               	msg = g_strdup_printf("  X  ");
	        insert_to_list(msg, 0);
	        g_free(msg);
		return 1;
	}
	
	move = make_computer_move();
	if (board.newgamepending)
		return 1;
	if (move.lmoves == 0) {
		testpos.x = move.moves[0].oldx;
		testpos.y = move.moves[0].oldy;
		i = find_checker_by_square(testpos.x, testpos.y);
		board.board[testpos.x][testpos.y] = 0;
		redraw_square(widget, testpos.x, testpos.y);
		testpos.x = move.moves[0].newx;
		testpos.y = move.moves[0].newy;
		msg = g_strdup_printf("%c%c - %c%c", move.moves[0].oldx+'A', '8'-move.moves[0].oldy,
				move.moves[0].newx+'A', '8'-move.moves[0].newy);
		insert_to_list(msg, 1);
		g_free(msg);
		if (testpos.y == 7) {
			if (board.checkers[i].type != 3) {
				board.checkers[i].type = 3;
	                        msg = g_strdup_printf("--> Queen");
	                        insert_to_list(msg, 0);
	                        g_free(msg);
			}									
		}
		board.board[testpos.x][testpos.y] = board.checkers[i].type;
		board.checkers[i].back.x = board.checkers[i].pos.x = testpos.x * 50 + 25;
		board.checkers[i].back.y = board.checkers[i].pos.y = testpos.y * 50 + 25;
		redraw_square(widget, testpos.x, testpos.y);
	}
	else {
		for (j = 1; j <= move.lmoves; ++j) {
			testpos.x = move.moves[j].oldx;
			testpos.y = move.moves[j].oldy;
			i = find_checker_by_square(testpos.x, testpos.y);
			board.board[testpos.x][testpos.y] = 0;
			redraw_square(widget, testpos.x, testpos.y);
			
			testpos.x = move.moves[j].newx;
			testpos.y = move.moves[j].newy;
			board.board[testpos.x][testpos.y] = board.checkers[i].type;
			board.checkers[i].back.x = board.checkers[i].pos.x = testpos.x * 50 + 25;
			board.checkers[i].back.y = board.checkers[i].pos.y = testpos.y * 50 + 25;
			redraw_square(widget, testpos.x, testpos.y);
                        while (gtk_events_pending ())
                        	gtk_main_iteration ();
			usleep(500000);
			
			if (testpos.x > move.moves[j].oldx)
				delta.x = 1;
			else
				delta.x = -1;
			if (testpos.y > move.moves[j].oldy)
				delta.y = 1;
			else
				delta.y = -1;
			testpos.x = move.moves[j].oldx + delta.x;
			testpos.y = move.moves[j].oldy + delta.y;
			while ((testpos.x != move.moves[j].newx) || (testpos.y != move.moves[j].newy)) {
				if (board.board[testpos.x][testpos.y] != 0) {
					i = find_checker_by_square(testpos.x, testpos.y);
					board.board[testpos.x][testpos.y] = 0;
					redraw_square(widget, testpos.x, testpos.y);
					board.checkers[i].type = 0;
				}
				testpos.x += delta.x;
				testpos.y += delta.y;
			}
		msg = g_strdup_printf("%c%c : %c%c", move.moves[j].oldx+'A', '8'-move.moves[j].oldy,
				move.moves[j].newx+'A', '8'-move.moves[j].newy);
		if (j == 1) {
			insert_to_list(msg, 1);
		}
		else {
			insert_to_list(msg, 0);
		}
		g_free(msg);
			
		}
		if (testpos.y == 7) {
			i = find_checker_by_square(testpos.x, testpos.y);
			if (board.checkers[i].type != 3) {
				board.checkers[i].type = 3;
				board.board[testpos.x][testpos.y] = board.checkers[i].type;
				redraw_square(widget, testpos.x, testpos.y);
                        	msg = g_strdup_printf("--> Queen");
	                        insert_to_list(msg, 0);
	                        g_free(msg);
			}
		}
	}
	
	board.player = (board.player % 2) + 1; /* human move */
	if (!are_legal_moves()) {
		announce_result( widget, board.player + 4);
               	msg = g_strdup_printf("  X  ");
	        insert_to_list(msg, 0);
	        g_free(msg);
		return 1;
	}
	unlegalize_moves();
	moves = find_all_moves(board.board, board.player, 0);
	sortlist(&moves);
	cutlist(moves);
	iterator = moves;
	while (iterator) {
		if (iterator->move.lmoves == 0) {
		square.x = iterator->move.moves[0].oldx;
		square.y = iterator->move.moves[0].oldy; 
		}
		else {
		square.x = iterator->move.moves[1].oldx;
		square.y = iterator->move.moves[1].oldy; 
		}
		legalize_move(square.x, square.y);
		iterator = iterator->next;
	}
	freelist(&moves);
	return 0;
}
