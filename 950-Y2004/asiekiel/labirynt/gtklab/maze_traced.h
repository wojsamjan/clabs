#ifndef INCLUDED__MAZE_TRACED_H
#define INCLUDED__MAZE_TRACED_H

#include "mazelib.h"

/* Funkcje ¶ledz±ce proces wyszukiwania wyj¶cia */

/* W jakim stanie zakoñczy³o siê wyszukiwanie */
bool maze_unsolved(void);
bool maze_exit_found(void);

/* Koñcowy punkt na ¶ledzonej ¶cie¿ce */
pointT current_point_traced(void);

/* Wykonaj jeden krok algorytmu */
bool solve_maze_step(void);

/* Zainicjalizuj/zwolnij struktury u¿ywane przez ten modu³ */
void solve_maze_by_step_init(void);
void solve_maze_by_step_cleanup(void);

#endif

