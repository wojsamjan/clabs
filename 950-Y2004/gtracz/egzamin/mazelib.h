/*  File: mazelib.h
 *
    Interfejs zawieraj±cy funkcje u³atwiaj±ce rozwi±zywanie labiryntów.
 */


#ifndef mazelib_included
#define mazelib_included

//#include "genlib.h"

#define MAXLAB 1000

/* W zmiennych typu `poinT' przechowujemy wspó³rzêdne punktów na p³aszczy¼nie. */
typedef struct {
  int x, y;
} pointT;


typedef struct {
  int x,y;
  char stan;
  char odw;
  int odl;
} mazeT;


/* labirynt */
mazeT lab[MAXLAB];

/* tablica punktow koncowych */
pointT fin[10];


/* punkt startowy */
pointT start;

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

/* Wyswietla labirynt */

void DrawMove(int y);

/* Znajduje najkrotsza droge do wyjscia */

int ShortestPath(pointT pt);

void MarkSquare(pointT pt);

void UnmarkSquare(pointT pt);

/* Wyznacza wspolrzedne punktu lezacego w kierunku 'dir'
   od punktu 'pt'*/

pointT NPoint(pointT pt, directionT dir);

/* Funkcja zwraca indeks tablicy lab[] pod ktorym zapisany
   jest punkt 'pt'. */

int FindPoint(pointT pt);

/* Funkcja losujaca liczby z przedzialu od 'dol' do 'gora'.*/

int Random(int dol, int gora);


#endif
