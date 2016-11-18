/*
    Implementacja interfejsu u¿ytkownika do gry w CONNECT 4.
 */

#include "connect.h"
#include "ui-connect.h"
#include <stdlib.h>
#include <stdio.h>
#include <ncurses/curses.h>
#include <simpio.h>


static int MoveIsLegal(moveT move, stateT state);

void RysujLinie(){
  int i;

  printf("     ");
  for(i = 0; i<=20; i++)
    printf("-");
  printf("\n");
}

void DisplayGame(stateT state) {
  int i,j;
    for(j = 6; j>=1; j--){  
      RysujLinie();
      /*      refresh();*/
      for(i = 1; i<=7; i++){ 
	/*	color_set(3,0);*/
	if (i == 1) printf("     ");
	/*refresh();*/
	/*	if(state->board[i][j] == 'X')
	  color_set(1,0);
	if(state->board[i][j] == 'O')
	color_set(2,0);*/
	printf(" %c ", state->board[i][j]);
      }
      /*      color_set(3,0);*/
      printf("\n");
    }
    RysujLinie();
    printf("      ");
    for(i = 1; i<=7; i++)
      printf("%d  ",i);
    printf("\n");
    printf("\n");
}

void DisplayMove(moveT move)
{
  printf("Stawiam `%c' na polu %d.\n",
	 PlayerMark(Computer),move);
}

char PlayerMark(playerT player)
{
  if (player==FirstPlayer)
    return 'X';
  else
    return 'O';
}

static int MoveIsLegal(moveT move, stateT state) /*bool*/
{
  return move>=1 && move<=7 && state->board[move][6]==' ';
}

moveT GetUserMove(stateT state) {
  moveT move;
  printf("Twój ruch.\n");
  while (1) {
    printf("Na jakie pole? ");
    /*move=GetInteger();*/
    scanf("%d",&move);
    if (MoveIsLegal(move,state))
      break;
    printf("Tego ruchu nie mo¿esz wykonaæ. Spróbuj jeszcze raz.\n");
  }
  return move;
}

void AnnounceResults(stateT state)
{
  DisplayGame(state);
  if (CheckForWin(state,Human)) {
    printf("Wygra³e¶;(\n");
  } else if (CheckForWin(state,Computer)) {
    printf("Wygra³em;)\n");
  } else {
    printf("Remis.\n");
  }
}

void GiveInstructions(void) 
{
  printf("Witam w grze 'CONNECT 4' aka '4 IN LINE' aka 'CZWÓRKI'.\n");
}
