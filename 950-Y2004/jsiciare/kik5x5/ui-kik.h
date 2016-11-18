/*  
 *  File: ui-kik.c
 *
 *  $Revision: 1.1.1.1 $
 *  $Date: 2004/01/24 10:39:05 $
 *
    Interfejs u¿ytkownika do gry w kó³ko i krzy¿yk.
 */

#ifndef UI_KIK_INCLUDED
#define UI_KIK_INCLUDED

#include "simpio.h"
#include "kik.h"


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

/*  Funkcja zwracaj±ca znak umieszczany na planszy 
    przez gracza wykonuj±cego ruch. */

char PlayerMark(playerT player);

#endif
