/*  File: mazelib.c
 *
    Implementacja interfejsu z `mazelib.h'.
 */
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h> //dla funkcji Random
#include "mazelib.h"

//#define MAX 1000
/* Struktura danych do zapamiêtywania labiryntów. */

typedef struct {
  int x,y;
  char stan;
  char odw;
  int odl;
} mazeT;


mazeT lab[MAX];

pointT start;

pointT path[MAX];
/* ??? (podaj definicjê) */

/* Funkcja zwraca 1 jezeli punkt 'pt' lezy poza labiryntem. */       

static int OutsideMaze(pointT pt);


/* Funkcja zwraca TRUE, je¶li w podanym kierunku `dir' w pozycji `pt'
   jest ¶ciana. */

static int WallExists(pointT pt, directionT dir);

/* Poni¿sze funkcje zacznaczaj±, odznaczaj± podany punkt
   oraz sprawdzaj± czy punkt jest zaznaczony. */

static void MarkSquare(pointT pt);

static void UnmarkSquare(pointT pt);

static int IsMarked(pointT pt);

/* Wyznacza wspolrzedne punktu lezacego w kierunku 'dir'
   od punktu 'pt'*/

static pointT NPoint(pointT pt, directionT dir);

/* Funkcja zwraca indeks tablicy lab[] pod ktorym zapisany
   jest punkt 'pt'. */

static int FindPoint(pointT pt);

/* Funkcja losujaca liczby z przedzialu od 'dol' do 'gora'.*/

static int Random(int dol, int gora);

/* Implementacje ekportowanych funkcji. */



void ReadMazeMap(char filename[]) {
  FILE *f;
  int y,z;
  char c;
  f=fopen(filename,"r");
  z=0;
  y=0;
  lab[-1].y=0;
  lab[-1].x=-1;
  while ((c=getc(f))!=EOF){
    if (c=='\n'){
      lab[z].x=lab[z-1].x+1;
      lab[z].stan='e';
      z++;
      y++;
      lab[z].y=y;
      lab[z].x=0;
      if ((c=getc(f))!=EOF){
	if (c==' ')
	  lab[z].odl=MAX+1;
	if (c=='#')
	  lab[z].odl=-1;
	lab[z].stan=c;
	lab[z].odw=c;
      }else break;
      z++;
    }else{
      lab[z].y=lab[z-1].y;
      lab[z].x=lab[z-1].x+1;
      if (c==' ')
	lab[z].odl=MAX+1;
      if (c=='#')
	lab[z].odl=-1;
      lab[z].stan=c;
      lab[z].odw=c;
      z++;
    }
  }
  lab[z].stan='\0';
  start=GetStartPosition();
  pokaz(0);
  printw("Wczytano taki labirynt\n");
  printw("Nacisnij 'ENTER, aby go rozwiazac\n");
  refresh();
  getch();
  path[0].x=-1;
  path[0].y=-1;
}

pointT  GetStartPosition(void) {
  pointT pt;
  int z=0;
  while (lab[z].stan!='S')z++;
  pt.x=lab[z].x;
  pt.y=lab[z].y;
  return pt;
}

static int OutsideMaze(pointT pt) {
 int minX,maxX,minY,maxY,z,q,r=0;
 minY=-1;
 maxY=-1;
 z=0;
 while (lab[z].stan!='\0'){
   if (minY==-1)
     if (lab[z].stan=='#')
       minY=lab[z].y;
   if (maxY<lab[z].y)
     if(lab[z].stan=='#')
       maxY=lab[z].y;
   z++;
 }
 if (pt.y>maxY || pt.y<minY)
   r=1;//poza
 else{
   z=-1;
   do{
     z++;
     if (lab[z].y==pt.y-1)break;
   }while (lab[z].stan!='\0');
   minX=-1;
   q=z;
   maxX=-1;
   z=0;
   while (lab[z].stan!='\0'){
     if (minX==-1)
       if (lab[z].stan=='#')
	 minX=lab[z].x;
     if (maxX<lab[z].x)
       if(lab[z].stan=='#')
	 maxX=lab[z].x;
     z++;
   }
   if (pt.x>maxX || pt.x<minX)
     r=1;//poza
   else
     r=0;//wewnatrz
 }
 return r;
}

static int WallExists(pointT pt, directionT dir) {
  int r;
  pointT newpt;
  newpt=pt;
  switch(dir){
  case North:
    newpt.y--;
    if (OutsideMaze(newpt)==0){
      if (lab[FindPoint(newpt)].stan!=' '){
	r=1;
      }else{
	r=0;
      }
    }else{
      r=0;
    }break;
  case East:
    newpt.x++;
    if (OutsideMaze(newpt)==0){
      if (lab[FindPoint(newpt)].stan!=' '){
	r=1;
      }else{
	r=0;
      }
    }else{
      r=0;
    }break;
  case South:
    newpt.y++;
    if (OutsideMaze(newpt)==0){
      if (lab[FindPoint(newpt)].stan!=' '){
	r=1;
      }else{
	r=0;
      }
    }else{
      r=0;
    }break;
  case West:
    newpt.x--;
    if (OutsideMaze(newpt)==0){
      if (lab[FindPoint(newpt)].stan!=' '){
	r=1;
      }else{
	r=0;
      }
    }else{
      r=0;
    }break;
  }
  return r;
}

static void MarkSquare(pointT pt) {
  int z;
  z=FindPoint(pt);
  lab[z].stan='X';
  lab[z].odw='X';
}

static void UnmarkSquare(pointT pt) {
  int z;
  z=FindPoint(pt);
  if (lab[z].stan=='X')
    lab[z].stan=' ';
}

static int IsMarked(pointT pt) {
  int r;
  if (lab[FindPoint(pt)].odw=='X'){
    r=1;//odwiedzone
  }else{
    r=0;
  }
  return r;
}

static pointT NPoint(pointT pt, directionT dir) {
  pointT newpt;
  newpt=pt;
  switch (dir) {
    case North: newpt.y--; break;
    case East: newpt.x++; break;
    case South: newpt.y++; break;
    case West: newpt.x--; break;    
  }
  return newpt;
}

int SolveMaze(pointT pt) {
  int r,s,g,j;
  g=0;
  pokaz(100);
  if (OutsideMaze(pt)!=0){
    g=1;
  }else{
    if (IsMarked(pt)==1){
      g=0;
    }else{
      MarkSquare(pt);
      j=0;
      //for (s=0;s<4;s++){
      s=Random(0,3);
      while (j<4){
	s=s%4;
	j++;
	if (WallExists(pt,s)!=1 && g==0){
	  r=SolveMaze(NPoint(pt,s));
	  if(r==1){
	    g=1;
	  }
	}
      	s++;
      }
    }
  }

  if (g==0){
    UnmarkSquare(pt);
    pokaz(100);
    return 0;
  }else
    return 1;
}

void pokaz(int y){
  int g=0;
  clear();
  if (has_colors()==1){
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_BLUE, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    init_pair(4, COLOR_GREEN, COLOR_BLACK);
    init_pair(5, COLOR_RED, COLOR_BLACK);
    if (y==-1){
      g=0;
      lab[FindPoint(start)].stan='S';
      while (lab[g].stan!='\0'){
	if (lab[g].stan=='e')
	  printw("\n");
	else {
	  if(lab[g].stan=='#'){
	    attrset(COLOR_PAIR(1));
	    printw("%c",lab[g].stan);
	  }else
	    if (lab[g].stan=='X'){
	      attrset(COLOR_PAIR(3));
	      printw("%c",lab[g].stan);
	    }else{
	      if (lab[g].stan=='S'){
		attrset(COLOR_PAIR(5));
		printw("%c",lab[g].stan);
	      }else{
		if (lab[g].stan=='.'){
		  attrset(COLOR_PAIR(2));
		  printw("%c",lab[g].stan);
		}else{
		  attrset(COLOR_PAIR(1));
		  printw("%c",lab[g].stan);
		}
	      }
	    }
	}
	g++;
      }
      refresh();
    }else{
      g=0;
      lab[FindPoint(start)].stan='S';
      while (lab[g].stan!='\0'){
	if (lab[g].stan=='e')
	  printw("\n");
	else {
	  if(lab[g].stan=='#'){
	    attrset(COLOR_PAIR(1));
	    printw("%c",lab[g].stan);
	  }else
	    if (lab[g].stan=='X'){
	      attrset(COLOR_PAIR(4));
	      printw("%c",lab[g].stan);
	    }else{
	      if (lab[g].stan=='S'){
		attrset(COLOR_PAIR(5));
		printw("%c",lab[g].stan);
	      }else{
		attrset(COLOR_PAIR(1));
		printw("%c",lab[g].stan);
	      }
	    }
	}
	g++;
      }
      napms(y);
      refresh();
    }
  }else{
      g=0;
      lab[FindPoint(start)].stan='S';
      while (lab[g].stan!='\0'){
	if (lab[g].stan=='e')
	  printw("\n");
	else
	  printw("%c",lab[g].stan);
	g++;
      }
      refresh();
      napms(y);
  }
}

static int FindPoint(pointT pt){
  int z=0;
  while (lab[z].stan!='\0'){
    if (lab[z].x==pt.x && lab[z].y==pt.y)
      break;
    z++;
  }
  return z;
}

static int Random(int dol, int gora){
  struct timeval tv;
  gettimeofday(&tv, 0);
  srand(tv.tv_sec);
  
  return dol+(rand() % (gora-dol+1));
}

void ShortestPath(pointT pt){
  pointT last,newpt,temp,finish,kol[MAX];
  int z=0,licznik=0,g,x,s,no=0;;
  while (z<=MAX){        //zerowanie tablicy kolejki
    kol[z].x=0;
    kol[z].y=0;
    z++;
  }
  z=0;
  while (lab[z].stan!='\0')
    z++;
  last.x=lab[z-2].x;          //znajdowanie ostatniego elementu
  last.y=lab[z-2].y;
  z=0;
  while (lab[z].stan!='\0'){
    if ((lab[z].x==0 || lab[z].x==last.x
	 || lab[z].y==0 || lab[z].y==last.y) &&
	(lab[z].stan==' ' || lab[z].stan=='X'))  // jesli punkt ma wspolrzedne 
                                                 //na skraju i nie jest sciana
                                                 // to break
      break;
    z++;
  }
  finish.x=lab[z].x;        //zapisujemy je do zmiennej finish
  finish.y=lab[z].y;
  lab[FindPoint(pt)].odl=licznik;
  kol[0].x=pt.x;
  kol[0].y=pt.y;    // wprowadzamy do kolejki punkt startowy
  kol[1].x=-1;      // oraz wartownika
  kol[1].y=-1;
  licznik++;
  s=0;
  while(1){
    g=0;
    while (kol[g].x!=-1 && kol[g].y!=-1)
      g++;          //wyszukujemy ostatni element kolejki
    if (g==0){
      no=1;          // jesli jest on jedynym elementem jes wartownik 
                     //to przerywamy. oznacza to ze z labiryntu nie ma wyjscia
      break;
    }
    temp.x=kol[g-1].x;
    kol[g-1].x=-1;       //zapisujemy ostatni element do zmiennej temp
    temp.y=kol[g-1].y;
    kol[g-1].y=-1;
    g--;
    for (x=0;x<4;x++){
      newpt=NPoint(temp,x);    //zapisujemy wspolrzedne punktu polozonego
                               // w kierunku x od punktu temp
      if (lab[FindPoint(newpt)].stan!='#'){  // jesli nie jest on sciana 
	if (lab[FindPoint(newpt)].odl>licznik){ // a jego odleglosc nie 
                                                //jest mniejsza od licznika
	                                        // co oznacza ze juz tu bylismy
	  lab[FindPoint(newpt)].odl=licznik;  //to odleglosc ma wartosc licznik
	  g=0;
	  while (kol[g].x!=-1 && kol[g].y!=-1)
	    g++;
	  while (g>=0){
	    kol[g+1].x=kol[g].x;  // a wspolrzedne tego punktu dopisujemy 
                                  //na poczatek kolejki
	    kol[g+1].y=kol[g].y;
	    g--;
	  }
	  if (newpt.x==finish.x && newpt.y==finish.y)
	    s=1;           //jesli newpt jest wyjsciem z labiryntu to s 
	                   //przyjmuje 1 co jest podstawa do przerwania petli
	  kol[0].x=newpt.x;   
	  kol[0].y=newpt.y;
	}
      }
    }
    if (s==1 || licznik >MAX)    //jesli te warunki sa 
                                 //spelnione to przerywamy petle
      break;
    licznik++;
  }
  if (no!=1){  // jesli no == 1 to z naczy ze nie wyjscia z labiryntu
    licznik=0;
    temp.x=finish.x;
    temp.y=finish.y;
    g=0;
    while(1){
      lab[FindPoint(temp)].stan='.'; // ozaczamy wyjscie .
      licznik++;
      for (x=0;x<4;x++){
	last=NPoint(temp,x);   // last staje sie punktem w x-kierunku od temp
	if (lab[FindPoint(last)].stan=='S'){
	  g=1;  // jesli last jest punktem startowym to koniec
	  break;
      }
	if (lab[FindPoint(last)].odl<lab[FindPoint(temp)].odl && 
	    lab[FindPoint(last)].odl>0){ 
	  temp=NPoint(temp,x); //jesli odleglosc punktu last jest mniejsza 
	                       // od odleglosci punktu temp i nie jest ujemna
	                       // tzn. nie jest sciana to temp =last
	  break;
	}
      }
      if (g==1)
      break;
    }
  pokaz(-1);
  printw("Najkrotsza droga ma %d krokow\n",licznik);
  refresh();
  }else{
    pokaz(-1);
    printw("\nZ tego punktu nie ma drogi do wyjscia\n");
    refresh();
  }
}

int FindPath(pointT path[],pointT pt){
  int t,l,x,w=0;
  pointT newpt,temp;
  temp.x=pt.x;
  temp.y=pt.y;
  while(1){
    l=0;
    for (x=0;x<4;x++){
      newpt=NPoint(temp,x);
      t=FindPoint(newpt);
      if (lab[t].stan=='X' && lab[t].odw=='X'){
	path[w].x=newpt.x;
	path[w].y=newpt.y;
	w++;
	temp.x=newpt.x;
	temp.y=newpt.y;
	lab[t].odw=' ';
	l++;
      }
    }
    if (l==0)
      break;
  }
  return w;
}
