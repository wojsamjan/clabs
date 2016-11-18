#include "mazelib.h"
#include <stdlib.h>
#include<unistd.h>
#include"random.h"
#include"cmaze.h"

#define bool
#include "ncurses/curses.h"

#define NoSolution 10000
#define MaxPath    1000

static bool SolveMaze(pointT pt);
static int FindPath(pointT pt, pointT path[], int pathSize);
static int ShortestPathLength(pointT pt);
static int Min(int *licznik);
static void Menu(void);
static bool MazeIsOk(string filename);

string MazeFile = "labirynt.txt";  /* nazwa pliku z labiryntem */

int main() {
	pointT path[MaxPath];
	int a,i,len,x,y;
	char opcja;
	initscr();
	curs_set(0);
	leaveok(stdscr, 1);
	if (has_colors())
	{
		start_color();
		init_pair(1, COLOR_GREEN, COLOR_BLACK);
		init_pair(2, COLOR_RED, COLOR_BLACK);
		init_pair(3, COLOR_WHITE, COLOR_BLACK);
		init_pair(4, COLOR_YELLOW, COLOR_BLACK);
	}
	while(1)
	{
	Menu();		/*wy¶wietlanie menu*/
	cbreak();
	opcja=getch();
	erase();
	switch (opcja)
	{
		case '1':
			if(!MazeIsOk(MazeFile)) return EXIT_FAILURE;
			a=ShortestPathLength(GetStartPosition());
			if (a!=NoSolution)
				printw("D³ugo¶æ najkrótszj ¶cie¿ki prowadz±cej do wyj¶cia to: %d\n\n",a);		
			else printw("Nie ma ¶cie¿ki prowadz±cej do wyj¶cia\n");
			break;
		case '2':
			if(!MazeIsOk(MazeFile)) return EXIT_FAILURE;
			if (SolveMaze(GetStartPosition())) 
			{
				printw("Zaznaczone kwadraty pokazuj± drogê do wyj¶cia z labiryntu.\n");
				for (i=0; i<Maze.lines; i++)
					printw("%s\n",Maze.maze[i]);
				refresh();
				noecho();
				getch();
				echo();
				erase();
			}
		       	else 
			{
				printw("Z podanego punktu brak wyj¶cia z labiryntu.\n");
			}
			break;
		case '3':
			if(!MazeIsOk(MazeFile)) return EXIT_FAILURE;
			len=FindPath(GetStartPosition(),path,MaxPath);
			if (len==0)
				printw("Nie ma wyj¶cia z labiryntu.\n");
			else {
				printw("¦cie¿ka prowadz±ca do wyj¶cia:\n\n");
			for (i=0; i<len-1; i++)
			printw("\t(%d,%d)",path[i].x,path[i].y);
			}
			break;
		case '4':
			if(!MazeIsOk(MazeFile)) return EXIT_FAILURE;
			len=FindPath(GetStartPosition(),path,MaxPath);
			if (len==0)
				printw("Nie ma wyj¶cia z labiryntu.\n");
			else {
				ReadMazeMap(MazeFile);
				attrset(COLOR_PAIR(1));
				for (i=0; i<Maze.lines; i++)
					printw("%s\n",Maze.maze[i]);
				refresh();
				sleep(1);
				attrset(COLOR_PAIR(2));
				attron(A_BOLD);
				for (i=0; i<len-1; i++)
				{
					move(path[i].y,path[i].x);
					addch('.');
					refresh();
					sleep(1);
				}
				attroff(A_BOLD);
				attrset(COLOR_PAIR(3));
				move(Maze.lines+1,0);
				refresh();
				noecho();
				getch();
				echo();
				erase();
			}	
			break;
		case '5':
			Randomize();
			x = RandomInteger(2,20);
			y = RandomInteger(2,10);
			CreateMazeInFile(MazeFile, 2*x + 1, 2*y + 1);
			for (i=0; i<Maze.lines; i++)
				printw("%s",Maze.maze[i]);
			refresh();
			noecho();
			getch();
			echo();
			erase();
			break;
		case '6': 
			endwin();
			return EXIT_SUCCESS;
		default: 
			printw("\nNie ma takiej pozycji w menu\n\n");
			refresh();
			break;
				 
	}
	}
	endwin();
    return EXIT_FAILURE;
}

/* Funkcja `SolveMaze(pt)' próbuje znale¼æ drogê do wyj¶cia 
   z labiryntu z podanego punktu `pt'. Funkcja zwraca TRUE 
   je¶li jest taka droga, a FALSE w przeciwnym wypadku.
   Funkcja korzysta z rekurencji do rozwi±zania podlabiryntów
   powstaj±cych przez zaznaczenie bie¿±cego punktu 
   i przej¶cie o jeden krok dalej niezablokowanym przej¶ciem. */

static bool SolveMaze(pointT pt) {
	int dir;
	pointT newpt;
	if (OutsideMaze(pt)) 
		return TRUE;
	if (IsMarked(pt))
		return FALSE;
	MarkSquare(pt);
	for (dir=0; dir<4; dir++)
		if (!WallExists(pt,dir))
		{
		newpt=AdjacentPoint(pt,dir);	
		if(SolveMaze(newpt))
				return TRUE;				
		
		}
	UnmarkSquare(pt);
	return FALSE;
}

/* ShortestPathLength: zwraca d³ugo¶æ najkrótszej drogi prowadz±cej do wyj¶cia
 * z labiryntu z podanego punktu. Je¶li nie ma ¶cie¿ki prowadz±cej do wyj¶cia, 
 * to funkcja ShortestPathLength zwraca sta³± NoSolution, wiêksz± od maksymalnej
 * mo¿liwej d³ugo¶ci ¶cie¿ki */

static int ShortestPathLength(pointT pt) {
	int dir,licznik[4];
	pointT newpt;
	/*printw("(%d, %d) ",pt.x+1,pt.y+1);*/
	if (OutsideMaze(pt)) 
		return 0;
	if (IsMarked(pt))
		return NoSolution;
	MarkSquare(pt);
	for (dir=0; dir<4; dir++)
		if (!WallExists(pt,dir))
		{
			newpt=AdjacentPoint(pt,dir);	
			licznik[dir]=ShortestPathLength(newpt);
		}
		else licznik[dir]=NoSolution;
	/*printw("%d %d %d %d\n",licznik[0],licznik[1],licznik[2],licznik[3]);*/
	UnmarkSquare(pt);
	if(Min(licznik)<NoSolution)
			return Min(licznik)+1;
	return NoSolution;
}

/* FindPath: wstawia do tablicy 'path' o rozmiarze 'pathSize'
 * wspó³rzêdne punktów od pt do wyj¶cia z labiryntu.
 * Funkcja zwraca liczbê punktów na ¶cie¿ce lub 0 je¶li z 
 * podanego punktu nie ma ¶cie¿ki do wyj¶cia z labiryntu */

static int FindPath(pointT pt, pointT *path, int pathSize)
{
	int dir;
	int len;
	pointT newpt;
	path[0]=pt;
	if (OutsideMaze(pt)) 
		return 1;
	if (IsMarked(pt))
		return 0;
	MarkSquare(pt);
	for (dir=0; dir<4; dir++)
		if (!WallExists(pt,dir))
		{
			newpt=AdjacentPoint(pt,dir);	
			len=FindPath(newpt,path+1,pathSize);
			if (len!=0)
			{
				path[0]=pt;
				return len+1;				
			}
		}
	UnmarkSquare(pt);
	return 0;
}	

/* Min: zwraca warto¶æ najmniejszego elementu czteroelementowej
 * tablicy */

static int Min(int *licznik)
{
	int i,min=licznik[0];
	for(i=1; i<4; i++)
		if(min>licznik[i])
			min=licznik[i];
	return min;
}

/* Menu: drukuje munu wyboru */

static void Menu(void)
{
	attrset(COLOR_PAIR(4));
	attron(A_BOLD);
	printw("\nWybierz opcjê:\n");
	attroff(A_BOLD);
	printw("1. D³ugo¶æ najkrótszej ¶cie¿ki prowadz±cej do wyj¶cia z labiryntu\n");
	printw("2. Poka¿ jedno z rozwi±zañ labiryntu\n");
	printw("3. Umie¶æ rozwi±zanie labiryntu w tablicy\n");
	printw("4. Poka¿ rozwi±zanie labiryntu z u¿yciem ncurses\n");
	printw("5. Wygeneruj nowy labirynt\n");
	printw("6. Wyj¶cie\n");
	refresh();
	attrset(COLOR_PAIR(3));
}
/* MazeIsOk: funkcja zwraca TRUE je¶li istnieje plik o podanej nazwie, 
 * jest w nim punkt startowy oraz labirynt mie¶ci siê na ekranie
 * w przeciwnym wypadku zwraca FALSE */

static bool MazeIsOk(string filename)
{
		FILE *file;
		pointT start;
		file=fopen(filename,"r");
		if (file==NULL)
		{
			printw("Nie moge odczytaæ pliku\n");
			refresh();
			sleep(1);
			endwin();
			return FALSE;
		}
		ReadMazeMap(filename);
		start=GetStartPosition();
		if(start.x==-1)
		{
			printw("Nie ma pozycji startowej\n");
			refresh();
			sleep(1);
			endwin();
			return FALSE;
		}
    		if (LINES < Maze.lines + 1) 
		{
			printw("Minimalna d³ugo¶æ ekranu: %d linii\n", Maze.lines + 1 );
			refresh();
			sleep(1);
			endwin();
			return FALSE;
		}
		return TRUE;
}

