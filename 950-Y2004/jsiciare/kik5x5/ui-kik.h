/*  
 *  File: ui-kik.c
 *
 *  $Revision: 1.1.1.1 $
 *  $Date: 2004/01/24 10:39:05 $
 *
    Interfejs użytkownika do gry w kółko i krzyżyk.
 */

#ifndef UI_KIK_INCLUDED
#define UI_KIK_INCLUDED

#include "simpio.h"
#include "kik.h"


/*  Funkcja wyświetlająca instrukcję gry. */

void GiveInstructions(void);

/*  Funkcja wyświetla bieżący stan gry. */

void DisplayGame(stateT state);

/*  Funkcja umożliwiająca graczowi wykonanie ruchu.
    Zwraca numer podanego kwadratu. Jeśli gracz wykonał
    nieprawidłowy ruch, to funkcja ta umożliwia podanie
    poprawnego ruchu. */

moveT GetUserMove(stateT state);

/*  Funkcja wyświetlająca ruch komputera. */

void DisplayMove(moveT move);

/*  Funkcja wypisująca wynik gry. */

void AnnounceResults(stateT state);

/*  Funkcja zwracająca znak umieszczany na planszy 
    przez gracza wykonującego ruch. */

char PlayerMark(playerT player);

#endif
