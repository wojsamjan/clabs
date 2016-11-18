/*  File: mazelib.h
 *
    Interfejs zawieraj±cy funkcje u³atwiaj±ce rozwi±zywanie labiryntów.
 */


#ifndef mazelib_included
#define mazelib_included

#include "genlib.h"

/* W zmiennych typu `poinT' przechowujemy wspó³rzêdne punktów na p³aszczy¼nie. */

typedef struct {
  int x, y;
} pointT;

/* Typ `directionT' reprezentuje kierunki w których mo¿na poruszaæ siê po labiryncie. */

typedef enum { North, East, South, West} directionT;
    
/* Funkcja czytaj±ca labirynt z pliku o podanej nazwie.
   Labirynt jest zapamiêtywany w strukturze danych zarz±dzanej przez funkcje
   tego modu³u. Sama struktura danych powinna byæ zdefiniowana w pliku `mazelib.c'.

   Oto przyk³adowy labirynt (punkt w lewym górnym rogu powinien mieæ
   wspó³rzêdne (0,0), a `S' wskazuje pozycjê pocz±tkow±):

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

/* Funkcja zwraca wspó³rzêdne punktu pocz±tkowego, z którego mamy 
   znale¼æ drogê do wyj¶cia. */

pointT  GetStartPosition(void);

/* Funkcja zwraca TRUE je¶li podany punkt jest poza labiryntem. */

bool OutsideMaze(pointT pt);


/* Funkcja zwraca TRUE, je¶li w podanym kierunku `dir' w pozycji `pt'
   jest ¶ciana. */

bool WallExists(pointT pt, directionT dir);

/* Poni¿sze funkcje zacznaczaj±, odznaczaj± podany punkt
   oraz sprawdzaj± czy punkt jest zaznaczony. */

void MarkSquare(pointT pt);
void UnmarkSquare(pointT pt);
bool IsMarked(pointT pt);

/* Funkcja zwraca wspó³rzêdne punktu o jeden krok dalej od podanego punktu `pt'
   w kierunku `dir'. */         
pointT AdjacentPoint(pointT pt, directionT dir);

#endif
