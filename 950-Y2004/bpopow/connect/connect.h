
#ifndef KIK_INCLUDED
#define KIK_INCLUDED


#define WinningPosition  1000
#define NeutralPosition  0
#define LosingPosition  (-WinningPosition)


typedef enum { Human, Computer } playerT;


typedef int moveT;

typedef struct {
  char board[7+1][6+1];
  playerT whoseTurn;
  int turnsTaken;
} *stateT;

#define MaxMoves  8

#define MaxDepth  5

#define FirstPlayer  Computer

stateT NewGame(void);


void MakeMove(stateT state, moveT move);

/*  Funkcja zwraca TRUE je¶li state wskazuje na koniec gry. */

/*bool GameIsOver(stateT state);*/
int GameIsOver(stateT state);

/*  Funkcja zwracaj±ca w podanym stanie czyj jest ruch. */

playerT WhoseTurn(stateT state);

/*  Funkcja zmienia stan gry ,,odwo³uj±c'' podany ruch. */

void RetractMove(stateT state, moveT move);

/*  Funkcja zwraca TRUE je¶li podany gracz wygra³ grê. */

/*bool CheckForWin(stateT state, playerT player);*/
int CheckForWin(stateT state, playerT player);

/*  Funkcja zwraca warto¶æ wskazuj±ca czyj jest nastêpny ruch. */

playerT Opponent(playerT player);
int WhereInCol(stateT state, moveT move);
int WezLiczbe();

#endif
