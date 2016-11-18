
#include <string.h>
#include <ncurses/ncurses.h>

int ttycursor;

void screen_init()
{
    initscr();
    noecho();
    cbreak();
    start_color();
    init_pair(0, COLOR_BLACK, COLOR_BLACK);
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_RED, COLOR_BLACK);
    init_pair(4, COLOR_BLUE, COLOR_BLACK);
    init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(6, COLOR_CYAN, COLOR_BLACK);
    init_pair(7, COLOR_YELLOW, COLOR_BLACK);
    
    keypad(stdscr, TRUE);
    //ttycursor = curs_set(0);
    bkgdset(COLOR_PAIR(0));
    clear();
    refresh();
}

void screen_end()
{
    endwin();
    //curs_set(ttycursor);
}

void centerln(int line, char *text)
{
    int y, x;
    
    getmaxyx(stdscr, y, x);
    mvaddstr(line, x / 2 - strlen(text) / 2, text);
}
