/*
   $URL: http://manta.univ.gda.pl/svn/wb/labs/c/605-Ncurses/hello-utf.c $
   $Revision: 231 $
*/

#include <unistd.h>  /* sleep */
#include <time.h>
#include <locale.h>
#include <ncursesw/ncurses.h>

static WINDOW *tmwindow;    /* okienko z czasem i datą */

void init_screen(void)
{
  initscr();
  noecho();                 /* wyłącz echo klawiatury */
  raw();                    /* znaki dostępne zaraz po wpisaniu */
  nodelay(stdscr, TRUE);    /* włącz nieblokowane wywołania getch() */
  curs_set(0);              /* niewidoczny kursor */
  refresh();
}

void end_screen(void)
{
  endwin();
}

void init_tmwindow(void)
{
  tmwindow = newwin(13, 36, 5, 10);
  box(tmwindow, ACS_VLINE, ACS_HLINE);
}

static void update_tmwindow(void)
{
  time_t now = time(NULL);
  struct tm *t = localtime(&now);
  mvwprintw(tmwindow, 3, 6, "Czas: %d:%d:%d", t->tm_hour, t->tm_min, t->tm_sec);
  mvwprintw(tmwindow, 5, 6, "Data: %d-%d-%d", t->tm_mday, t->tm_mon+1, t->tm_year+1900);
  mvwprintw(tmwindow, 7, 6, "Naciśnij q aby zakończyć");
  wrefresh(tmwindow);
}

int main(int argc, char *argv[])
{
  setlocale(LC_ALL, "");

  init_screen();
  init_tmwindow();
  while (getch() != 'q') {
    update_tmwindow();
    sleep(1);
  }
  end_screen();
  
  /* teraz możemy skorzystać z printf */
  printf("koniec programu \"%s\"\n", argv[0]);
  return 0;
}
