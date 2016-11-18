/*  
 *  Plik: main.c
 *
 *  $Revision: 1.1.1.1 $
 *  $Date: 2004/01/24 10:39:46 $
 *
    Funkcja g³ówna do gry NIM.
 
    Zadanie:
      Zaimplementowaæ interfejs `minimax.h' oraz 
      zaprojektowaæ i zaimplementowaæ interfejs `nim.h',
      tak aby po skonsolidowaniu z funkcj± main
      powsta³ dzia³aj±cy program.
 */

#include <stdio.h>
#include <stdlib.h>
#include "nim.h"
#include "minimax.h"

int main()
{
    stateT state;
    moveT move;

    initscr();
    start_color();
    cbreak();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    init_pair(4, COLOR_GREEN, COLOR_BLACK);
    color_set(2, 0);

    state = NewGame();
    GiveInstructions();

    while (!GameIsOver()) {
	switch (state) {
	case Human:
	    DisplayGame();
	    move = GetUserMove();
	    state = Computer;
	    break;
	case Computer:
	    DisplayGame();
	    move = ChooseComputerMove();
	    DisplayMove(move);
	    getchar();
	    state = Human;
	    break;
	}
	MakeMove(move);
    }
    DisplayGame();
    AnnounceResults(state);
    endwin();
    return EXIT_SUCCESS;
}
