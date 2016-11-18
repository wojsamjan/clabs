/*  File: mazelib.c
 *
    Implementacja interfejsu z `mazelib.h'.
 */

#include "mazelib.h"

/* Jedyna nie eksportowana funkcja.
   Funkcja zwraca wspó³rzêdne punktu o jeden krok dalej od podanego punktu `pt'
   w kierunku `dir'. */         

static pointT AdjacentPoint(pointT pt, directionT dir);

/* Struktura danych do zapamiêtywania labiryntów. */

/* !!! */

/* definicja struktury maze + definicja zmiennej globalnej + funkcja opakowuj±ca AdjacentPoint */

typedef struct {
	int xsize, ysize;
	pointT startpos;
	char** powierzchnia;
} mazeT;

mazeT labirynt;

pointT
PunktObok(pointT pt, directionT dir)
{
	return AdjacentPoint(pt, dir);
}

/* !!! */

/* Implementacje ekportowanych funkcji. */

void ReadMazeMap(string filename) {
	FILE* plik = NULL;
	int sx, sy, n, znak;
	if (labirynt.powierzchnia != NULL) {
		for (n = 0; n < labirynt.xsize; ++n) {
			free(labirynt.powierzchnia[n]);
		}
		free(labirynt.powierzchnia);
	}
	sx = n = 0;
	sy = 1;
	plik = fopen(filename, "r");
	if (!plik) {
		printf("Nie mo¿na otworzyæ pliku!\n");
		exit(1);
	}
	while ((znak = fgetc(plik)) != EOF) {
		if (znak == '\n') {
			++sy;
			if (n > sx) {
				sx = n;
			}
			n = 0;
			continue;
		}
		++n;
	}
	labirynt.powierzchnia = calloc(1, sx * sizeof(char *));
	for (n = 0; n < sx; ++n) {
		labirynt.powierzchnia[n] = calloc(1, sy * sizeof(char));
	}
	labirynt.xsize = sx;
	labirynt.ysize = sy;
	rewind(plik);
	sy = 0;
	sx = 0;
	while ((znak = fgetc(plik)) != EOF) {
		if (znak == '\n') {
			++sy;
			sx = 0;
			continue;
		}
		if (znak == 'S') {
			labirynt.startpos.x = sx;
			labirynt.startpos.y = sy;
		}
		labirynt.powierzchnia[sx][sy] = znak;
		++sx;
	}
	fclose(plik);
}

pointT  GetStartPosition(void) {
  pointT pt;
  pt = labirynt.startpos; 
  return pt;
}

bool OutsideMaze(pointT pt) {
	if ((pt.x<0) || (pt.x>labirynt.xsize-1)) /* wspó³rzêdna x jest poza */
		return TRUE;
	if ((pt.y<0) || (pt.y>labirynt.ysize-1)) /* wspó³rzêdna y jest poza */
		return TRUE;
  return FALSE;
}

bool WallExists(pointT pt, directionT dir) {
	pointT punkt = AdjacentPoint(pt, dir);
	if (OutsideMaze(punkt))
		return FALSE;
	if (labirynt.powierzchnia[punkt.x][ punkt.y] == '#')
		return TRUE;
	return FALSE;
}

void MarkSquare(pointT pt) {
	if (labirynt.powierzchnia[pt.x][ pt.y] == ' ')
		labirynt.powierzchnia[pt.x][ pt.y] = 'x';
	if (labirynt.powierzchnia[pt.x][ pt.y] == 'S')
		labirynt.powierzchnia[pt.x][ pt.y] = 'X';
}

void UnmarkSquare(pointT pt) {
	if (labirynt.powierzchnia[pt.x][ pt.y] == 'x')
		labirynt.powierzchnia[pt.x][ pt.y] = 'p';
	if (labirynt.powierzchnia[pt.x][ pt.y] == 'X')
		labirynt.powierzchnia[pt.x][ pt.y] = 'S';
}

bool IsMarked(pointT pt) {
	if (labirynt.powierzchnia[pt.x][ pt.y] == 'x')
		return TRUE;
	if (labirynt.powierzchnia[pt.x][ pt.y] == 'X')
		return TRUE;
	if (labirynt.powierzchnia[pt.x][ pt.y] == 'p')
		return TRUE+1;
  return FALSE;
}

static pointT AdjacentPoint(pointT pt, directionT dir) {
  pointT newpt;
  newpt=pt;
  switch (dir) {
    case North: newpt.y--; break; /* !!! - by³o na odwrót !!!*/
    case East: newpt.x++; break;
    case South: newpt.y++; break; /* !!! - by³o na odwrót !!!*/
    case West: newpt.x--; break;    
  }
  return newpt;
}
