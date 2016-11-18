#include <stdio.h>
#include <stdlib.h>
#include "mazelib.h"
#include <ncurses/curses.h>

int WezLiczbe(){
  int temp,c;

  while (1 == 1){
    printw("Podaj liczbe: ");
    while ((c = getch()) != 10){
      temp = c;
    }
    if(temp>48 && temp<53)
      return temp-'0';
  }
}

int main(int argc, char *argv[]){

  TPoint pt;
  int i,check,wybor;
  i = wybor = 0;
  p = &pt;
  initscr();
  start_color();
  init_pair(1, COLOR_YELLOW, COLOR_BLACK); /*Sciany Labiryntu*/
  init_pair(2, COLOR_RED, COLOR_BLACK); /*Ludek i X'y*/
  init_pair(3, COLOR_WHITE, COLOR_BLACK); /*Pozostale rzeczy (text)*/

  if(argc < 2){
    printw("\nNie poda³e¶ prawid³owej liczby argumentów w wywo³aniu funkcji.\n\n");
    getch();
    goto koniec;
  }

  check = BierzLab(argv);
  lab2 = malloc(sizeof(int*)*(LabX+1));
  for(i = 0; i<=LabX; i++)
    lab2[i] = malloc(sizeof(int*)*LabY);

  if(check == 0){
    printw("\nPlik nie zawiera poprawnego labiryntu!\n");
    getch();
    goto koniec;
  }

  i = SzukajStartu();
  if(i == 0)  pt = LosujMiejsceStartu();

  RysujLab(lab);
  PiszPunkt(pt);
  while(1 == 1){

    printw("---------==|| WITAM ||==-----------\n\n");
    printw("1. Sproboj znalezc wyjscie z labiryntu.\n");
    printw("2. Znajdz najkrotsze wyjscie z labiryntu.\n");
    printw("3. Losuj nowe miejsce startu.\n");
    printw("4. Wyjdz z programu.\n");

    LICZBA = 100000;
    wybor = WezLiczbe();
    SkasujX(lab);
    erase();
    
    if(wybor == 1) {
      i = RozwLab(pt);
      if(i == FALSE) printw("Labirynt nie ma wyjscia.");
    }

    else if(wybor == 2){
      i = FindShortestPath(pt);
      RysujLab(lab2);
    }

    else if(wybor == 3){
      pt = LosujMiejsceStartu();
      RysujLab(lab);
    }
    
    else if(wybor == 4) goto koniec;
  }  

  
 koniec:
  endwin();
  return 0;
}
