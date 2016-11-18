#include <stdlib.h>
#include <stdio.h>
#include "nim.h"

void GiveInstructions(void){
  clear();
  mvaddstr( 1 ,COLS/2-20,"***** G R A    W     N I M *****");
  mvaddstr( 2 ,COLS/2-30,"Standardowo mamy 3 rzedy klockow. ");
  mvaddstr( 3 ,COLS/2-30,"W pierwszym sa 3, w drugim 4, a w trzecim 5 klocki.");
  mvaddstr( 4 ,COLS/2-30,"Mozna brac dowolna ilosc klockow (conajmniej jeden) ");
  mvaddstr( 5 ,COLS/2-30,"ale tylko z jednego rzedu. ");
  mvaddstr( 6 ,COLS/2-30,"Kto bierze ostatni przegrywa.");
  mvaddstr( 8 ,COLS/2-24,"Jesli chcesz rozpoczac nacisnij ENTER ");
  getch();
  refresh();
}

stateT NewGame(void){
  stateT state;
  int c,s=1,x,r;
  clear();
  mvaddstr( 1 ,COLS/2-30,"Czy chcesz wprowadzic wlasne ustawienia ilosci klockow i ");
  mvaddstr( 2 ,COLS/2-30,"osoby zaczyajacej gre ?. Jesli tak - t, jesli nie - n : ");
  refresh();
  do{
    s=0;
    while ((r=getch())!='\n')
      c=r;
    if (c=='N' || c=='n'){
      s=2;
      c='n';
    }else
      if (c=='T' || c=='t'){
	s=0;
	c='t';
      }else{
	clear();
	mvaddstr( 3,COLS/2-30 ,"Musisz wpisac t lub n ! : ");
	refresh();
	s=1;
      }
  }while (s==1);
  if (s==0){
    clear();
    for (x=1;x<=3;x++){
      mvprintw( 2+x,COLS/2-30," Podaj liczbe klockow w %d rzedzie : ",x);
      refresh();
      switch(x){
      case 1:
	scanw("%d",&state.r1);
	break;
      case 2:
	scanw("%d",&state.r2);
	break;
      case 3:
	scanw("%d",&state.r3);
	break;
      }
    }
    mvaddstr(6 ,COLS/2-30," Wpisz kto bedze zaczynal gre. 0 - Czlowiek , 1 - Komputer : ");
    refresh();
    do{
      s=0;
      scanw("%d",&c);
      if (c==0 || c==1){
	s=0;
	state.who=c;
      }else{
	clear();
	mvaddstr( 6 , COLS/2-30,"Musisz wpisac 0 lub 1 ! : ");
	refresh();
	s=1;
      }
    }while (s==1);
    }else{
    state.r1=3;
    state.r2=4;
    state.r3=5;
    state.who=0;
    } 
  clear();
  return state;
}

int GameIsOver(stateT state){
  int r;
  if ((state.r1+state.r2+state.r3)<=1)
    r=1;
  else 
    r=0;
  return r;
}

void DisplayGame(stateT state){
  int x;
  if (has_colors()==1){
    mvaddstr( 2 ,COLS/2-30,"Rzad 1 : ");
    for (x=1;x<=state.r1;x++){
      attrset(COLOR_PAIR(4));
      printw("  ");
      attrset(COLOR_PAIR(1));
      printw(" ");
    } 
    mvaddstr( 4 ,COLS/2-30,"Rzad 2 : ");
    for (x=1;x<=state.r2;x++){
      attrset(COLOR_PAIR(3));
      printw("  ");
      attrset(COLOR_PAIR(1));
      printw(" ");
    }
    mvaddstr( 6 ,COLS/2-30,"Rzad 3 : ");
    for (x=1;x<=state.r3;x++){
      attrset(COLOR_PAIR(5));
      printw("  ");
      attrset(COLOR_PAIR(1));
    printw(" ");
    }
  }else{
    mvprintw( 2 ,COLS/2-30,"Rzad 1 : %d",state.r1);
    mvprintw( 3 ,COLS/2-30,"Rzad 2 : %d",state.r2);
    mvprintw( 4 ,COLS/2-30,"Rzad 3 : %d",state.r3);
  }
  refresh();
}

int WhoseTurn(stateT state){
  return state.who;
}

moveT GetUserMove(stateT state){
  int c,s,max;
  moveT move;
    mvaddstr( LINES-2 ,COLS/2-30,"Z jakiego rzedu bedziesz bral klocki ? : ");
  do{
    s=0;
    refresh();
    scanw("%d",&s);
    switch(s){
    case 1:
      if (state.r1==0){
	s=0;
	mvaddstr( LINES-2 ,COLS/2-30,"W tym rzedzie nie ma klockow.");
	mvaddstr( LINES-1 ,COLS/2-30,"Wybierz inny rzad : ");
      }
      break;
    case 2:
      if (state.r2==0){
	s=0;
	mvaddstr( LINES-2 ,COLS/2-30,"W tym rzedzie nie ma klockow.");
	mvaddstr( LINES-1 ,COLS/2-30,"Wybierz inny rzad : ");
      }
      break;
    case 3:
      if (state.r3==0){
	s=0;
	mvaddstr( LINES-2 ,COLS/2-30,"W tym rzedzie nie ma klockow.");
	mvaddstr( LINES-1 ,COLS/2-30,"Wybierz inny rzad : ");
      }
      break;
    default:
      s=0;
      clear();
      DisplayGame(state);
      mvaddstr( LINES-2 ,COLS/2-30,"Musiz wybrac 1,2 lub 3 : ");
      break;
    }
  }while(s==0);
  move.rzad=s;
  mvprintw( LINES-1 ,COLS/2-30,"Ile bierzesz klockow z %d rzedu ? : ",s);
  do{
    refresh();
    scanw("%d",&s);
    switch(move.rzad){
    case 1:
      c=1;
      max=state.r1;
      break;
    case 2:
      c=2;
      max=state.r2;
      break;
    case 3:
      c=3;
      max=state.r3;
      break;
    }
    if(s>0 && s<=max){
      c=s;
      s=1;
    }
    else{
      clear();
      DisplayGame(state);
      mvprintw( LINES-2 ,COLS/2-30,"Musisz wybrac liczbe od 1 do %d. Wiec : ",max);
      s=0;
    }
  }while(s==0);
  move.ile=c;
  return move;
}

void DisplayMove(moveT move){
  mvprintw( LINES-1 ,COLS/2-30,"Biore z %d rzedu %d klockow",move.rzad,move.ile);
  refresh();
}

stateT MakeMove(stateT state,moveT move){
  mvprintw( 1 ,COLS/2-30,"Po zabraniu %d klockow z %d rzedu : ",move.ile,move.rzad);
  switch(move.rzad){
  case 1:
    state.r1=state.r1-move.ile;
    break;
  case 2:
    state.r2=state.r2-move.ile;
    break;
  case 3:
    state.r3=state.r3-move.ile;
    break;
  }
  napms(3000);
  clear();
  DisplayGame(state);
  if (state.who==0)
    state.who=1;
  else
    state.who=0;
  return state;
}

void AnnounceResults(stateT state){
  if ((state.r1+state.r2+state.r3)==1);
  else
    if (state.who==1)
      state.who=0;
    else
      state.who=1;
  switch(state.who){
  case Human:
    mvaddstr( LINES/2,COLS/2-10,"Wygralem!\n");
    break;
  case Computer:
    mvaddstr( LINES/2,COLS/2-10,"Gratulacje! Przegralem\n");
    break;
  }   
  refresh();
}
