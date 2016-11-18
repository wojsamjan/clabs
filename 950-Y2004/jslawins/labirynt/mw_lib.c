/* Jakub S³awiñski (Slaughter House Entertainment Group)
 * plik implementuj±cy funkcje operuj±ce na labiryntach
 * mw_lib.c
 */

#include "mw_lib.h"
#include "myfunkc.h"
#include "mw_maze.h"
#include "grafika.h"
#include <string.h> /* dla memset */
#include <stdio.h>
#include <stdlib.h>

labiryntT labirynt; /* g³ówny labirynt */
labiryntT klientlab; /* labirynt klienta */

int
CzytajLabirynt(char* nazwa)
{
	FILE* plik = NULL;
	int sx, sy, n, znak;
	if (labirynt.powierzchnia != NULL) {
		for (n = 0; n < labirynt.xsize; ++n) {
			free(labirynt.powierzchnia[n]);
		}
		free(labirynt.powierzchnia);
		labirynt.xsize = 0;
		labirynt.ysize = 0;
	}
	sx = n = 0;
	sy = 1;
	plik = fopen(nazwa, "r");
	if (plik == NULL) {
		return 1;
	}
	while ((znak = fgetc(plik)) != EOF) {
		if ((znak != '\n') && (znak != ' ') && (znak != '#') &&
				(znak != 'S') && (znak != 'E'))
			return 1;
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
	return 0;
}

void
TworzSciezke(punktT pt, int kier)
{
	int i, j, los;
	char tab[4] = {0, 0, 0, 0};
	if (NaZewnatrz(pt, 0) || (!JestMur(pt, 0)))
		return;
	labirynt.powierzchnia[pt.x][pt.y] = ' ';
	switch (kier) {
		case 0: {
				labirynt.powierzchnia[pt.x][pt.y+1] = ' ';
				break;
			}
		case 1: {
				labirynt.powierzchnia[pt.x-1][pt.y] = ' ';
				break;
			}
		case 2: {
				labirynt.powierzchnia[pt.x][pt.y-1] = ' ';
				break;
			}
		case 3: {
				labirynt.powierzchnia[pt.x+1][pt.y] = ' ';
				break;
			}
	}
	for (i = 0; i < 4; ++i) {
		los = myrand(1, 4-i);
		for(j = 0; j < 4; ++j) {
			if (tab[j] == 0) {
				--los;
			}
			if (!los) {
				tab[j] = 1;
				break;
			}
		}
	    TworzSciezke(PunktObok(PunktObok(pt, tablica[j]), tablica[j]), j);
	}
}

int
GenerujLabirynt(int xsize, int ysize)
{
	int rozmx, rozmy;
	punktT iterator = {1, 1};
	rozmx = 2 * xsize + 3;
	rozmy = 2 * ysize + 3;
	PustyLabirynt(0, xsize, ysize, '#');
	TworzSciezke(iterator, 4);
	/* losowanie pocz±tku */
	iterator.x = myrand(1, rozmx-2);
	iterator.y = myrand(1, rozmy-2);
	while (JestMur(iterator, 0)) {
		iterator.y = (iterator.y+1) % rozmy;
	}
	labirynt.startpos = iterator;
	labirynt.powierzchnia[iterator.x][iterator.y] = 'S';
	/* losowanie koñca */
	iterator.x = myrand(1, rozmx-2);
	iterator.y = myrand(1, rozmy-2);
	while (JestMur(iterator, 0)||
			((iterator.x==labirynt.startpos.x)&&
			 (iterator.y==labirynt.startpos.y))) {
		iterator.y = (iterator.y+1) % rozmy;
		if (iterator.y == 0) {
			iterator.x = (iterator.x+1) % rozmx;
		}
	}
	labirynt.powierzchnia[iterator.x][iterator.y] = 'E';
	return 0;
}

int
PustyLabirynt(char ktory, int xsize, int ysize, char znak)
{
	labiryntT* lab;
	int n, rozmx, rozmy;
	if (ktory == 0)
		lab = &labirynt;
	else
		lab = &klientlab;
	rozmx = 2 * xsize + 3;
	rozmy = 2 * ysize + 3;
	if ((*lab).powierzchnia != NULL) {
		for (n = 0; n < (*lab).xsize; ++n) {
			free((*lab).powierzchnia[n]);
		}
		free((*lab).powierzchnia);
	}
	(*lab).powierzchnia = calloc(1, rozmx * sizeof(char *));
	for (n = 0; n < rozmx; ++n) {
		(*lab).powierzchnia[n] = calloc(1, rozmy * sizeof(char));
		memset((*lab).powierzchnia[n], znak, rozmy);
	}
	(*lab).xsize = rozmx;
	(*lab).ysize = rozmy;
	return 0;
}


punktT
PobierzStart(void)
{
  punktT pt;
  pt = labirynt.startpos; 
  return pt;
}

int
NaZewnatrz(punktT pt, char typ)
{
	if (typ==0) {
	if ((pt.x<0) || (pt.x>labirynt.xsize-1)) /* wspó³rzêdna x jest poza */
		return 1;
	if ((pt.y<0) || (pt.y>labirynt.ysize-1)) /* wspó³rzêdna y jest poza */
		return 1;
	if (labirynt.powierzchnia[pt.x][pt.y] == 'E')
		return 2;
	}
	else {
	if ((pt.x<0) || (pt.x>klientlab.xsize-1)) /* wspó³rzêdna x jest poza */
		return 1;
	if ((pt.y<0) || (pt.y>klientlab.ysize-1)) /* wspó³rzêdna y jest poza */
		return 1;
	if (klientlab.powierzchnia[pt.x][pt.y] == 'E')
		return 2;
	}
  return 0;
}

int
JestMur(punktT pt, char typ)
{
	if (NaZewnatrz(pt, typ))
		return 0;
	if (typ==0) {
	if (labirynt.powierzchnia[pt.x][ pt.y] == '#')
		return 1;
	}
	else {
	if (klientlab.powierzchnia[pt.x][ pt.y] == '#')
		return 1;
	}
	return 0;
}

void
Zaznacz(punktT pt, char typ)
{
	if (typ==0) {
	if (labirynt.powierzchnia[pt.x][ pt.y] == ' ')
		labirynt.powierzchnia[pt.x][ pt.y] = 'x';
	if (labirynt.powierzchnia[pt.x][ pt.y] == 'S')
		labirynt.powierzchnia[pt.x][ pt.y] = 'X';
	}
	else {
		klientlab.powierzchnia[pt.x][ pt.y] = typ;
	}
}

void
Odznacz(punktT pt)
{
	if (labirynt.powierzchnia[pt.x][ pt.y] == 'x')
		labirynt.powierzchnia[pt.x][ pt.y] = 'p';
	if (labirynt.powierzchnia[pt.x][ pt.y] == 'X')
		labirynt.powierzchnia[pt.x][ pt.y] = 'S';
}

int
JestZaznaczone(punktT pt, char typ)
{
	if (typ==0) {
	if (labirynt.powierzchnia[pt.x][ pt.y] == 'x')
		return 1;
	if (labirynt.powierzchnia[pt.x][ pt.y] == 'X')
		return 1;
	if (labirynt.powierzchnia[pt.x][ pt.y] == 'p')
		return 2;
	}
	else {
	if (klientlab.powierzchnia[pt.x][ pt.y] == '.')
		return 1;
	}
  return 0;
}

punktT
PunktObok(punktT pt, kierunkiT dir) {
  punktT newpt;
  newpt=pt;
  switch (dir) {
    case North: newpt.y--; break;
    case East: newpt.x++; break;
    case South: newpt.y++; break;
    case West: newpt.x--; break;    
  }
  return newpt;
}

int
RozmiarX(char typ)
{
	if (typ==0)
		return labirynt.xsize;
	else
		return klientlab.xsize;
}

int
RozmiarY(char typ)
{
	if (typ==0)
		return labirynt.ysize;
	else
		return klientlab.ysize;
}

