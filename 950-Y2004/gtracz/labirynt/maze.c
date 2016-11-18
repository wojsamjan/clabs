#include <ncurses.h>
#include <stdlib.h>
#include "mazelib.h"

/* Funkcja `SolveMaze(pt)' próbuje znale¼æ drogê do wyj¶cia 
   z labiryntu z podanego punktu `pt'. Funkcja zwraca TRUE 
   je¶li jest taka droga, a FALSE w przeciwnym wypadku.
   Funkcja korzysta z rekurencji do rozwi±zania podlabiryntów
   powstaj±cych przez zaznaczenie bie¿±cego punktu 
   i przej¶cie o jeden krok dalej niezablokowanym przej¶ciem. */


char MazeFile[] = "labirynt.txt";  /* nazwa pliku z labiryntem */

int main() {
  int t,s,q,c,k,x;
  pointT path[MAX];
  initscr();
  s=scrollok(stdscr,true);
  init_pair(1, COLOR_WHITE, COLOR_BLACK);
  init_pair(2, COLOR_BLUE, COLOR_BLACK);
  init_pair(3, COLOR_YELLOW, COLOR_BLACK);
  init_pair(4, COLOR_GREEN, COLOR_BLACK);
  init_pair(5, COLOR_RED, COLOR_BLACK);
  ReadMazeMap(MazeFile);
  do{
    s=0;
    clear();
    attrset(COLOR_PAIR(1));
    mvaddstr( 1 ,COLS/2-14,"********* M E N U *********");
    mvaddstr( 4 ,COLS/2-30,"1 - Rozwiaz labirynt zapisany w pliku \"labirynt.txt\"");
    mvaddstr( 7 ,COLS/2-30,"2 - Znajdz najkrotsza droge w labryncie z pliku \"labirynt.txt\"");
    mvaddstr( 10 ,COLS/2-30,"3 - Wyjscie");
    mvaddstr( 13 ,COLS/2-30,"Podaj numer opcji jakiej chcesz uzyc : ");
    refresh();
    c=getch();
    switch(c){
    case '1':
      t=SolveMaze(GetStartPosition());
      pokaz(-1);
      if (t==1){
	printw("Zaznaczone kwadraty pokazuj± drogê do wyj¶cia z labiryntu.\n");
	do{
	  q=0;
	  printw("Jesli chcesz wyswietlic wspolrzedne punktow tej drogi \nwpisz  - T, jesli nie - N : ");
	  refresh();
	  k=getch();
	  if (k=='T')
	    k='t';
	  if (k=='N')
	    k='n';
	  switch(k){
	  case 't':
	    t=FindPath(path,GetStartPosition());
	    pokaz(-1);
	    printw("Ta droga ma %d krokow\n",t);
	    printw("Wspolrzedne punktow tworzacych droge do wyjscia : ");
	    for (x=0;x<=t;x++){
	      if(x%(COLS/9)==0)
		printw("\n");
	      printw("(%d,%d) ",path[x].x,path[x].y);
	    }
	    printw("\n");
	    printw("Nacisnij ENTER aby zakonczyc");
	    break;
	  case 'n':
	    printw("\n");
	    printw("Nacisnij ENTER aby zakonczyc ");
	    break;
	  default :
	    q=1;
	    pokaz(-1);
	    printw("Musisz wpisac T dla \"TAK\" lub N dla \"NIE\" : ");
	    refresh();
	  break;
	  }
	}while(q==1);
      }else
	printw("Z podanego punktu brak wyj¶cia z labiryntu.\n");
      refresh();
      getch();
      break;
    case '2':
      ShortestPath(GetStartPosition());
      getch();
      break;
    case '3':
      break;
    default :
      s=1;
      mvaddstr(15,COLS/2-30,"Musisz wpisac 1, 2 lub 3 !!!\n Nacisnij ENTER aby kontynuowac");
      refresh();
      getch();
      break;
    }
  }while(s==1);
  endwin();
  return EXIT_SUCCESS;
}
