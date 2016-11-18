/*  
 *  File: minimax.c
 *
 *  $Revision: 1.1.1.1 $
 *  $Date: 2004/01/24 10:39:46 $
 *
    Uniwersalne funkcje do ka¿dej gry zaimplementowanej
    za pomoc± algorytmu minimax.
 */

#ifndef MINIMAX_INCLUDED
#define MINIMAX_INCLUDED

#include "nim.h"

/*  Funkcja ta znajduje najlepszy ruch dla gracza wykonuj±cego
    ruch. Parametr depth i sta³± MaxDepth u¿ywamy do ograniczenia
    g³êboko¶ci przeszukiwania w grach, w których taka pe³na 
    analiza nie jest wykonywalna. Funkcja zwraca najlepszy
    znaleziony ruch i zapisuje w podanej zmiennej ca³kowitej
    jego ocenê. */

moveT FindBestMove(int st_tmp[], int n, int r);

//Zrezygnowa³em z implementacji funkcji 
//EvaluatePosition, z powodu prostoty operacji jakie mialaby
//ona u mnie wykonywaæ. (wybór 0 lub 1)
//Ruch mo¿e byæ u mnie oceniony na 0 lub 1,
//(ruch wygrywaj±cy lub przegrywaj±cy)
//Wybór ruchu dokonuje siê wewn±trz funkcji
//opisanych poni¿ej.

//moveT EvaluatePosition(stateT state, int depth);


moveT ChooseComputerMove(void);

int IsBadPosition(int st_tmp[]);

#endif
