#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "maze.h"

#if   SIZE==TINY
#define WIDTH  5
#define HEIGHT WIDTH
#elif SIZE==SMALL
#define WIDTH  13
#define HEIGHT WIDTH
#elif SIZE==MEDIUM
#define WIDTH  21
#define HEIGHT WIDTH
#else
#define WIDTH  71
#define HEIGHT 23
#endif


typedef struct {
    int x;
    int y;
    int abs[4];
} labirynt;

void CreateMaze();
void CreateBoard();
void TrackMaze(int pStack);
int CheckAbbilities(int pStack);
void MakeStep(int pStack, int direction);
void CreateEnter();
void CreateExit();
void ShowMaze();

void SolveMaze(int pPathstack);
int CheckPath(int pPathstack);
void MakeStepOnPath(int pPathstack, int direction);



char maze[HEIGHT][WIDTH];

labirynt dedal = { -100, -100, {0, 0, 0, 0} };
labirynt stack[WIDTH * HEIGHT];
labirynt pathstack[WIDTH * HEIGHT];

int pStack = 0, pPathstack = 0, direction, wybiera = 1, enter = 0, finish = 0;

WINDOW *pierwsze, *drugie;

enum { EAST, NORTH, WEST, SOUTH };

int main(int argc, char *argv[])
{
    srand(time(NULL));
    CreateMaze();
    return 0;
}




void CreateMaze()
{
    stack[pStack++] = dedal;

    CreateBoard();

    stack[pStack].x = 1;
    stack[pStack].y = 1;

    CheckAbbilities(pStack);

    TrackMaze(pStack);
}




void TrackMaze(int pStack)
{
    if (pStack) {

	if (CheckAbbilities(pStack)) {

	    wybiera = 1;

	    while (wybiera) {
		direction = (int) (4.0 * rand() / (RAND_MAX + 1.0));
		if (stack[pStack].abs[direction])
		    wybiera = 0;
	    }

	    MakeStep(pStack, direction);

	    TrackMaze(pStack + 1);
	} else {
	    TrackMaze(pStack - 1);
	}

    } else {
	CreateExit();
	CreateEnter();
	ShowMaze();
    }

}



void CreateEnter()
{
    do {
	enter = (int) rand() % (WIDTH - 1);
    } while (maze[1][enter] != PATH);

    maze[0][enter] = PATH;
}


void CreateExit()
{

    do {
	finish = (int) rand() % (WIDTH - 1);
    } while (maze[HEIGHT - 2][finish] != PATH);

    maze[HEIGHT - 1][finish] = PATH;
}





int CheckAbbilities(int pStack)
{

    int dir;

    for (dir = 0; dir < 4; dir++) {
	switch (dir) {
	case EAST:
	    if (maze[stack[pStack].y][stack[pStack].x + 1] == WALL &&
		maze[stack[pStack].y][stack[pStack].x + 2] == WALL &&
		stack[pStack].x < WIDTH - 3) {
		stack[pStack].abs[EAST] = 1;
	    } else {
		stack[pStack].abs[EAST] = 0;
	    }
	    break;

	case NORTH:
	    if (maze[stack[pStack].y - 1][stack[pStack].x] == WALL &&
		maze[stack[pStack].y - 2][stack[pStack].x] == WALL &&
		stack[pStack].y > 2) {
		stack[pStack].abs[NORTH] = 1;
	    } else {
		stack[pStack].abs[NORTH] = 0;
	    }
	    break;

	case WEST:
	    if (maze[stack[pStack].y][stack[pStack].x - 1] == WALL &&
		maze[stack[pStack].y][stack[pStack].x - 2] == WALL &&
		stack[pStack].x > 2) {
		stack[pStack].abs[WEST] = 1;
	    } else {
		stack[pStack].abs[WEST] = 0;
	    }
	    break;

	case SOUTH:
	    if (maze[stack[pStack].y + 1][stack[pStack].x] == WALL &&
		maze[stack[pStack].y + 2][stack[pStack].x] == WALL &&
		stack[pStack].y < HEIGHT - 3) {
		stack[pStack].abs[SOUTH] = 1;
	    } else {
		stack[pStack].abs[SOUTH] = 0;
	    }
	    break;
	}
    }

    return stack[pStack].abs[EAST] | stack[pStack].
	abs[NORTH] | stack[pStack].abs[WEST] | stack[pStack].abs[SOUTH];

}


void MakeStep(int pStack, int direction)
{
    int a;

    switch (direction) {
    case EAST:
	for (a = 0; a <= 2; a++)
	    maze[stack[pStack].y][stack[pStack].x + a] = PATH;
	stack[pStack].abs[EAST] = 0;

	dedal.y = stack[pStack].y;
	dedal.x = stack[pStack].x + 2;
	break;

    case NORTH:
	for (a = 0; a <= 2; a++)
	    maze[stack[pStack].y - a][stack[pStack].x] = PATH;
	stack[pStack].abs[NORTH] = 0;

	dedal.y = stack[pStack].y - 2;
	dedal.x = stack[pStack].x;
	break;

    case WEST:
	for (a = 0; a <= 2; a++)
	    maze[stack[pStack].y][stack[pStack].x - a] = PATH;
	stack[pStack].abs[WEST] = 0;

	dedal.y = stack[pStack].y;
	dedal.x = stack[pStack].x - 2;
	break;

    case SOUTH:
	for (a = 0; a <= 2; a++)
	    maze[stack[pStack].y + a][stack[pStack].x] = PATH;
	stack[pStack].abs[SOUTH] = 0;

	dedal.y = stack[pStack].y + 2;
	dedal.x = stack[pStack].x;
	break;
    }

    stack[pStack + 1] = dedal;
    if (CheckAbbilities(pStack + 1))
	stack[++pStack] = dedal;
}




void CreateBoard()
{
    int x, y;

    for (y = 0; y < HEIGHT; y++) {
	for (x = 0; x < WIDTH; x++) {
	    maze[y][x] = WALL;
	}
    }
}



void ShowMaze()
{

    initscr();
    start_color();
    noecho();
    curs_set(0);


    pierwsze =
	newwin(HEIGHT, WIDTH, (LINES / 2 - HEIGHT / 2),
	       (COLS / 2 - WIDTH / 2) - 1);
    drugie =
	newwin(HEIGHT, WIDTH, (LINES / 2 - HEIGHT / 2),
	       (COLS / 2 - WIDTH / 2) - 1);

    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(1, COLOR_GREEN, COLOR_BLACK);

    wprintw(drugie, "%s", maze);

    wattrset(pierwsze, COLOR_PAIR(1));
    wattron(pierwsze, A_BLINK | A_BOLD);

    wattrset(drugie, COLOR_PAIR(2));
    wattron(drugie, A_BOLD);

    mvwaddch(pierwsze, 0, enter, FOUND);
    mvwaddch(drugie, 0, enter, TRACK);

    ++pPathstack;
    pathstack[pPathstack].y = 1;
    pathstack[pPathstack].x = enter;
    pathstack[pPathstack].abs[0] = 0;
    pathstack[pPathstack].abs[1] = 0;
    pathstack[pPathstack].abs[2] = 0;
    pathstack[pPathstack].abs[3] = 0;

    refresh();
    wrefresh(pierwsze);
    wrefresh(drugie);

    getch();

    SolveMaze(pPathstack);

    mvwaddch(pierwsze, HEIGHT - 1, finish, FOUND);
    mvwaddch(drugie, HEIGHT - 1, finish, TRACK);
    refresh();
    wrefresh(pierwsze);
    wrefresh(drugie);

    napms(SPEED);
    overlay(pierwsze, drugie);
    refresh();
    wrefresh(pierwsze);
    wrefresh(drugie);
    getch();
    delwin(pierwsze);
    delwin(drugie);
    endwin();

}


void SolveMaze(int pPathstack)
{

    int wybiera = 0;

    if (pathstack[pPathstack].y != HEIGHT - 1) {

	if (CheckPath(pPathstack)) {

	    wybiera = 1;

	    while (wybiera) {
		direction = (int) (4.0 * rand() / (RAND_MAX + 1.0));
		if (pathstack[pPathstack].abs[direction])
		    wybiera = 0;
	    }

	    mvwaddch(pierwsze, pathstack[pPathstack].y,
		     pathstack[pPathstack].x, FOUND);
	    mvwaddch(drugie, pathstack[pPathstack].y,
		     pathstack[pPathstack].x, TRACK);


#ifdef SMART

	    if (pathstack[pPathstack].y == HEIGHT - 2
		&& mvwinch(drugie, pathstack[pPathstack].y + 1,
			   pathstack[pPathstack].x) == PATH) {
		return;
	    }
#endif


	    MakeStepOnPath(pPathstack, direction);

	    refresh();
	    wrefresh(pierwsze);
	    wrefresh(drugie);
	    napms(SPEED);
	    SolveMaze(pPathstack + 1);
	} else {
	    mvwaddch(pierwsze, pathstack[pPathstack].y,
		     pathstack[pPathstack].x, FOUND);
	    mvwaddch(drugie, pathstack[pPathstack].y,
		     pathstack[pPathstack].x, TRACK);
	    refresh();
	    wrefresh(pierwsze);
	    wrefresh(drugie);
	    napms(SPEED / 2);

	    mvwaddch(pierwsze, pathstack[pPathstack].y,
		     pathstack[pPathstack].x, PATH);
	    mvwaddch(drugie, pathstack[pPathstack].y,
		     pathstack[pPathstack].x, PATH);
	    refresh();
	    wrefresh(pierwsze);
	    wrefresh(drugie);
	    napms(SPEED / 2);
	    SolveMaze(pPathstack - 1);
	}
    }
}


int CheckPath(int pPathstack)
{

    int dir;

    for (dir = EAST; dir <= SOUTH; dir++) {

	switch (dir) {

	case EAST:
	    if (mvwinch
		(drugie, pathstack[pPathstack].y,
		 pathstack[pPathstack].x + 1) == PATH
		&& pathstack[pPathstack].x < WIDTH - 2) {
		pathstack[pPathstack].abs[EAST] = 1;
	    } else {
		pathstack[pPathstack].abs[EAST] = 0;
	    }
	    break;

	case NORTH:
	    if (mvwinch
		(drugie, pathstack[pPathstack].y - 1,
		 pathstack[pPathstack].x) == PATH
		&& pathstack[pPathstack].y > 1) {
		pathstack[pPathstack].abs[NORTH] = 1;
	    } else {
		pathstack[pPathstack].abs[NORTH] = 0;
	    }
	    break;

	case WEST:
	    if (mvwinch
		(drugie, pathstack[pPathstack].y,
		 pathstack[pPathstack].x - 1) == PATH
		&& pathstack[pPathstack].x > 1) {
		pathstack[pPathstack].abs[WEST] = 1;
	    } else {
		pathstack[pPathstack].abs[WEST] = 0;
	    }
	    break;

	case SOUTH:
	    if (mvwinch
		(drugie, pathstack[pPathstack].y + 1,
		 pathstack[pPathstack].x) == PATH
		&& pathstack[pPathstack].y < HEIGHT - 1) {
		pathstack[pPathstack].abs[SOUTH] = 1;
	    } else {
		pathstack[pPathstack].abs[SOUTH] = 0;
	    }
	    break;
	}
    }

    return pathstack[pPathstack].abs[EAST] | pathstack[pPathstack].
	abs[NORTH] | pathstack[pPathstack].
	abs[WEST] | pathstack[pPathstack].abs[SOUTH];

}




void MakeStepOnPath(int pPathstack, int direction)
{


    switch (direction) {
    case EAST:
	pathstack[pPathstack].abs[EAST] = 0;
	dedal.y = pathstack[pPathstack].y;
	dedal.x = pathstack[pPathstack].x + 1;
	break;

    case NORTH:
	pathstack[pPathstack].abs[NORTH] = 0;
	dedal.y = pathstack[pPathstack].y - 1;
	dedal.x = pathstack[pPathstack].x;
	break;

    case WEST:
	pathstack[pPathstack].abs[WEST] = 0;
	dedal.y = pathstack[pPathstack].y;
	dedal.x = pathstack[pPathstack].x - 1;
	break;

    case SOUTH:
	pathstack[pPathstack].abs[SOUTH] = 0;
	dedal.y = pathstack[pPathstack].y + 1;
	dedal.x = pathstack[pPathstack].x;
	break;
    }

    pathstack[pPathstack + 1] = dedal;

}
