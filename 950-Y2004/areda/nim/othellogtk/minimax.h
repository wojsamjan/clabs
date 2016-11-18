/*  
 *  File: minimax.c
 *
    Uniwersalne funkcje do ka¿dej gry zaimplementowanej
    za pomoc± algorytmu minimax.
 */

#ifndef MINIMAX_INCLUDED
#define MINIMAX_INCLUDED

#include "othello.h"

/*  Funkcja ta znajduje najlepszy ruch dla gracza wykonuj±cego
    ruch. Parametr depth i sta³a MaxDepth u¿ywana jest do ograniczenia
    g³êboko¶ci przeszukiwania (w "Othello" pe³na analiza nie jest 
    wykonywalna.) Funkcja zwraca najlepszy znaleziony ruch i zapisuje 
    w podanej zmiennej ca³kowitej jego ocenê lub (-1,-1) gdy gracz nie 
    ma ruchu i musi spasowaæ */

moveT FindBestMove(stateT state, int depth, float *pRating);

/*  Funkcja ta wycenia pozycjê znajduj±c ocenê najlepszego
    ruchu w tej pozycji. */

float EvaluatePosition(stateT state, int depth);

/*  Funkcja opakowuj±ca funkcjê FindBestMove.  
    Tutaj wybierany jest ruch komputera. */

moveT ChooseComputerMove(stateT state);

#endif
