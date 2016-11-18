/* Jakub S³awiñski (Slaughter House Entertainment Group)
 * plik implementuj±cy obs³ugê grafiki
 * grafika.c
 */

#include <stdarg.h> /* dla obs³ugi zmiennej ilo¶ci argumentów */
#include <string.h> /* dla m.in. strlen */
#include <stdlib.h> /* dla m.in stdlib.h */
#include "grafika.h"

WINDOW *mainwin, *infowin, *splitwin;
static int mainkol;
static int infokol;
static int kolumny;
static int wiersze;

void
Inicjuj(void)
{
	int i;
	setenv("TERM", "linux", 1);
	initscr();
	cbreak();
	noecho();
	nonl();
	mainwin = newwin(LINES-5, COLS, 0, 0);
	infowin = newwin(4, COLS, LINES-4, 0);
	splitwin = newwin(1, COLS, LINES-5, 0);
	keypad(mainwin, TRUE);
	if (has_colors()) {
		start_color();
		init_pair( 1, COLOR_WHITE, COLOR_BLUE);
		init_pair( 2, COLOR_BLUE, COLOR_BLACK);
		init_pair( 3, COLOR_MAGENTA, COLOR_BLACK);
		init_pair( 4, COLOR_CYAN, COLOR_BLACK);
		init_pair( 5, COLOR_GREEN, COLOR_BLACK);
		init_pair( 6, COLOR_WHITE, COLOR_BLACK);
		init_pair( 7, COLOR_RED, COLOR_BLACK);
		init_pair( 8, COLOR_YELLOW, COLOR_BLACK);
		init_pair( 9, COLOR_BLUE, COLOR_BLUE);
	}
	werase( mainwin);
	werase( infowin);
	werase( splitwin);
	wbkgdset( splitwin, COLOR_PAIR(9));
	for (i = 0; i < COLS; ++i)
		waddch( splitwin, ' ');
	Odswiez();
	kolumny = COLS;
	wiersze = LINES;
}

void
Zakoncz(void)
{
	endwin();
}

void
Odswiez(void)
{
	wnoutrefresh( mainwin );
	wnoutrefresh( infowin );
	wnoutrefresh( splitwin );
	doupdate();
}

void
PiszNaMain(int kol, int x, int y, char* napis, ...)
{
	va_list ap;
	va_start(ap, napis);
	if (mainkol != kol) {
		wattron(mainwin, COLOR_PAIR(kol));
		mainkol = kol;
	}
	if (x >= MaxEkranX()) return;
	if (y >= (MaxEkranY()-5)) return;
	wmove( mainwin, y, x);
	vwprintw( mainwin, napis, ap );
	va_end(ap);
}

void
PiszNaMainS(int kol, int y, char* napis, ...)
{
	va_list ap;
	va_start(ap, napis);
	if (mainkol != kol) {
		wattron(mainwin, COLOR_PAIR(kol));
		mainkol = kol;
	}
	if (y >= (MaxEkranY()-5)) return;
	wmove( mainwin, y, (MaxEkranX()-strlen(napis))/2);
	vwprintw( mainwin, napis, ap );
	va_end(ap);
}

void
PiszNaInfo(int kol, int x, int y, char* napis, ...)
{
	va_list ap;
	va_start(ap, napis);
	if (infokol != kol) {
		wattron(infowin, COLOR_PAIR(kol));
		infokol = kol;
	}
	wmove( infowin, y, x);
	vwprintw( infowin, napis, ap );
	va_end(ap);
}

void
PiszNaInfoS(int kol, int y, char* napis, ...)
{
	va_list ap;
	va_start(ap, napis);
	if (infokol != kol) {
		wattron(infowin, COLOR_PAIR(kol));
		infokol = kol;
	}
	wmove( infowin, y, (MaxEkranX()-strlen(napis))/2);
	vwprintw( infowin, napis, ap );
	va_end(ap);
}

void
OczyscMain(void)
{
	werase( mainwin );
}

void
OczyscInfo(void)
{
	werase( infowin );
}

int
MaxEkranX(void)
{
	if (kolumny != COLS) {
		Zakoncz();
		Inicjuj();
	}
	return COLS;
}

int
MaxEkranY(void)
{
	if (wiersze != LINES) {
		Zakoncz();
		Inicjuj();
	}
	return LINES;
}

int
PobierzZnak(void)
{
	return wgetch(mainwin);
}
