/*  File: mazelib.c
 *
    Implementacja interfejsu z `mazelib.h'.
 */
#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h> //dla funkcji Random
#include "mazelib.h"

pointT path[MAXLAB];


/* Implementacje ekportowanych funkcji. */



void ReadMazeMap(char filename[]) {
  FILE *f;
  int y,z,coun=0;
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
	  lab[z].odl=MAXLAB+1;
	if(c=='W' || c=='w'){
	  fin[coun].x=lab[z].x;
	  fin[coun].y=lab[z].y;
	  lab[z].odl=MAXLAB+1;
	  coun++;
	}
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
	lab[z].odl=MAXLAB+1;
      if(c=='W' || c=='w'){
	fin[coun].x=lab[z].x;
	fin[coun].y=lab[z].y;
	lab[z].odl=MAXLAB+1;
	coun++;
      }
      if (c=='#')
	lab[z].odl=-1;
      lab[z].stan=c;
      lab[z].odw=c;
      z++;
    }
  }
  lab[z].stan='\0';
  start=GetStartPosition();
  fin[coun].x=-1;
  fin[coun].y=-1;
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

void MarkSquare(pointT pt) {
  int z;
  z=FindPoint(pt);
  lab[z].stan='X';
  lab[z].odw='X';
}

void UnmarkSquare(pointT pt) {
  int z;
  z=FindPoint(pt);
  if (lab[z].stan=='X')
    lab[z].stan=' ';
}

pointT NPoint(pointT pt, directionT dir) {
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

int FindPoint(pointT pt){
  int z=0;
  while (lab[z].stan!='\0'){
    if (lab[z].x==pt.x && lab[z].y==pt.y)
      break;
    z++;
  }
  return z;
}

int Random(int dol, int gora){
  struct timeval tv;
  gettimeofday(&tv, 0);
  srand(tv.tv_sec);
  
  return dol+(rand() % (gora-dol+1));
}

int ShortestPath(pointT pt){
  pointT last,newpt,temp,finish,kol[MAXLAB];
  int z=0,licznik=0,g,x,s,no=0,r,q;
  while (z<=MAXLAB){        //zerowanie tablicy kolejki
    kol[z].x=0;
    kol[z].y=0;
    z++;
  }

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
	  q=0;
	  while(fin[q].x!=-1){
	    if (newpt.x==fin[q].x && newpt.y==fin[q].y){
	      s=1;           //jesli newpt jest wyjsciem z labiryntu to s 
	      //przyjmuje 1 co jest podstawa do przerwania petli
	      finish.x=fin[q].x;
	      finish.y=fin[q].y;
	      break;
	    }
	    q++;
	  }
	  kol[0].x=newpt.x;   
	  kol[0].y=newpt.y;
	}
      }
    }
    if (s==1 || licznik >MAXLAB)    //jesli te warunki sa 
                                 //spelnione to przerywamy petle
      break;
    licznik++;
  }
  z=0;
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
    r=licznik;
  }else{
    r=0;
  }
  return r;
}

