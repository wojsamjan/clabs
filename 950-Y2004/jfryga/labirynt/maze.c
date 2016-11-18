#include <stdlib.h>
#include "mazelib.h"

/* Funkcja `SolveMaze(pt)' próbuje znale¼æ drogê do wyj¶cia 
   z labiryntu z podanego punktu `pt'. Funkcja zwraca TRUE 
   je¶li jest taka droga, a FALSE w przeciwnym wypadku.
   Funkcja korzysta z rekurencji do rozwi±zania podlabiryntów
   powstaj±cych przez zaznaczenie bie¿±cego punktu 
   i przej¶cie o jeden krok dalej niezablokowanym przej¶ciem. */

static bool SolveMaze(pointT pt);
string MazeFile = "labirynt.txt";	/* nazwa pliku z labiryntem */

int main()
{
    ReadMazeMap(MazeFile);
    if (SolveMaze(GetStartPosition())) {
	printf("\n");
	printf
	    ("\nZaznaczone kwadraty pokazuja droge do wyjscia z labiryntu.\n\n");
    } else {
	printf("\nZ podanego punktu brak wyjscia z labiryntu.\n\n");
    }
    return EXIT_SUCCESS;
}

bool SolveMaze(pointT pt)
{
    directionT kier;
    pointT newp;
    if (OutsideMaze(pt)) {
	ShowMaze();
	return TRUE;
    }
    if (IsMarked(pt))
	return FALSE;
    MarkSquare(pt);
    for (kier = North; kier <= West; kier++) {
	if (!WallExists(pt, kier)) {
	    newp = AdjacentPoint(pt, kier);
	    if (SolveMaze(newp))
		return TRUE;
	}
    }
    UnmarkSquare(pt);
    return FALSE;
}
