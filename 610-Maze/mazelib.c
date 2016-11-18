/*  File: mazelib.c
 *
    Implementacja interfejsu z `mazelib.h'.
 */

#include "mazelib.h"

/* Struktura danych do zapamiętywania labiryntów. */

/* ??? (podaj definicję) */

/* Jedyna nie eksportowana funkcja.
   Funkcja zwraca współrzędne punktu o jeden krok dalej od podanego punktu `pt'
   w kierunku `dir'. */         

static pointT AdjacentPoint(pointT pt, directionT dir);

/* Implementacje ekportowanych funkcji. */

void ReadMazeMap(string filename) {
  
}

pointT  GetStartPosition(void) {
  pointT pt = {0, 0};
  return pt;
}

bool OutsideMaze(pointT pt) {
  return TRUE;
}

bool WallExists(pointT pt, directionT dir) {
  return TRUE;
}

void MarkSquare(pointT pt) {

}

void UnmarkSquare(pointT pt) {

}

bool IsMarked(pointT pt) {

  return TRUE;
}

static pointT AdjacentPoint(pointT pt, directionT dir) {
  pointT newpt;
  newpt=pt;
  switch (dir) {
    case North: newpt.y++; break;
    case East: newpt.x++; break;
    case South: newpt.y--; break;
    case West: newpt.x--; break;    
  }
  return newpt;
}
