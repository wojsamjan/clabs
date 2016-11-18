#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <gtk/gtk.h>
#include "gui.h"


#define PROB 138


#define WALL '#'
#define FLOOR ' '

int MAXX=30;
int MAXY=30;

/* stos */

int stack[2*MAXLAB];
int sptr = 0;
int maxsptr = 0;


unsigned short randseed = 69;



int starty, endy;


int x,y;

char *sets = "1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
int setptr = 0;


char maze[31][31];

/* Zapisywanie do pliku */
void print_maze(char *NazwaPliku) {
  int x, y;
  FILE *plik;

  plik=fopen(NazwaPliku,"w"); 
  for(y=0; y<MAXY; y++) {
    for(x=0; x<MAXX; x++) {
      fprintf(plik,"%c",maze[x][y]);
    }
    fprintf(plik,"\n");
  }
  fclose(plik);
}


/* liczby losowe */
void randgen_init(void)
{
  randseed = time(NULL) % 256;
}

unsigned short rnd(void)
{
  randseed += 42; 
  randseed %= 256; 
  return(randseed);
}

/* wkladanie na stos */
void push(int n)
{
  if(sptr++ >2*MAXLAB) {
    printf(" *** Przepelnienie stosu\n");
    exit(1);
  } else {
    stack[sptr] = n;
  }
  if(sptr > maxsptr)
    maxsptr = sptr;
}
/* zdejmowanie ze stosu */
int pop(void)
{
  if(--sptr < 0) {
    printf(" *** Stos pusty\n");
    exit(1);
  } else {
    return(stack[sptr+1]);
  }
  return 0; 
}

void make_grid(void)
{
  for(y=0; y<MAXY; y++) {
    for(x=0; x<MAXX; x++) {
      maze[x][y]=FLOOR;
    }
  }

  /* wypelniam lewa i prawa granice */
  for(y=0; y<MAXY; y++) {
    maze[0][y] = WALL;
    maze[MAXX-1][y] = WALL;
  }

  /* Then the top/bottom sides */
  for(x=0; x<MAXX; x++) {
    maze[x][0] = WALL;
    maze[x][MAXY-1] = WALL;
  }


  for(y=0; y<MAXY; y += 2) {
    for(x=0; x<MAXX; x++) {
      maze[x][y] = WALL;
    }
  }
  for(y=0; y<MAXY; y++) {
    maze[MAXX][y] = FLOOR;
  }
  for(x=0; x<MAXX; x += 2) {
    for(y=0; y<MAXY; y++) {
      maze[x][y] = WALL;
    }
  }
}

void dfs_set(int xx, int yy, char set, char retreat, int toend)
{
  int solved = 0;

  x = xx; y = yy;

  push(x);
  push(y);

  while(solved == 0 && sptr > 0) {
    if(sptr>=MAXLAB)
      solved = 1;

    maze[x][y] = set;


    if(maze[x-1][y] == FLOOR) { 
      maze[x][y] = set;
      push(x);
      push(y);
      x = x-1;
    } else if(maze[x+1][y] == FLOOR) {
      maze[x][y] = set;
      push(x);
      push(y);
      x = x+1;
    } else if(maze[x][y+1] == FLOOR) { 
      maze[x][y] = set;
      push(x);
      push(y);
      y = y+1;
    } else if(maze[x][y-1] == FLOOR) { 
      maze[x][y] = set;
      push(x);
      push(y);
      y = y-1;
    } else {
      maze[x][y] = retreat;
      y = pop();
      x = pop();
    }
  }
}

void generate_maze(void)
{
  int dx, dy, q, liczba;
  int holes = 0;


  make_grid();

  for(x=2; x<(MAXX-1); x+=2) {
    for(y=1; y<(MAXY-1); y+=2) {
      if(rnd()<PROB) {
	maze[x][y] = FLOOR;
      }
    }
  }

  for(x=1; x<(MAXX-1); x+=2) {
    for(y=2; y<(MAXY-1); y+=2) {
      if(rnd()<PROB) {
	maze[x][y] = FLOOR;
      }
    }
  }

  for(dx=0; dx<MAXX; dx++) {
    for(dy=0; dy<MAXY; dy++) {
      if(maze[dx][dy] == FLOOR) {
	setptr++;
	dfs_set(dx, dy, sets[setptr], sets[setptr], 0);
	sptr=0;
      }
    }
  }
  for(dx=1; dx<(MAXX-1); dx++) {
    for(dy=1; dy<MAXY; dy++) {
      
      if(maze[dx][dy] == WALL &&
	 (maze[dx-1][dy] != maze[dx+1][dy]) &&
	 maze[dx-1][dy] != WALL && maze[dx+1][dy] != WALL &&
	 maze[dx-1][dy] != FLOOR && maze[dx-1][dy] != FLOOR) {

	maze[dx][dy] = FLOOR;
	holes++;
      }
    }
  }

  for(dx=0; dx<MAXX; dx++) {
    for(dy=0; dy<MAXY; dy++) {
      if((maze[dx][dy] != FLOOR) && (maze[dx][dy] != WALL))
	maze[dx][dy] = FLOOR;
    }
  }  
  x=rnd()%(MAXX-2)+1;
  for (y=1;y<MAXY-1;y++)
    maze[x][y]=FLOOR;
  y=rnd()%(MAXY-2)+1;
  for (x=1;x<MAXX-1;x++)
    maze[x][y]=FLOOR;
  maxsptr=0; sptr=0;
  x=rnd()%(MAXX-2)+1;
  y=rnd()%(MAXY-2)+1;
  maze[x][y]='S';
  liczba=rnd()%5+1;
  for (q=0;q<liczba;q++){
    while(1){
      x=rnd()%MAXX;
      y=rnd()%MAXY;
      if (x==0 || x==MAXX-1 ||
	  y==0 || y==MAXY-1)
	break;
    }
    maze[x][y]='W';
  }
   maxsptr=0; sptr=0; 
}


void generate(char *NazwaPliku)
{
  sptr=0;
  maxsptr=0;
  randgen_init();
  MAXX=rnd()%15+15;
  MAXY=rnd()%15+15;
  generate_maze();

  print_maze(NazwaPliku);

}

