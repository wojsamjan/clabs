/*  
 *  File: kik.c
 *
 *  $Revision: 1.1.1.1 $
 *  $Date: 2004/01/24 10:40:30 $
 *
    Implementacja interfejsu do gry w CONNECT 4.
 */

#include "genlib.h"
#include "connect.h"
#include "ui-connect.h"

stateT NewGame(void) {
  stateT state;
  int i,j;

  state = (stateT)malloc(sizeof(stateT));
  for (i=1; i<=7; i++) {
    for(j = 1; j<=6; j++){
      state->board[i][j]=' ';
    }
  }
  state->whoseTurn=FirstPlayer;
  state->turnsTaken=0;
  return state;
}


int WhereInCol(stateT state, moveT move){
  int i;

  /*if(move>7) return 2;*/

  for(i = 1; i<=6; i++){
    if(state->board[move][i] == ' ') return i;    
  }
  return 0;
}

void MakeMove(stateT state, moveT move) {
  /*  int a;  
  a = WhereInCol(state, move);
  printf("%d\n",a);*/
  state->board[move][WhereInCol(state, move)]=PlayerMark(state->whoseTurn);
  state->whoseTurn=Opponent(state->whoseTurn);
  state->turnsTaken++;
}

void RetractMove(stateT state, moveT move) {
  int a;

  a = WhereInCol(state, move);

  if(a == 0) a = 7;
  
  state->board[move][a-1]=' ';
  state->whoseTurn=Opponent(state->whoseTurn);
  state->turnsTaken--;
}

playerT WhoseTurn(stateT state)
{
  return state->whoseTurn;
}

int GameIsOver(stateT state)
{
  return state->turnsTaken==6*7 || CheckForWin(state,state->whoseTurn)
    || CheckForWin(state,Opponent(state->whoseTurn));
}

static int RecursiveSkosPrawy(stateT state, char mark, int i, int j, int suma){

  if(state->board[i][j] == mark){
    suma++;
    if(suma == 4)
      return 1;
  }
  else suma = 0;
  
  if(i<=7 && j<=6) /*!!!!!!*/
    return RecursiveSkosPrawy(state, mark, i+1, j+1, suma);
  else return 0;
}

static int RecursiveSkosLewy(stateT state, char mark, int i, int j, int suma){

  if(state->board[i][j] == mark){
    suma++;
    if(suma == 4)
      return 1;
  }
  else suma = 0;

  if(i<7 && j>1)
    return RecursiveSkosLewy(state, mark, i+1, j-1, suma);
  else return 0;
}

static int CheckSkosPrawy(stateT state, playerT player){
  int i,j;
  char mark = PlayerMark(player);

  for(i = 1; i<=4; i++){
    if(i == 1){
      for(j = 1; j<=3; j++)
	if(RecursiveSkosPrawy(state, mark, i, j, 0)) return 1;
    }
    else if(RecursiveSkosPrawy(state, mark, i, 1, 0)) return 1;
    
  }
  return 0;
}

static int CheckPion(stateT state, playerT player){
  int i,j,suma;
  char mark = PlayerMark(player);

  for(i = 1; i<=7; i++){
    suma = 0;
    for(j = 1; j<=6; j++){
      if(j>3 && suma == 0)
	break;
      if(mark == state->board[i][j])
	suma++;
      else suma = 0;
      if(suma == 4) {
	/*if(mark == 'O'){
	  state->board[i][j] = 'Q';
	  state->board[i][j-1] = 'Q';
	  state->board[i][j-2] = 'Q';
	  state->board[i][j-3] = 'Q';	  
	}
	else if(mark == 'X'){
	  state->board[i][j] = 'V';
	  state->board[i][j-1] = 'V';
	  state->board[i][j-2] = 'V';
	  state->board[i][j-3] = 'V';
	  }*/
	return 1;
      }
    }
  }
  return 0;
}

static int CheckPoziom(stateT state, playerT player){
  int i,j,suma;
  char mark = PlayerMark(player);

  for(j = 1; j<=6; j++){
    suma = 0;
    for(i = 1; i<=7; i++){
      if(i>4 && suma == 0)
	break;
      if(mark == state->board[i][j])
	suma++;
      else suma = 0;
      if(suma == 4) {
	/*if(mark == 'O'){
	  state->board[i][j] = 'Q';
	  state->board[i-1][j] = 'Q';
	  state->board[i-2][j] = 'Q';
	  state->board[i-3][j] = 'Q';	  
	}
	else if(mark == 'X'){
	  state->board[i][j] = 'V';
	  state->board[i-1][j] = 'V';
	  state->board[i-2][j] = 'V';
	  state->board[i-3][j] = 'V';
	  }*/
	return 1;
      }
    }
  }
  return 0;
}

static int CheckSkosLewy(stateT state, playerT player){
  int i, j;
  char mark;

  mark = PlayerMark(player);

  for(i = 1; i<=4; i++){
    if(i == 1){
      for(j = 4; j<=6; j++)
	if(RecursiveSkosLewy(state, mark, i, j, 0)) return 1;
    }
    else if(RecursiveSkosLewy(state, mark, i, 6, 0)) return 1;
  }
  return 0;
}

int CheckForWin(stateT state, playerT player){

  if (state->turnsTaken<7)
    return 0;
    
  return CheckPion(state, player) || CheckPoziom(state, player)
    || CheckSkosPrawy(state, player) || CheckSkosLewy(state, player);
}

playerT Opponent(playerT player)
{
  switch (player) {
  case Human: return Computer;
  case Computer: return Human;
  }
  return Computer;
}

int WezLiczbe(){
  int temp,c;

  while (1 == 1){
    printf("Podaj liczbe: ");
    while ((c = getchar()) != 10){
      temp = c;
    }
    if(temp>48 && temp<51)
      return temp-'0';
  }
}
