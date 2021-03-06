/*  
 *  File: ui-othello.c
 *
    Interfejs użytkownika do gry w "Othello".
 */

#ifndef UI_OTHELLO_INCLUDED
#define UI_OTHELLO_INCLUDED

#include "simpio.h"
#include "othello.h"

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

#endif
