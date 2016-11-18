/*  File: mazelib.c
 *
    Implementacja interfejsu z `mazelib.h'.
 */


#include "mazelib.h"

/* Struktura danych do zapamiêtywania labiryntów. */

typedef struct {
    char **lab;
    int szer;
    int wys;
} labirynT;

labirynT maze;


/* Implementacje ekportowanych funkcji. */

void ReadMazeMap(string filename)
{
    FILE *in;
    char c;
    int i, j;
    maze.wys = 0;
    maze.szer = -1;
    if (!(in = fopen(filename, "r")))
	perror("\n Blad otwarcia pliku wejsciowego. Plik nie istnieje.");

    while ((c = fgetc(in)) != EOF)	// zliczanie szerokosci i wysokosci
    {
	if (c == '\n')
	    maze.wys++;
	else if (maze.wys == 0)
	    maze.szer++;
    }
/* zalokowanie pamieci na labirynt */
    maze.lab = (char **) malloc(sizeof(char *) * maze.wys);
    for (i = 0; i <= maze.wys; i++)
	maze.lab[i] = (char *) malloc(sizeof(char) * maze.szer);


    rewind(in);
    i = j = 0;



    while ((c = fgetc(in)) != EOF) {
	if (j == maze.szer + 1) {
	    i++;
	    j = 0;
	}
	if (c != '\n') {
	    maze.lab[i][j] = c;
	    j++;
	}

    }
/*
printf("\n wysokosc  = %d",maze.wys);
printf("\n szerokosc = %d",maze.szer); 
*/
}

pointT GetStartPosition(void)
{
    int i = 0, j = 0;
    pointT pt = { 0, 0 };
    char c;
    printf("\n");
    for (i = 0; i <= maze.wys; i++)
	for (j = 0; j <= maze.szer; j++) {
	    c = maze.lab[i][j];
	    if ((c == 's') || (c == 'S')) {
		pt.x = j;
		pt.y = i;
	    }

	}
    return pt;
}

bool OutsideMaze(pointT pt)
{
    if ((pt.y == 0) || (pt.y == maze.wys) || (pt.x == 0)
	|| (pt.x == maze.szer)) {
	return TRUE;
    } else
	return FALSE;
}

bool WallExists(pointT pt, directionT dir)
{
    pointT newpt;
    newpt = AdjacentPoint(pt, dir);
    if (maze.lab[newpt.y][newpt.x] != ' ')
	return TRUE;
    else
	return FALSE;

}

void MarkSquare(pointT pt)
{
    maze.lab[pt.y][pt.x] = '.';
}

void UnmarkSquare(pointT pt)
{
    maze.lab[pt.y][pt.x] = ' ';
}

bool IsMarked(pointT pt)
{
    if (maze.lab[pt.y][pt.x] == '.')
	return TRUE;
    else
	return FALSE;
}

pointT AdjacentPoint(pointT pt, directionT dir)
{
    pointT newpt;
    newpt = pt;
    switch (dir) {
    case North:
	newpt.y++;
	break;
    case East:
	newpt.x++;
	break;
    case South:
	newpt.y--;
	break;
    case West:
	newpt.x--;
	break;
    }
    return newpt;
}

void ShowMaze(void)
{
    int a, b;
// int i;
    printf("\n");
    for (a = 0; a <= maze.wys; a++) {
	printf("\n");
	for (b = 0; b <= maze.szer; b++) {
	    if (maze.lab[a][b] == '.')
		printf("\033[1;32m%c\033[m", maze.lab[a][b]);
	    else
		printf("%c", maze.lab[a][b]);
	}
    }

/*for(i=0;i<maze.wys;i++)
 free(maze.lab[i]);
free(maze.lab);*/
}
