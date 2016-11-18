/*  File: mazelib.c
 *
    Implementacja interfejsu z `mazelib.h'.
 */

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include "mazelib.h"
#include <stdio.h>

#define TERRAIN_NORMAL ' '
#define TERRAIN_WALL   '#'
#define TERRAIN_MARKED '.'
#define TERRAIN_START_POS 'S'


/* Struktura reprezentuj±ca pojedyncz± liniê labiryntu */
typedef struct {
    char* tab; /* tablica opisuj±ca liniê terenu labiryntu */
    size_t length; /* d³ugo¶æ tablicy */
} LabiryntLine;

/* Struktura danych do zapamiêtywania labiryntów, od
 * razu definiujemy g³ówny obiekt-labirynt */
static struct Labirynt {
    LabiryntLine* lines;    /* wska¼nik do tablicy linii reprezentuj±cych labirynt */
    size_t number_of_lines; /* liczba linii */
    pointT start_pos;       /* pozycja startowa */
} TheLabirynt;

/* Pomocnicze funkcja do ustawiania/pobierania typu terenu w okre¶lonym punkcie */
static void SetTerrain(pointT pt, char type) {
  TheLabirynt.lines[pt.y].tab[pt.x] = type;
}

static char GetTerrain(pointT pt) {
  return TheLabirynt.lines[pt.y].tab[pt.x];
}

/* Implementacje ekportowanych funkcji. */
void ReadMazeMap(string filename) {

  /* Pomocnicza funkcja zwracaj±ca liczbê linii w pliku -- przydatne,
   * aby wiedzieæ, ile pamiêci zaalokowaæ na dane z labiryntu */
  size_t numberOfLines(FILE* f) {
    int c;
    int count = 0;
    while ((c = fgetc(f)) != EOF)
      if (c == '\n')
        ++count;
    return count;
  }

  /* Na podstawie wczytanej linii akutalizuje stan labiryntu */
  void updateMaze(size_t maze_line) {
        char* tab = TheLabirynt.lines[maze_line].tab;
        while (*tab) {
              if (*tab == '\n') {
                    *tab = '\0';
                    TheLabirynt.lines[maze_line].length--;
                    return;
              } else if (*tab == TERRAIN_START_POS) {
                    TheLabirynt.start_pos.x = tab - TheLabirynt.lines[maze_line].tab;
                    TheLabirynt.start_pos.y = maze_line;
              } else if (*tab != TERRAIN_NORMAL && *tab != TERRAIN_WALL &&
                         *tab != TERRAIN_MARKED) {
                    printf("B³êdny format terenu '%c', uznajê to za ¶cianê\n", *tab);
                    *tab = TERRAIN_WALL;
              }
              ++tab;
        }
  }

  FILE* f;
  int i;
  size_t size;
  
  f = fopen(filename, "r");
  if (!f)
    return;
  TheLabirynt.number_of_lines = numberOfLines(f);
  fseek(f, 0, SEEK_SET);
  TheLabirynt.lines = malloc(sizeof(LabiryntLine) * TheLabirynt.number_of_lines);
  for (i = 0; i < TheLabirynt.number_of_lines; ++i) {
    TheLabirynt.lines[i].tab = NULL; size = 0;
    TheLabirynt.lines[i].length = 
          getline(&TheLabirynt.lines[i].tab, &size, f);
    updateMaze(i);
  }
}

pointT  GetStartPosition(void) {
  return TheLabirynt.start_pos;
}

bool OutsideMaze(pointT pt) {
  return (pt.y >= TheLabirynt.number_of_lines ||
	  pt.x >= TheLabirynt.lines[pt.y].length);
}

bool WallExists(pointT pt, directionT dir) {
  pointT adj = AdjacentPoint(pt, dir);
  if (OutsideMaze(adj))
        return FALSE;
  else
        return GetTerrain(adj) == TERRAIN_WALL;
}


void UnmarkSquare(pointT pt) {
  SetTerrain(pt, TERRAIN_NORMAL);
}

void MarkSquare(pointT pt) {
  SetTerrain(pt, TERRAIN_MARKED);
}

bool IsMarked(pointT pt) {
  return GetTerrain(pt) == TERRAIN_MARKED;
}

pointT AdjacentPoint(pointT pt, directionT dir) {
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

