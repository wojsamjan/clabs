#include <string.h>
#include <ncurses/ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include "screen.h"

#define MAXX 20
#define MAXY 20
#define PLRCOLOR 9

// plansza, i kolory liczb na planszy
int board[MAXX][MAXY];
int colors[MAXX][MAXY];

/*
 * Wybiera pare kolorow na podstawie wpisanego indeksu koloru.
 */
int colorlevel(int level)
{
    switch (level)
    {
	case 0: return COLOR_PAIR(0);
	case 1: return COLOR_PAIR(4);
	case 2: return COLOR_PAIR(3) | A_BOLD;
	case 3: return COLOR_PAIR(6);
	case 4: return COLOR_PAIR(7) | A_BOLD;
	case 5: return COLOR_PAIR(2);
	case 6: return COLOR_PAIR(2) | A_BOLD;
	case 7: return COLOR_PAIR(7);
	case 8: return COLOR_PAIR(6) | A_BOLD;
	case 9: return COLOR_PAIR(3);
	case 10: return COLOR_PAIR(4) | A_BOLD;
	case 11: return COLOR_PAIR(1) | A_BOLD;
	default: return COLOR_PAIR(0);
    }
}

/*
 * rysowanie calej planszy
 */
void drawblocks()
{
    int x, y;
    
    for (y = 0; y < MAXY; y++)
	for (x = 0; x < MAXX; x++)
	    // zero = puste miejsce na planszy
	    if (board[x][y] == 0)
	    {
		attrset(COLOR_PAIR(0));
		mvaddstr(y, x * 4, "    ");
	    }
	    else
	    {
		attrset(colorlevel(colors[x][y]));
		mvprintw(y, x * 4, " %2d ", board[x][y]);
	    }
}

/* wypelnienie planszy i kolorow na poczatku losowymi wartosciami */
void fillboard()
{
    int x, y;

    for (y = 0; y < MAXY; y++)
	for (x = 0; x < MAXX; x++)
	{
	    board[x][y] = random() % 9;
	    colors[x][y] = random() % 5 + 1;
	}
}

/* rekurencyjne zaznaczanie kolorem gracza */
int recursive_count(int x, int y)
{
    int cnt = 1;
    colors[x][y] = PLRCOLOR;
    
    /* jesli punkt na lewo istnieje, i jeszcze nas tam nie bylo - wchodzimy tam */
    if (x > 0 && board[x-1][y] <= board[x][y] && colors[x-1][y] != PLRCOLOR)
	cnt += recursive_count(x-1, y);
    /* jw w gore */
    if (y > 0 && board[x][y-1] <= board[x][y] && colors[x][y-1] != PLRCOLOR)
	cnt += recursive_count(x, y-1);
    if (x < MAXX - 1 && board[x+1][y] <= board[x][y] && colors[x+1][y] != PLRCOLOR)
	cnt += recursive_count(x+1, y);
    if (y < MAXY - 1 && board[x][y+1] <= board[x][y] && colors[x][y+1] != PLRCOLOR)
	cnt += recursive_count(x, y+1);
    return cnt;
}

/* start rekurencji, wpisalismy nowa cyfre i trzeba pozaznaczac */
void pulldown(int x, int y, int num)
{
    if (board[x][y] != 0 || num == 0) return;
    board[x][y] = num;
    recursive_count(x, y);
}

int playwfall()
{
    int x, y, score = 0;
    
    // na poczatek kursor na srodek.
    x = MAXX / 2;
    y = MAXY / 2;
    
    while (1)
    {
	// wyrysuj
	drawblocks();
	// i kursor
	attrset(colorlevel(colors[x][y]));
	mvprintw(y, x * 4, "<%2d>", board[x][y]);
	// i punkty
	attrset(COLOR_PAIR(1));
	mvprintw(25, 0, "Score: %6d", score);
	refresh();
	
	switch (getch())
	{
	    case KEY_LEFT: if (x > 0) x--; break;
	    case KEY_RIGHT: if (x < MAXX - 1) x++; break;
	    case KEY_UP: if (y > 0) y--; break;
	    case KEY_DOWN: if (y < MAXY - 1) y++; break;
	
	    case KEY_ENTER:
	    case 13: case 10:
		if (board[x][y] == 0)
		{
		    char buf[20];
		    // wlacz z powrotem kursor edycyjny
		    curs_set(ttycursor);
		    // i wypisywanie wcisnietych klawiszy
		    echo();
		    // wyczysc miejsce pod wpis
		    mvaddstr(y, x * 4 + 1, "  ");
		    // i zapytaj usera
		    mvgetnstr(y, x * 4 + 1, buf, 2);
		    // ponownie wylacz kursor i echo
		    noecho();
		    ttycursor = curs_set(0);
		    // i zaznacz cyfry
		    pulldown(x, y, atoi(buf));
		    score += atoi(buf);
		}
		break;
	    case 'q':
		return 1;
	}
    }
}

int main()
{
    screen_init();
    // zainicjalizuj RNG
    srand(time(NULL));
    while (1)
    {
	fillboard();
	if (playwfall()) break;
    }
    screen_end();
    return 0;
}
