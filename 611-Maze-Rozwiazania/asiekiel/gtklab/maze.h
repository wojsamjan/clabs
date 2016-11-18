#ifndef INCLUDED__MAZE_H
#define INCLUDED__MAZE_H

#include <stdbool.h>
#include "mazelib.h"

/* Znajd¼ drogê do wyj¶cia */
bool SolveMaze(pointT pt);

/* D³ugo¶æ najkrótszej ¶cie¿ki */
#define NoSolution 100000
int ShortestPathLength(pointT pt);

/* Tablica wszystkich kierunków */
extern directionT all_directions[];

#endif

