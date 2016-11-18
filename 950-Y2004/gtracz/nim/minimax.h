/*  
 *  File: minimax.c
 *
 *  $Revision: 1.1.1.1 $
 *  $Date: 2004/01/24 10:40:46 $
 *
    Uniwersalne funkcje do ka¿dej gry zaimplementowanej
    za pomoc± algorytmu minimax.
 */

#ifndef MINIMAX_INCLUDED
#define MINIMAX_INCLUDED

#include "nim.h"

/* Funkcja wywolujaca funkcje ktora znajduje najlepszy ruch 
   na podstawie stsnu 'state'. Funkcja zwraca najlepszy ruch */

moveT ChooseComputerMove(stateT state);

#endif
