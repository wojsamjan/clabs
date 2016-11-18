/*  
 *  File: minimax.c
 *
 *  $Revision: 1.1.1.1 $
 *  $Date: 2004/01/24 10:39:05 $
 *
    Uniwersalne funkcje do ka¿dej gry zaimplementowanej
    za pomoc± algorytmu minimax.
 */

#ifndef MINIMAX_INCLUDED
#define MINIMAX_INCLUDED

#include "kik.h"

/*  Funkcja ta znajduje najlepszy ruch dla gracza wykonuj±cego
    ruch. Parametr depth i sta³± MaxDepth u¿ywamy do ograniczenia
    g³êboko¶ci przeszukiwania w grach, w których taka pe³na 
    analiza nie jest wykonywalna. Funkcja zwraca najlepszy
    znaleziony ruch i zapisuje w podanej zmiennej ca³kowitej
    jego ocenê. */

moveT FindBestMove(stateT state, int depth, int *pRating);

/*  Funkcja ta wycenia pozycjê znajduj±c ocenê najlepszego
    ruchu w tej pozycji. */

moveT EvaluatePosition(stateT state, int depth);

/*  Funkcja opakowuj±ca funkcjê FindBestMove.  
    Tutaj wybierany jest ruch komputera. */

moveT ChooseComputerMove(stateT state);

#endif
