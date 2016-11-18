#include <ncurses/ncurses.h>
typedef char *string;
typedef enum { North, East, South, West } directionT;

typedef struct {
	    int x, y;
} pointT;

typedef struct {
    char **linia;
    char flaga;
    int ilosc, iloscL, *dlugosciL;
    pointT exit;
} maze;

maze labirynt;

int ReadMazeMap(string);

pointT GetStartPosition(void);

void DlugosciLini(void);

bool OutsideMaze(pointT punkt);

bool WallExists(pointT pt, directionT dir);

pointT AdjacentPoint(pointT pt, directionT dir);

void Rysuj();

void MarkSquare(pointT pt);

void UnmarkSquare(pointT pt);

bool IsMarked(pointT pt);

#define Czas2 100000 /*Czas odstêpu pomiêdzy krokami w labiryncie*/

