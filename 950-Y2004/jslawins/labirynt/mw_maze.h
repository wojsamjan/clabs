/* Jakub S³awiñski (Slaughter House Entertainment Group)
 * plik nag³ówkowy do funkcji rozwi±zuj±cych problemy labiryntowe
 * mw_maze.h
 */

#include "mw_lib.h"

#ifndef _JS_MW_MAZE_H
#define _JS_MW_MAZE_H

struct { /* struktura do wynajdowania najkrótszej ¶cie¿ki */
	int xsize, ysize;
	int** powierzchnia;
} wyniki;

/* tablica trzymaj±ca mo¿liwe kierunki do przemieszczania siê */
extern kierunkiT tablica[];

int RozwiazLabirynt(punktT); /* rekurencyjne znajdowanie wyj¶cia */
void RysujLabirynt(int, int, char); /* wyrysowuje labirynt */
void RysujSciezke(int, punktT*, int); /* wyrysowuje scie¿kê */
void RysujInfo(int); /* wyrysowuje info */
int NajkrotszaSciezka(punktT); /* znajdowanie d³ugo¶ci najkrótszej ¶cie¿ki */
punktT* ZnajdzSciezke(punktT); /* wynajduje kolejne punkty ¶cie¿ki */

#endif
