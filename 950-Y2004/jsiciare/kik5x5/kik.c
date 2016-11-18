/*  
 *  File: kik.c
 *
 *  $Revision: 1.1.1.1 $
 *  $Date: 2004/01/24 10:39:05 $
 *
    Implementacja interfejsu do gry w kó³ko i krzy¿yk.

#include "genlib.h"

 */

#include "kik.h"
#include "ui-kik.h"

#define CHECKING  if (plansza[x+y*BoardSize+1] != temp) {gracze[chance] = 0;} \
switch(plansza[x + y * BoardSize+1]){ \
case 'o': gracze[1]++; chance=1; break; \
case 'x': gracze[2]++; chance=2; break; \
case ' ': gracze[1] = gracze[2] = 0; chance=100; break;} \
if (gracze[1] >= WinnerResult){ \
return 1; \
}else if (gracze[2] >= WinnerResult) { \
return 2; \
}else{ \
temp = plansza[x + y * BoardSize+1]; \
}







/*  W tej tablicy zapamiêtujemy wszystkie linie
    wygrywaj±ce. Chocia¿ ³atwo jest je obliczyæ w trakcie
    gry, ale tutaj u³atwiamy sobie nieco kodowanie. */

int winningLines[][3] = {
  { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 },
  { 1, 4, 7 }, { 2, 5, 8 }, { 3, 6, 9 },
  { 1, 5, 9 }, { 3, 5, 7 } 
};

int nWinningLines = sizeof winningLines / sizeof winningLines[0];

static int Check(stateT state);


stateT NewGame(void)
{
  stateT state;
  int i;

  state=New(stateT);
  for (i=1; i<=MaxMoves; i++) {
    state->board[i]=' ';
  }
  state->whoseTurn=FirstPlayer;
  state->turnsTaken=0;
  return state;
}

void MakeMove(stateT state, moveT move) {
  state->board[move]=PlayerMark(state->whoseTurn);
  state->whoseTurn=Opponent(state->whoseTurn);
  state->turnsTaken++;
}

void RetractMove(stateT state, moveT move)
{
  state->board[move]=' ';
  state->whoseTurn=Opponent(state->whoseTurn);
  state->turnsTaken--;
}

playerT WhoseTurn(stateT state)
{
  return state->whoseTurn;
}

int GameIsOver(stateT state)
{
  return state->turnsTaken==MaxMoves || CheckForWin(state,state->whoseTurn)
    || CheckForWin(state,Opponent(state->whoseTurn));
}

/*  Sprawdzaj±c czy turnsTaken<5 przyspiesza dzia³anie programu,
    poniewa¿ ¿aden z graczy nie mo¿e wygraæ przed wykonaniem
    pi±tego ruchu. */

int CheckForWin(stateT state, playerT player)
{

  if (state->turnsTaken<5)
    return 0;

  if((Check(state)==1&&player==Human) || (Check(state)==2&&player==Computer)){
	return 1;
  }

  return 0;
}




static int Check(stateT state)
{

  char plansza[MaxMoves+1];
  int gracze[3] = {0, 0, 0 };

  int x = 0, y = 0, i, a, chance=100;
  char temp = ' ';

  for(i=0;i<=MaxMoves;i++){
  plansza[i]=state->board[i];
  }

/* POZIOMO: */

for (y = 0; y < BoardSize; y++) {
for (x = 0; x < BoardSize; x++) {

CHECKING

}gracze[1]=gracze[2] = 0;
}

/* PIONOWO: */
    for (x = 0; x < BoardSize; x++) {
	for (y = 0; y < BoardSize; y++) {

CHECKING

}gracze[1]=gracze[2] = 0;
}

/* LEWY GÓRNY -> PRAWY DOLNY  :: PONI¯EJ PRZEK¡TNEJ */
    for (a = 0; a < (BoardSize - WinnerResult + 1); a++) {
	for (x = 0, y = a; y < BoardSize; x++, y++) {

CHECKING

}gracze[1]=gracze[2] = 0;
}

/* LEWY GÓRNY -> PRAWY DOLNY :: POWY¯EJ PRZEK¡TNEJ */
    for (a = 1; a < (BoardSize - WinnerResult + 1); a++) {
	for (x = a, y = 0; x < BoardSize; x++, y++) {

CHECKING

}gracze[1]=gracze[2] = 0;
}

/* PRAWY GÓRNY -> LEWY DOLNY :: PONI¯EJ PRZEK¡TNEJ */
    for (a = 0; a < (BoardSize - WinnerResult + 1); a++) {
	for (x = (BoardSize - 1); x > 0, y < BoardSize; x--, y++) {

CHECKING

}gracze[1]=gracze[2] = 0;
}

/* PRAWY GÓRNY -> LEWY DOLNY :: POWY¯EJ PRZEK¡TNEJ */
    for (a = 0; a < (BoardSize - WinnerResult); a++) {
	for (x = (BoardSize - 2) - a, y = 0; x >= 0; x--, y++) {

CHECKING

}gracze[1]=gracze[2] = 0;
}

  return 0;
}






playerT Opponent(playerT player)
{
  switch (player) {
  case Human: return Computer;
  case Computer: return Human;
  }
  return Computer;
}
