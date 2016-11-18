/*  File: mazelib.h
 *
    Interfejs zawieraj±cy funkcje u³atwiaj±ce rozwi±zywanie labiryntów.
 */


#ifndef mazelib_included
#define mazelib_included

//#include "genlib.h"

#define MAX 1000

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

void ReadMazeMap(char *filename);

/* Funkcja zwraca wspó³rzêdne punktu pocz±tkowego, z którego mamy 
   znale¼æ drogê do wyj¶cia. */

pointT GetStartPosition(void);

/* Funkcja zwraca 1 jesli istnieje droga z punktu poczatkowego
   do wyjscia */

int SolveMaze(pointT pt);

/* Wyswietla labirynt stosujac ncurses */

void pokaz(int y);

/* Znajduje najkrotsza droge do wyjscia */

int FindPath(pointT path[],pointT pt);

void ShortestPath(pointT pt);

#endif
