#include"nim.h"

void GiveInstructions(void)
{
    erase();
    mvprintw(1, 10, "Witam w grze w NIM!");
    color_set(1, 0);
    mvprintw(3, 0, "Zaczynasz grê z trzema stosami ¿etonów.\n");
    printw("Liczba ¿etonów znajduj±cych siê na stosach:\n\n");
    color_set(3, 0);
    printw("- stos nr.1 - ");
    printw("%d,\n- stos nr.2 - %d,\n- stos nr.3 - %d;\n\n", stos[1],
	   stos[2], stos[3]);
    color_set(1, 0);
    printw("Ruchy wykonywane s± na przemian.\n");
    printw
	("W ka¿dym ruchu mo¿na zabraæ ze stosu dowoln± ilo¶æ ¿etonów,\n");
    printw("pod warunkiem, ¿e zabieramy ¿etony z jednego stosu.\n");
    printw("Gracz, który zabierze ostatni ¿eton przegrywa.\n");
    printw("\n\tPierwszy zaczyna%s\n",
	   (kto_zaczyna == 0) ? " Computer." : "sz Ty.");
    printw("\n");
    refresh();
    getch();
}

stateT NewGame(void)
{

    stos[1] = zetony1;
    stos[2] = zetony2;
    stos[3] = zetony3;

    return kto_zaczyna;
}

int GameIsOver(void)
{
    if ((stos[1] + stos[2] + stos[3]) > 1)
	return 0;
    return 1;
}

void DisplayGame(void)
{
    int i, j;

    erase();
    color_set(3, 0);
    mvprintw(1, 3, "Pozosta³o jeszcze:\n%d ¿etonów na pierwszym stosie,\n",
	     stos[1]);
    printw("%d ¿etonów na drugim stosie,\n", stos[2]);
    printw("%d ¿etonów na trzecim stosie.\n\n", stos[3]);

    color_set(4, 0);

    for (j = 1; j <= 3; j++) {
	printw("%d) ", j);
	for (i = 1; i <= stos[j]; i++)
	    printw("*");
	printw(" %d\n", stos[j]);
    }

    color_set(1, 0);

    mvprintw(10, 5, "Naci¶nij <ENTER>\n");
    refresh();
    getch();
}

moveT GetUserMove(void)
{
    moveT ruch;
    ruch.nr_stosu = -1;
    ruch.liczba = -1;

    while (!((ruch.nr_stosu >= 1) && (ruch.nr_stosu <= 3))) {
	mvprintw(10, 2, "Z którego stosu chcesz zabraæ ¿etony?\n");
	mvprintw(11, 2, "Podaj liczbê od 1 do 3.\n");
	clrtobot();
	refresh();

	color_set(2, 0);

	if (scanw("%d", &ruch.nr_stosu) == 0) {
	    mvprintw
		(13, 2,
		 "Wpisany znak jest nieprawid³owy, spróbuj jeszcze raz.\n");
	    mvprintw(14, 2, "Naci¶nij dowolny klawisz.");
	    refresh();
	    getch();
	    ruch.nr_stosu = -1;
	} else {
	    if (!((ruch.nr_stosu >= 1) && (ruch.nr_stosu <= 3))) {
		mvprintw(13, 2,
			 "Nie ma stosu o numerze który poda³e¶! Spróbuj jeszcze raz!\n");
		mvprintw(14, 2, "Naci¶nij dowolny klawisz.");
		refresh();
		getch();
	    } else if (stos[ruch.nr_stosu] == 0) {
		mvprintw(13, 2, "Ten stos jest juz pusty!!!");
		mvprintw(14, 2, "Nie mo¿esz z niego ju¿ nic zdj±æ.");
		mvprintw(15, 2, "Wybierz nowy stos");
		mvprintw(17, 2, "Naci¶nij dowolny klawisz.");
		refresh();
		getch();
		ruch.nr_stosu = -1;
	    }
	}

	color_set(1, 0);

    }

    while (!MoveIsLegal(ruch)) {
	mvprintw(10, 2, "Podaj ile ¿etonów chcesz zabraæ ze stosu.\n");
	clrtobot();
	refresh();
	color_set(2, 0);
	if (scanw("%d", &ruch.liczba) == 0) {
	    mvprintw
		(13, 2,
		 "Podany znak jest nieprawid³owy, spóbuj jeszcze raz.\n");
	    mvprintw(14, 2, "Naci¶nij dowolny klawisz.");
	    refresh();
	    ruch.liczba = -1;
	    getch();
	} else if (!MoveIsLegal(ruch)) {
	    mvprintw(13, 2, "Poda³e¶ z³± liczbê, spróbuj jeszcze raz!\n");
	    mvprintw(14, 2, "Naci¶nij dowolny klawisz");
	    refresh();
	    getch();
	}

	color_set(1, 0);
    }

    return ruch;
}


int MoveIsLegal(moveT ruch)
{
    if (stos[ruch.nr_stosu] >= ruch.liczba && 1 <= ruch.liczba)
	return 1;
    else
	return 0;
}

void DisplayMove(moveT move)
{
    printw("\nComputer bierze z %d stosu %d.\n",
	   move.nr_stosu, move.liczba);
    refresh();
}

void MakeMove(moveT move)
{
    stos[move.nr_stosu] -= move.liczba;
}

void AnnounceResults(stateT state)
{
    color_set(2, 0);
    if (state == Computer)
	printw("\nGratulacje, WYGRA£E¦!!!\n");
    else
	printw("\nNiestety tym razem komputer by³ lepszy :(\n");
    getch();
    refresh();
}
