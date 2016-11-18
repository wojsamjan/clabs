#include <stdlib.h>
#include "minimax.h"

#define WINNING 100
#define LOSING -WINNING

/* Znajduje najlepszy ruch na podstawie stanu 'state' */

static moveT FindBestMove(stateT state, int depth);

/* Funkcja wzajemnie rekurencyjna z FindBestMove okreslajaca 
   jaki ruch jest ruchem przegrywajacym LOSING */

static moveT EvaluatePosition(stateT state, int depth, int max, int rzad);

/* Funkcje */


static moveT FindBestMove(stateT state, int depth){
  moveT move,maxmove;
  int x;
  maxmove.value=LOSING-1;
  for (x=1;x<=3;x++){
    // printf(" x=%d maxmova=%d state r1=%d r2=%d r3=%d \n ",x,maxmove.value,state.r1,state.r2,state.r3);
    switch(x){
    case 1:
      if (state.r1>0){
	move=EvaluatePosition(state,depth,state.r1,x);
	if (move.value>=maxmove.value){
	  maxmove.value=move.value;
	  maxmove.ile=move.ile;
	  maxmove.rzad=x;
	}
      }
      break;
    case 2:
      if (state.r2>0){
	move=EvaluatePosition(state,depth,state.r2,x);
       	if (move.value>=maxmove.value){
	  maxmove.value=move.value;
	  maxmove.ile=move.ile;
	  maxmove.rzad=x;
	}
      }
      break;
    case 3:
      if (state.r3>0){
	move=EvaluatePosition(state,depth,state.r3,x);
	if (move.value>=maxmove.value){
	  maxmove.value=move.value;
	  maxmove.ile=move.ile;
	  maxmove.rzad=x;
	}
      }
      break;
    }
  }
  maxmove.value=-maxmove.value;
  return maxmove; 
}

static moveT EvaluatePosition(stateT state, int depth, int max, int rzad){
  int x;
  moveT move,maxmove;
  stateT newstate;
  maxmove.value=LOSING-1;
  for (x=1;x<=max;x++){
    // printf("\n E r1=%d r2=%d r3=%d max=%d rzad=%d \n",state.r1,state.r2,state.r3,max,rzad);
    newstate.r1=state.r1;
    newstate.r2=state.r2;
    newstate.r3=state.r3;
    if ((state.r1+state.r2+state.r3-x)!=0){
      switch(rzad){
      case 1:
	newstate.r1=state.r1-x;
	break;
      case 2:
	newstate.r2=state.r2-x;
	break;
      case 3:
	newstate.r3=state.r3-x;
	break;
      }
      move=FindBestMove(newstate,depth);
    }
    else
      move.value=LOSING;
    if (move.value>=maxmove.value){
      maxmove.value=move.value;
      maxmove.ile=x;
      maxmove.rzad=0;
    }
  }
  return maxmove;
}

moveT ChooseComputerMove(stateT state){
  return FindBestMove(state,1000);
}
