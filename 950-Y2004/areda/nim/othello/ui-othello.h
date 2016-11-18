/*  
 *  File: ui-othello.c
 *
    Interfejs u¿ytkownika do gry w "Othello".
 */

#ifndef UI_OTHELLO_INCLUDED
#define UI_OTHELLO_INCLUDED

#include "simpio.h"
#include "othello.h"

/*  Funkcja wy¶wietlaj±ca instrukcjê gry. */

void GiveInstructions(void);

/*  Funkcja wy¶wietla bie¿±cy stan gry. */

void DisplayGame(stateT state);

/*  Funkcja umo¿liwiaj±ca graczowi wykonanie ruchu.
    Zwraca numer podanego kwadratu. Je¶li gracz wykona³
    nieprawid³owy ruch, to funkcja ta umo¿liwia podanie
    poprawnego ruchu. */

moveT GetUserMove(stateT state);

/*  Funkcja wy¶wietlaj±ca ruch komputera. */

void DisplayMove(moveT move);

/*  Funkcja wypisuj±ca wynik gry. */

void AnnounceResults(stateT state);

#endif
