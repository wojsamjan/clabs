/*  File: mazelib.h
 *
    Interfejs zawierający funkcje ułatwiające rozwiązywanie labiryntów.
 */


#ifndef mazelib_included
#define mazelib_included

#include "genlib.h"

/* W zmiennych typu `poinT' przechowujemy współrzędne punktów na płaszczyźnie. */

typedef struct {
  int x, y;
} pointT;

/* Typ `directionT' reprezentuje kierunki w których można poruszać się po labiryncie. */

typedef enum { North, East, South, West} directionT;
    
/* Funkcja czytająca labirynt z pliku o podanej nazwie.
   Labirynt jest zapamiętywany w strukturze danych zarządzanej przez funkcje
   tego modułu. Sama struktura danych powinna być zdefiniowana w pliku `mazelib.c'.

   Oto przykładowy labirynt (punkt w lewym górnym rogu powinien mieć
   współrzędne (0,0), a `S' wskazuje pozycję początkową):

          ###################
          # #       #     # #
          # ### ### # ### # #
          #     # # # #     #
          ####### # # ##### #
          #    S  # #   #   #
          # ##### # ### # ###
          # #   #   #   #   #
          # # # ##### ##### #
          #   # #     #   # #
          ##### # ##### # # #
          #     #     # #   #
          # ####### # ##### #
          # #     # #     # #
          # # # # ### ### # #
          # # # #   # #   # #
          # ### ### ### ### #
          #     #       #    
          ###################
 */   

void ReadMazeMap(string filename);

/* Funkcja zwraca współrzędne punktu początkowego, z którego mamy 
   znaleźć drogę do wyjścia. */

pointT  GetStartPosition(void);

/* Funkcja zwraca TRUE jeśli podany punkt jest poza labiryntem. */

bool OutsideMaze(pointT pt);


/* Funkcja zwraca TRUE, jeśli w podanym kierunku `dir' w pozycji `pt'
   jest ściana. */

bool WallExists(pointT pt, directionT dir);

/* Poniższe funkcje zacznaczają, odznaczają podany punkt
   oraz sprawdzają czy punkt jest zaznaczony. */

void MarkSquare(pointT pt);
void UnmarkSquare(pointT pt);
bool IsMarked(pointT pt);

                   
#endif
