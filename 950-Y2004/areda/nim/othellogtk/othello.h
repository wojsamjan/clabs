#ifndef OTHELLO_INCLUDED
#define OTHELLO_INCLUDED

#include <stdbool.h>

/*  Sta³e okre¶laj±ce system oceniania pozycji w grze.*/ 

#define WinningPosition  1000
#define NeutralPosition  0
#define LosingPosition  (-WinningPosition)

/*  Typ umo¿liwiaj±cy rozró¿nienie graczy. */

typedef enum { Human, Computer } playerT;

/*   Typ umo¿liwiaj±cy rozró¿nienie kierunków */

typedef enum { North=0, East, South, West, NE, ES, SW, WN} directionT;

/*  Typ moveT umo¿liwia zapamiêtanie pojedynczego
    ruchu w grze. */

typedef struct {
  int x,y;
} moveT;

/* Stan gru zapamiêtany jest w strukturze.
 * board - tablica wska¼ników, zapamiêtuje planszê
 * whoseTurn - przechowuje informacjê o tym czyj jest ruch
 * turnsTaken - zawiera ilo¶æ wykonanych ruchów 
 * (w "Othello" ka¿dy ruch oznacza zajêcie jednego pola na planszy) */ 

typedef struct {
  char board[10][11];
  playerT whoseTurn;
  int turnsTaken;
} *stateT;

/*  Sta³a ta okre¶la maksymaln± liczba ruchów.
    Korzystamy z niej alokuj±c, w danej pozycji, pamiêæ na 
    tablicê dopuszczalnych ruchów. */

#define MaxMoves 60

/*  Sta³a ta okre¶la maksymaln± g³êboko¶æ rekurencji
    w poszukiwaniu najlepszego ruchu. */

#define MaxDepth 4 

/*  Sta³a ta wskazuje, kto ma pierwszy ruch. */

#define FirstPlayer Human

/*  T± funkcj± zaczynamy now± grê. Zwraca ona stan pocz±tkowy
    gry. */

stateT NewGame(void);

/*  Funkcja zmienia stan gry wykonuj±c podany ruch. */

void MakeMove(stateT state, moveT move, char *changes);

/*  Funkcja zwraca TRUE je¶li state wskazuje na koniec gry. */

bool GameIsOver(stateT state);

/*  Funkcja zwracaj±ca w podanym stanie czyj jest ruch. */

playerT WhoseTurn(stateT state);


/*  Funkcja zmienia stan gry ,,odwo³uj±c'' podany ruch. */

void RetractMove(stateT state, moveT move, char *changes);

/*  Funkcja zwraca TRUE je¶li podany gracz wygra³ grê. */

bool CheckForWin(stateT state, playerT player);

/*  Funkcja zwraca warto¶æ wskazuj±ca czyj jest nastêpny ruch. */

playerT Opponent(playerT player);

/*  Funkcja prze³±czaj±ca gracza */

void SwitchToOpponent(stateT state);

/*  Funkcja zwracaj±ca pozycjê s±siedniego punktu w kierunku dir */

static moveT diffs[] = { {0,-1},{1,0},{0,1},{-1,0},{1,-1},{1,1},{-1,1},{-1,-1} };

extern inline moveT AdjacentPoint(moveT pt, directionT dir) {
      pt.x += diffs[dir].x;
      pt.y += diffs[dir].y;
      return pt;
}

/*  Funkcja zwraca TRUE je¶li mo¿na wykonaæ podany ruch */

bool MoveIsLegal(moveT move, stateT state);

/*  Funkcja zwraca TRUE gdy dany gracz nie mo¿e wykonaæ ¿adnego ruchu */

bool NoLegalMoves(stateT state);

/*  Funkcja zwracaj±ca znak umieszczany na planszy 
    przez gracza wykonuj±cego ruch. */

extern inline char PlayerMark(playerT player)
{
  if (player==FirstPlayer)
    return 'x';
  else
    return 'o';
}

/*  Funkcja zwracaj±ca znak na planszy gry w miejscu move */
extern inline char BoardXY(stateT state, moveT move)
{
	return (state->board[move.y][move.x]);
}


#endif
