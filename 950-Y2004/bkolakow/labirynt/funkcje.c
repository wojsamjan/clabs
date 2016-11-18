#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include"main.h"

int ReadMazeMap(string MazeFile)
{
    FILE *wsk_plik;
    char *temp, c;
    int iloscN = 0, ilosc = 0, temp_ilosc;
    int i, j;

    if ((wsk_plik = fopen(MazeFile, "r")) == NULL)
	return 1;
    else {
	temp = malloc(3 * sizeof(char));
	temp_ilosc = 3;

	while ((c = fgetc(wsk_plik)) != EOF) {
	    if (temp_ilosc - ilosc == 2)
		temp = realloc(temp,
			       (temp_ilosc =
				2 * temp_ilosc) * sizeof(char));

	    temp[ilosc] = c;
	    ilosc++;
	    if (c == '\n')
		iloscN++;
	}

	if (iloscN == 0) {
	    labirynt.linia = malloc((1) * sizeof(char *));
	    iloscN = 1;
	} else
	    labirynt.linia = malloc((iloscN) * sizeof(char *));

	j = 0;
	labirynt.linia[0] = temp;
	for (i = 1; i < ilosc - 1; i++) {
	    if (temp[i] == '\n')
		labirynt.linia[++j] = &temp[i + 1];
	}
    }
    fclose(wsk_plik);
    labirynt.ilosc = ilosc;
    labirynt.iloscL = j + 1;
    return 0;
}

pointT GetStartPosition(void)
{
    int x, y, ilosc_S = 0;
    pointT start;


    for (y = 0; y < labirynt.iloscL; y++)
	for (x = 0; x < labirynt.dlugosciL[y]; x++)
	    if (*(labirynt.linia[y] + x) == 's'
		|| *(labirynt.linia[y] + x) == 'S') {
		start.x = x;
		start.y = y;
		ilosc_S++;
	    }
    if (ilosc_S != 1) {
	start.x = -1;
	start.y = -1;
	return start;
    }

    return start;
}

void DlugosciLini(void)
{
    int i;

    for (i = 0; i < labirynt.iloscL - 1; i++) {
	labirynt.dlugosciL[i] = labirynt.linia[i + 1] - labirynt.linia[i];
	labirynt.dlugosciL[labirynt.iloscL - 1] =
	    labirynt.linia[0] + labirynt.ilosc - 1 -
	    (labirynt.linia[labirynt.iloscL - 1] - 1);
    }
}

bool OutsideMaze(pointT punkt)
{
    if (labirynt.dlugosciL[punkt.y] - 1 <= punkt.x)
	    return 1;
    if (punkt.x <= 0)
	    return 1;
    if (punkt.y >= (labirynt.iloscL -1) || punkt.y <= 0)
	    return 1;
    if (punkt.x>=labirynt.dlugosciL[punkt.y-1]-1)
	    return 1;
    if (punkt.x>=labirynt.dlugosciL[punkt.y+1]-1)
	    return 1;
    return 0;
}

void MarkSquare(pointT pt)
{
    *(labirynt.linia[pt.y] + pt.x) = '.';
}

void UnmarkSquare(pointT pt)
{
    *(labirynt.linia[pt.y] + pt.x) = 'o';
}

bool IsMarked(pointT pt)
{
    if (*(labirynt.linia[pt.y] + pt.x) == '.'|| *(labirynt.linia[pt.y] + pt.x) == 'o')
	return 1;
    else
	return 0;
}

bool WallExists(pointT pt, directionT dir)
{
    switch (dir) {
    case North:
	pt.y -= 1;
	if (*(labirynt.linia[pt.y] + pt.x) == '#')
	    return 1;
	else
	    return 0;
    case East:
	pt.x += 1;
	if (*(labirynt.linia[pt.y] + pt.x) == '#')
	    return 1;
	else
	    return 0;
    case South:
	pt.y += 1;
	if (*(labirynt.linia[pt.y] + pt.x) == '#')
	    return 1;
	else
	    return 0;
    case West:
	pt.x -= 1;
	if (*(labirynt.linia[pt.y] + pt.x) == '#')
	    return 1;
	else
	    return 0;
    }
}

pointT AdjacentPoint(pointT pt, directionT dir)
{
    pointT newpt;
    newpt = pt;
    switch (dir) {
    case North:
	newpt.y--;
	break;
    case East:
	newpt.x++;
	break;
    case South:
	newpt.y++;
	break;
    case West:
	newpt.x--;
	break;
    }
    return newpt;
}

void Rysuj()
{
	int i,j;

	for(i=0; i<labirynt.iloscL;i++)
		for(j=0;j<labirynt.dlugosciL[i];j++)
		{
			if (*(labirynt.linia[i] + j) == 'o')
				mvprintw(i,j," ");
			else if(*(labirynt.linia[i] + j) == '#')
			{
				color_set(1,0);
				mvprintw(i,j,"%c",*(labirynt.linia[i] + j));
				color_set(2,0);
			}
			else
				mvprintw(i,j,"%c",*(labirynt.linia[i] + j));
		}
}
