
#include <stdlib.h>
#include "mazelib.h"

/* Funkcja `SolveMaze(pt)' próbuje znaleźć drogę do wyjścia 
   z labiryntu z podanego punktu `pt'. Funkcja zwraca TRUE 
   jeśli jest taka droga, a FALSE w przeciwnym wypadku.
   Funkcja korzysta z rekurencji do rozwiązania podlabiryntów
   powstających przez zaznaczenie bieżącego punktu 
   i przejście o jeden krok dalej niezablokowanym przejściem. */

static bool SolveMaze(pointT pt);

string MazeFile = "labirynt.txt";  /* nazwa pliku z labiryntem */

int main() {
  ReadMazeMap(MazeFile);
  if (SolveMaze(GetStartPosition())) {
    printf("Zaznaczone kwadraty pokazują drogę do wyjścia z labiryntu.\n\n");
  } else {
    printf("Z podanego punktu brak wyjścia z labiryntu.\n\n");
  }
  return EXIT_SUCCESS;
}

bool SolveMaze(pointT pt) {
   directionT dir;
   if (OutsideMaze(pt)) 
     return TRUE;
   if (IsMarked(pt)) 
     return FALSE;
   MarkSquare(pt);
   for (dir = North; dir <= West; dir++) {
     if (!WallExists(pt, dir))
       if (SolveMaze(AdjacentPoint(pt, dir)))
	 return TRUE;
   }
   UnmarkSquare(pt);
   return FALSE;
}
