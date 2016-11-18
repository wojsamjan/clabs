/*
     $URL: http://manta.univ.gda.pl/svn/wb/labs/c/605-Ncurses/hello.c $
     $Revision: 232 $
 */

#include <ncursesw/ncurses.h>
#include <locale.h>

int main()
{
    setlocale(LC_ALL, "");    /*  inicjalizacja locales  */
    initscr();		      /*  inicializacja trybu curses  */
    move(4, 32);              /*  przesuń kursor: y = 4, x = 32  */
    printw("witaj świecie");  /*  wypisz <q>witaj świecie</q> na <i>curscr</i>  */
    refresh();		      /*  przepisz na <i>stdscr</i>  */
    getch();		      /*  czekaj aż użytkownik coś naciśnie  */
    endwin();		      /*  zakończ tryb curses  */

    return 0;
}
