/* Jakub S³awiñski 13.12.2003 r.
 * plik nag³ówkowy dla implementacji minimaxa oraz funkcji pomocniczych
 * dramm.h
 */

#ifndef _JS_DRAMM_H
#define _JS_DRAMM_H

typedef struct {
	char oldx, oldy;
	char newx, newy;
} smoveT;

typedef struct {
	char lmoves;
	smoveT moves[12];
	char board[8][8];
} moveT;

typedef struct node {
	moveT move;
	struct node* next;
	struct node* prev;
} nodeT;

nodeT* find_all_moves(char lboard[][8], char type, char mode); /* find all the possible moves */
moveT find_best_move(char lboard[][8], char type, int depth, int *pRating); /* find best move */
int evaluate_position(char lboard[][8], char type, int depth); /* evaluate current position */

int is_next_break(char type); /* is there a break possibility after the move? */
int are_legal_moves(void); /* is there any legal moves for the player? */
void unlegalize_moves(void); /* unlegalize all checkers */
void legalize_move(char x, char y); /* legalize the ponted checker */
moveT make_computer_move(void); /* computer make a move in this function */


void insertnode(nodeT**, moveT); /* insert an element to a list*/
void freelist(nodeT**); /* free the memory allocated for a list */
void sortlist(nodeT**); /* sort the list */
void cutlist(nodeT*); /* cut the list to the first greatest keys */

#endif
