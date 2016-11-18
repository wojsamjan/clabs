/* Jakub S³awiñski 13.12.2003 r.
 * plik implementuj±cy strategiê minimax oraz funkcje pomocnicze
 * dramm.c
 */

#include <string.h>
#include <stdlib.h>
#include <setjmp.h>
#include "dramm.h"
#include "draughts.h"

extern chessboardT board;
static jmp_buf bufor;

/* is_square_outside
 * funkcja sprawdza, czy podane wspó³rzêdne mieszcz± siê na szachownicy
 */

int
is_square_outside(pointT square)
{
	if ((square.x < 0) || square.x > 7)
		return 1;
	if ((square.y < 0) || square.y > 7)
		return 1;
	return 0;
}

/* is_sample_break_dir
 * funkcja sprawdza, czy w podanym kierunku jest zwyk³e bicie
 */

int
is_simple_break_dir(pointT square, char dir)
{
	pointT point = square;
	switch (dir) {
		case 0: {
				point.x -= 2;
				point.y -= 2;
				if (is_square_outside(point)) {
					return 0;
				}
				if (board.board[point.x][point.y] != 0)
					return 0;
				if (board.board[square.x-1][square.y-1] < 3)
					return board.board[square.x-1][square.y-1];
				else
					return (board.board[square.x-1][square.y-1]-2);
				break;
			}
		case 1: {
				point.x += 2;
				point.y -= 2;
				if (is_square_outside(point)) {
					return 0;
				}
				if (board.board[point.x][point.y] != 0)
					return 0;
				if (board.board[square.x+1][square.y-1] < 3)
					return board.board[square.x+1][square.y-1];
				else
					return (board.board[square.x+1][square.y-1]-2);
				break;
			}
		case 2: {
				point.x -= 2;
				point.y += 2;
				if (is_square_outside(point)) {
					return 0;
				}
				if (board.board[point.x][point.y] != 0)
					return 0;
				if (board.board[square.x-1][square.y+1] < 3)
					return board.board[square.x-1][square.y+1];
				else
					return (board.board[square.x-1][square.y+1]-2);
				break;
			}
		case 3: {
				point.x += 2;
				point.y += 2;
				if (is_square_outside(point)) {
					return 0;
				}
				if (board.board[point.x][point.y] != 0)
					return 0;
				if (board.board[square.x+1][square.y+1] < 3)
					return board.board[square.x+1][square.y+1];
				else
					return (board.board[square.x+1][square.y+1]-2);
				break;
			}
	}
	return 0;
}

/* is_queen_break_dir
 * funkcja sprawdza, czy w podanym kierunku jest bicie przez królow±
 */

int
is_queen_break_dir(pointT square, char dir)
{
	pointT delta;
	int state;
	pointT point = square;
	switch (dir) {
		case 0: {
				delta.x = 1;
				delta.y = 1;
				break;
			}
		case 1: {
				delta.x = -1;
				delta.y = 1;
				break;
			}
		case 2: {
				delta.x = 1;
				delta.y = -1;
				break;
			}
		case 3: {
				delta.x = -1;
				delta.y = -1;
				break;
			}
	}
	point.x += delta.x;
	point.y += delta.y;
	state = 0;
	while (!is_square_outside(point)) {
		if (board.board[point.x][point.y] == 1 || board.board[point.x][point.y] == 3) {
			if (state == 0) {
				state = 1;
			}
			else {
				return 0;
			}
		}
		if (board.board[point.x][point.y] == 0) {
			if (state == 1)
				return 1;
		}
		point.x += delta.x;
		point.y += delta.y;
	}
	return 0;
}

/* is_next_break
 * funkcja sprawdza, czy w nastêpnym ruchu jest mo¿liwe bicie
 */

int
is_next_break(char type)
{
        switch (type) {
                case 2:{
	       if (is_simple_break_dir(board.data, 0) == ((type==1)?2:1))return 1;
	       if (is_simple_break_dir(board.data, 1) == ((type==1)?2:1))return 2;
	       if (is_simple_break_dir(board.data, 2) == ((type==1)?2:1))return 3;
	       if (is_simple_break_dir(board.data, 3) == ((type==1)?2:1))return 4;
                                break;
		       }
		case 4:{
	       if (is_queen_break_dir(board.data, 0))return 1;
	       if (is_queen_break_dir(board.data, 1))return 2;
	       if (is_queen_break_dir(board.data, 2))return 3;
	       if (is_queen_break_dir(board.data, 3))return 4;
			       break;
		       }
        }
	return 0;
}

/* are_legal_moves
 * funkcja zwraca, czy s± jeszcze mo¿liwe ruchy do wykonania
 */

int
are_legal_moves(void)
{
	int state;
	nodeT* moves = NULL;
	moves = find_all_moves(board.board, board.player, 0);
	if (moves)
		state = 1;
	else
		state = 0;
	freelist(&moves);
	return state;
}

/* make_computer_move
 * funkcja jest odpowiedzialna za wykonanie ruchu przez koputer.
 * Jest to funkcja opakowuj±ca dla find_best_move, która z kolei jest elementem
 * ci±gu wywo³añ funkcji w strategii minimax
 */

moveT
make_computer_move(void)
{
	moveT move;
	int rating;
	if (setjmp(bufor) == 0)
		move = find_best_move(board.board, 1, 1, &rating);
	return move;
}

/* copy_board
 * funkcja kopiuje zawarto¶æ pamiêci z src do dest
 */

void
copy_board(char dest[][8], char src[][8])
{
	memcpy(dest, src, 64);
}

/* find_m_moves
 * funkcja wyszukuje wszystkie mo¿liwe ruchy zwyk³ych pinów
 */

void
find_m_moves(nodeT** movesRef, pointT square, char lboard[][8], char type)
{
	int i;
	pointT cursqr;
	moveT newmove;
	smoveT smove;
	cursqr = square;
	if (type == 1)
		cursqr.y += 1;
	else
		cursqr.y -= 1;
	cursqr.x -= 1;
	for (i = 0; i < 2; ++i) {
		if (i == 1)
			cursqr.x += 2;
		if (!is_square_outside(cursqr)) {
			if (lboard[cursqr.x][cursqr.y] == 0) {
				newmove.lmoves = 0;
				smove.oldx = square.x;
				smove.oldy = square.y;
				smove.newx = cursqr.x;
				smove.newy = cursqr.y;
				newmove.moves[0] = smove;
				copy_board(newmove.board, lboard);
				newmove.board[square.x][square.y] = 0;
				if (type==1)
					newmove.board[cursqr.x][cursqr.y] = (cursqr.y==7)?3:1;
				else
					newmove.board[cursqr.x][cursqr.y] = (cursqr.y==0)?4:2;
				insertnode(movesRef, newmove);
			}
		}
	}
}

/* find_m_breaks
 * funkcja wyszukuje wszystkie mo¿liwe bicia zwyk³ych pionów
 */

void
find_m_breaks(nodeT** movesRef, pointT square, char lboard[][8], char depth, smoveT* prevmov, char type)
{
	int i;
	char checker;
	pointT cursqr;
	static moveT newmove;
	smoveT smove;
	cursqr = square;
	cursqr.y += 2;
	cursqr.x += 2;
	for (i = 0; i < 4; ++i) {
		if (i == 1)
			cursqr.x -= 4;
		if (i == 2)
			cursqr.y -= 4;
		if (i == 3)
			cursqr.x += 4;
		if (!is_square_outside(cursqr)) {
			checker = lboard[(cursqr.x+square.x)/2][(cursqr.y+square.y)/2];
			if ((lboard[cursqr.x][cursqr.y] == 0) && ((checker == (type%2)+1) || 
						(checker == ((type+2)%2)+3))) {
				newmove.lmoves = depth;
				smove.oldx = square.x;
				smove.oldy = square.y;
				smove.newx = cursqr.x;
				smove.newy = cursqr.y;
				memcpy(newmove.moves, prevmov, (depth-1) * sizeof(smoveT));
				newmove.moves[(int) depth] = smove;
				copy_board(newmove.board, lboard);
				newmove.board[square.x][square.y] = 0;
				newmove.board[(cursqr.x+square.x)/2][(cursqr.y+square.y)/2] = -1;
				if (type==1)
					newmove.board[cursqr.x][cursqr.y] = (cursqr.y==7)?3:1;
				else
					newmove.board[cursqr.x][cursqr.y] = (cursqr.y==0)?4:2;
				insertnode(movesRef, newmove);
				find_m_breaks(movesRef, cursqr, newmove.board, depth+1, newmove.moves, type);
			}
		}
	}
}

/* find_q_moves
 * funkcja wyszukuje wszystkie mo¿liwe ruchy damek
 */

void
find_q_moves(nodeT** movesRef, pointT square, char lboard[][8], char type)
{
	int i;
	pointT cursqr;
	moveT newmove;
	smoveT smove;
	for (i = 0; i < 4; ++i) {
		cursqr = square;
		while (!is_square_outside(cursqr)) {
			if (i == 0) {
				cursqr.x += 1;
				cursqr.y += 1;
			}
			if (i == 1) {
				cursqr.x -= 1;
				cursqr.y += 1;
			}
			if (i == 2) {
				cursqr.x += 1;
				cursqr.y -= 1;
			}
			if (i == 3) {
				cursqr.x -= 1;
				cursqr.y -= 1;
			}
			if (!is_square_outside(cursqr)) {
				if (lboard[cursqr.x][cursqr.y] == 0) {
					newmove.lmoves = 0;
					smove.oldx = square.x;
					smove.oldy = square.y;
					smove.newx = cursqr.x;
					smove.newy = cursqr.y;
					newmove.moves[0] = smove;
					copy_board(newmove.board, lboard);
					newmove.board[square.x][square.y] = 0;
					newmove.board[cursqr.x][cursqr.y] = (type == 1)?3:4;
					insertnode(movesRef, newmove);
				}
				else {
					break;
				}
			}
			else {
				break;
			}
		}
	}
}

/* find_q_breaks
 * funkcja wyszukuje wszystkie mo¿liwe bicia damek
 */

void
find_q_breaks(nodeT** movesRef, pointT square, char lboard[][8], char depth, smoveT* prevmov, char type)
{
	int i;
	char checker;
	pointT cursqr;
	int state;
	pointT lastsquare;
	static moveT newmove;
	smoveT smove;
	for (i = 0; i < 4; ++i) {
		cursqr = square;
		state = 0;
		while (!is_square_outside(cursqr)) {
			if (i == 0) {
				cursqr.x += 1;
				cursqr.y += 1;
			}
			if (i == 1) {
				cursqr.x -= 1;
				cursqr.y += 1;
			}
			if (i == 2) {
				cursqr.x += 1;
				cursqr.y -= 1;
			}
			if (i == 3) {
				cursqr.x -= 1;
				cursqr.y -= 1;
			}
			if (!is_square_outside(cursqr)) {
				if (state == 1) {
					if (lboard[cursqr.x][cursqr.y] == 0) {
				newmove.lmoves = depth;
				smove.oldx = square.x;
				smove.oldy = square.y;
				smove.newx = cursqr.x;
				smove.newy = cursqr.y;
				memcpy(newmove.moves, prevmov, (depth-1) * sizeof(smoveT));
				newmove.moves[(int) depth] = smove;
				copy_board(newmove.board, lboard);
				newmove.board[square.x][square.y] = 0;
				newmove.board[lastsquare.x][lastsquare.y] = -1;
				newmove.board[cursqr.x][cursqr.y] = (type == 1)?3:4;
				insertnode(movesRef, newmove);
				find_q_breaks(movesRef, cursqr, newmove.board, depth+1, newmove.moves, type);
					}
					else {
						break;
					}
				}
				else {
					checker = lboard[cursqr.x][cursqr.y];
					if ((checker == (type%2)+1) || (checker == ((type+2)%2)+3)) {
						lastsquare = cursqr;
						state = 1;
					}
					else {
						if (checker != 0)
							break;
					}
				}
			}
			else {
				break;
			}
		}
	}
}

/* find_all_moves
 * funkcja wyszukuje wszystkie mo¿liwe ruchy
 */

nodeT*
find_all_moves(char lboard[][8], char type, char mode)
{
	int i, j;
	pointT square;
	nodeT* moves = NULL;
	if (mode) {
		if (mode == 2) {
			find_m_moves(&moves, board.data, lboard, type);
			find_m_breaks(&moves, board.data, lboard, 1, NULL, type);
		}
		if (mode == 4) {
			find_q_moves(&moves, board.data, lboard, type);
			find_q_breaks(&moves, board.data, lboard, 1, NULL, type);
		}
	}
	else {
	   for (i = 0; i < 8; ++i) {
		for (j = 0; j < 8; ++j) {
			square.x = i;
			square.y = j;
			if ((lboard[i][j]==(type%2)+1) || (lboard[i][j]==(type%2)+3) || (lboard[i][j]==0))
				continue; /* there is no checker */
			if (lboard[i][j] == type) {
				find_m_moves(&moves, square, lboard, type);
				find_m_breaks(&moves, square, lboard, 1, NULL, type);
			}
			if (lboard[i][j] == type+2) {
				find_q_moves(&moves, square, lboard, type);
				find_q_breaks(&moves, square, lboard, 1, NULL, type);
			}
		}
	   }
	}
	return moves;
}

/* find_best_move
 * funkcja wyszukuje najlepszy ruch w danej pozycji.
 * Wywo³uje siê wzajemnie rekurencyjnie z funkcj± evaluate_position,
 * by zgodnie ze strategi± minimax wyszukiwaæ posuniêcie do wykonania.
 */

moveT
find_best_move(char lboard[][8], char type, int depth, int *pRating)
{
	int i, max;
	nodeT* moves = NULL;
	nodeT* iterator;
	static moveT statmove;
	moveT* move;

	while (gtk_events_pending()) {
		gtk_main_iteration();
		if (board.newgamepending)
			longjmp(bufor, 1);
	}
	
	move = malloc(sizeof(moveT));
	moves = find_all_moves(lboard, type, 0);
	sortlist(&moves);
	cutlist(moves);
	move->lmoves = -1;
	if (type == 2)
		max = -1000;
	else
		max = 1000;
	iterator = moves;
	while (iterator) {
		i = evaluate_position(iterator->move.board, type, depth);
		if (type == 2) {
			if (i > max) {
				max = i;
				move->lmoves = iterator->move.lmoves;
				memcpy(move->moves, iterator->move.moves, 12 * 4);
				*pRating = max;
			}
		}
		else {
			if (i < max) {
				max = i;
				move->lmoves = iterator->move.lmoves;
				memcpy(move->moves, iterator->move.moves, 12 * 4);
				*pRating = max;
			}
		}
		iterator = iterator->next;
	}
	if (move->lmoves == -1) {
		if (type == 1) {
			*pRating = 100;
		}
		else {
			*pRating = -100;
		}
	}
	freelist(&moves);
	statmove.lmoves = move->lmoves;
	memcpy(statmove.moves, move->moves, 12 * 4);
	free(move);
	return statmove;
}

/* evaluate_position
 * funkcja ocenia dan± pozycjê albo poprzez wywo³anie find_best_move
 * dla drugiego gracza, albo przez statyczne ocenienie pozycji, gdy
 * osi±gniêto limit g³êboko¶ci rekursji
 */

int
evaluate_position(char lboard[][8], char type, int depth)
{
	int i, j, evaluation;
	evaluation = 0;
	if (depth>=board.reclevel) {
		for (i = 0; i < 8; ++i) {
			for (j = 0; j < 8; ++j) {
				if (lboard[i][j] == type)
					evaluation += 1;
				if (lboard[i][j] == type+2)
					evaluation += 3;
				if (lboard[i][j] == (type%2)+1)
					evaluation -= 1;
				if (lboard[i][j] == ((type+2)%2)+3)
					evaluation -= 3;
			}
		}
		return evaluation;
	}
	find_best_move(lboard, (type%2)+1, depth+1, &evaluation);
	return evaluation;
}

/* unlegalize_moves
 * funkcja uniemo¿liwia poruszanie wszystkimi pionami na planszy
 */

void
unlegalize_moves(void)
{
	int i;
	for (i = 12; i < 24; ++i) {
		board.checkers[i].legal = 0;
	}
}

/* legalize_move
 * funkcja umo¿liwia poruszanie pionem le¿±cym na danej pozycji
 */

void
legalize_move(char x, char y)
{
	int i;
	pointT square;
                for (i = 12; i < 24; ++i) {
			if (board.checkers[i].type == 0)
				continue;
                        square = board_square(board.checkers[i].back.x, board.checkers[i].back.y);
                                if (square.x == x && square.y == y) {
                                        board.checkers[i].legal = 1;
					return;
                                }
                }
	
}
