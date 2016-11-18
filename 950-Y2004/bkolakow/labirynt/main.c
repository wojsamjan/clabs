#include<stdio.h>
#include<stdlib.h>
#include "main.h"
#define wielkoscTablicy 10000	/* Wielko¶æ tablicy path */
#define NoSolution 1000000

bool SolveMaze(pointT);
int FindPath(pointT pt, pointT path[], int pathSize);
int Droga(pointT pt, pointT path[], int pathSize, int index);
int ShortestPathLength(pointT pt);

int main()
{
    int i, dlugosc_drogi, najkrotsza;
    string MazeFile = "labirynt.txt";
    char temp[1000];
    FILE *fp;
    pointT start, path[wielkoscTablicy];

    labirynt.flaga = '3';

    system("clear");

    while (labirynt.flaga != '1' && labirynt.flaga != '2') {
	printf
	    ("\n\nNACI¦NIJ <1> I <ENTER> JE¦LI CHCESZ URUCHOMIÆ PROGRAM Z PRZECHODZENIEM KROKOWYM\n(MO¯NA PRZE¦LEDZIÆ DZIA£ANIE ALGORYTMU JEDNAK JEST TO DO¦Æ WOLNE)\n\nNACI¦NIJ <2> I <ENTER> JE¦LI NIE CHCESZ CZEKAÆ I ZALE¯Y CI TYLKO NA ZNALEZIENIU WYJ¦CIA\nZ LABIRYNTU\n\n");
	labirynt.flaga = getchar();
	system("clear");
    }

    getchar();
    printf
	("Wpisz ¶cie¿kê dostêpu do pliku z labiryntem\n(je¶li nic nie wpiszesz domy¶lnie zostanie wybrany \"labirynt.txt\")\n");
    fgets(temp, 1000, stdin);
    temp[strlen(temp) - 1] = '\0';
    if (strlen(temp) != 0)
	MazeFile = temp;


    if (ReadMazeMap(MazeFile) == 1) {
	printf("\nB³±d otwarcia pliku: %s \n", MazeFile);
	return 1;
    }

    labirynt.dlugosciL = malloc(labirynt.iloscL * sizeof(int));

    DlugosciLini();

    start = GetStartPosition();

    if (start.x == -1 && start.y == -1) {
	printf
	    ("\nB³±d przy wczytywaniu punktu startowego!\nSprawdz w pliku ilosc punktów startowych!\n");
	return 2;
    }

    initscr();
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    color_set(2, 0);
    cbreak();
    noecho();


    if (SolveMaze(start)) {
	*(labirynt.linia[start.y] + start.x) = 'S';
	Rysuj();
	printw
	    ("\nKropki pokazuj± drogê do wyj¶cia z labiryntu.\nWynik koñcowy zosta³ zapisany do pliku out.\n\n\t\tNACI¦NIJ <ENTER>");
	refresh();
	getch();
	endwin();

	fp = fopen("out", "w");
	for (i = 0; i < labirynt.ilosc; i++)
	    fprintf(fp, "%c", *(labirynt.linia[0] + i));
	fprintf(fp,
		"\nOznaczenia:\n(S) - punkt startowy,\n(.) - ¶cie¿ka do wyj¶cia z labiryntu,\n");
	fprintf(fp,
		"(o) - punkt przez który przeszed³ algorytm, ale nie prowadzi on do wyjscia ");
	fprintf(fp,
		"lub tworzy pêtle,\n( ) - (spacja) korytarz labiryntu, przez który ");
	fprintf(fp, "nie przeszed³ algorytm\n(#) - ¶ciana.");
	fclose(fp);
    } else {
	*(labirynt.linia[start.y] + start.x) = 'S';
	Rysuj();
	printw("\nZ podanego punktu brak wyjscia\n\n\tNACI¦NIJ <ENTER>");
	refresh();
	getch();
	endwin();
    }
    usleep(500000);
    ReadMazeMap(MazeFile);

    start = GetStartPosition();

    if ((dlugosc_drogi = FindPath(start, path, wielkoscTablicy)) == 0)
	printf("\n Nie ma drogi do wyjscia.\n");
    else {
	printf
	    ("\n¦cie¿ka do wyj¶cia z labiryntu, który przechodzi³ algorytm\nzapisana za pomoc± wspó³rzêdnych:");
	for (i = 0; i < dlugosc_drogi; i++)
	    printf("\n(%d , %d)", path[i].x, path[i].y);
	printf("\n");
    }

    ReadMazeMap(MazeFile);
    start = GetStartPosition();

    if ((najkrotsza = ShortestPathLength(start)) == NoSolution);
    else
	printf("\nNajkrótsza droga ma d³ugo¶æ %d\n", ShortestPathLength(start));

    return 0;
}

bool SolveMaze(pointT tu_jestem)
{
    int i;
    pointT nowy;
    if (OutsideMaze(tu_jestem)) {
	labirynt.exit.x = tu_jestem.x;
	labirynt.exit.y = tu_jestem.y;
	return 1;
    }
    if (IsMarked(tu_jestem))
	return 0;
    MarkSquare(tu_jestem);
    if (labirynt.flaga == '1') {
	Rysuj();
	refresh();
	usleep(Czas2);
    }

    for (i = North; i <= West; i++) {
	if (!WallExists(tu_jestem, i)) {
	    nowy = AdjacentPoint(tu_jestem, i);

	    if (SolveMaze(nowy))
		return 1;
	}
    }

    UnmarkSquare(tu_jestem);
    if (labirynt.flaga == '1') {
	Rysuj();
	refresh();
	usleep(Czas2);
    }
    return 0;
}

int FindPath(pointT pt, pointT path[], int pathSize)
{
    return Droga(pt, path, pathSize, 0);
}

int Droga(pointT pt, pointT path[], int pathSize, int index)
{
    int i, dlugoscDrogi;
    pointT nowy;

    if (index >= pathSize)
	return 0;
    if (OutsideMaze(pt))
	return index;
    if (IsMarked(pt))
	return 0;

    MarkSquare(pt);
    path[index].x = pt.x;
    path[index].y = pt.y;


    for (i = North; i <= West; i++) {
	if (!WallExists(pt, i)) {
	    nowy = AdjacentPoint(pt, i);

	    if (dlugoscDrogi = Droga(nowy, path, pathSize, index + 1))
		return dlugoscDrogi;
	}
    }

    return 0;
}

int ShortestPathLength(pointT pt)
{
    int *drogi, i, zmiana;
    pointT krok, start;

    start.x = pt.x;
    start.y = pt.y;

    drogi = malloc(labirynt.ilosc * (sizeof(int)));

    for (i = 0; i < labirynt.ilosc; i++)
	drogi[i] = NoSolution;
    drogi[labirynt.linia[labirynt.exit.y] - labirynt.linia[0] +
	  labirynt.exit.x] = 0;

    while (zmiana != 0) {
	zmiana = 0;
	for (pt.y = 1; pt.y < labirynt.iloscL - 1; pt.y++)
	    for (pt.x = 1; pt.x < labirynt.dlugosciL[pt.y]; pt.x++) {
		if (*(labirynt.linia[pt.y] + pt.x) == '#')
		    continue;

		for (i = North; i <= West; i++) {
		    if (!WallExists(pt, i)) {
			krok = AdjacentPoint(pt, i);

			if (drogi
			    [labirynt.linia[pt.y] - labirynt.linia[0] +
			     pt.x] >
			    drogi[labirynt.linia[krok.y] -
				  labirynt.linia[0] + krok.x] + 1) {
			    drogi[labirynt.linia[pt.y] -
				  labirynt.linia[0] + pt.x] =
				drogi[labirynt.linia[krok.y] -
				      labirynt.linia[0] + krok.x] + 1;
			    zmiana++;
			}
		    }
		}
	    }
    }
    return (drogi[labirynt.linia[start.y] - labirynt.linia[0] + start.x]);
}
