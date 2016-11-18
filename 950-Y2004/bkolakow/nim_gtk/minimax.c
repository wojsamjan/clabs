#include"minimax.h"
#include<sys/time.h>

static int Random(void);
//Funkcja opakowuj±ca funkcjê FindBestMove.
//Je¶li ruch wygrywaj±cy zosta³ znaleziony
//funkcja zwraca ten ruch. Jesli nie
//funkcja zwraca ruch polegaj±cy na zdjêciu
//jednego ¿etona ze stosu o najwiêkszej liczbie ¿etonów.
moveT ChooseComputerMove(void)
{
    moveT mv_tmp;

    int st_tmp[3 + 1], i;

    for (i = 1; i <= 3; i++) {
	st_tmp[i] = stos[i];
    }

    st_tmp[0] = rek_depth;

    mv_tmp = FindBestMove(st_tmp, 0, 0);

    if (mv_tmp.liczba != 0)
	return mv_tmp;

    mv_tmp.nr_stosu = 1;
    mv_tmp.liczba = 1;

    for (i = 1; i <= 3; i++)
	if (stos[i] >= stos[mv_tmp.nr_stosu])
	    mv_tmp.nr_stosu = i;
    return mv_tmp;
}

//Funkcja szuka ruchu wygrywaj±cego. Jesli taki znajdzie zwraca
//ten ruch w postaci ilosci zetonów do zdjêcia
//i numeru stosu, z którego nalezy zdj±æ te ¿etony.
//Je¶li nie znajdzie ruchu wygrywaj±cego zwraca
//ilo¶æ ¿etonów do zdjêcia równ± zero.
moveT FindBestMove(int st_tmp[], int n, int r)
{
    int found = 0;
    moveT mv_tmp;

    while ((found == 0) && r < 3) {
	r++;
	n = 0;

	while ((found == 0) && n < st_tmp[r]) {
	    n++;
	    st_tmp[r] -= n;

	    if (IsBadPosition(st_tmp))
		found = 1;
	    st_tmp[r] += n;
	}
    }

    if (found == 0)
	n = 0;
    mv_tmp.nr_stosu = r;
    mv_tmp.liczba = n;

    return mv_tmp;
}

//Funkcja sprawdza czy dany uk³ad jest przegrywaj±cy.
//Je¶li jest zwraca 1, je¶li nie jest zwraca 0.
//Dodatkowo funkcja zwraca losowo wartosc 1 lub 0 je¶li dojdzie do
//maksymalnej g³êboko¶ci rekursji i nie otrzyma wyniku.
int IsBadPosition(int st_tmp[])
{
    moveT mv_tmp;

    st_tmp[0]--;
    if (st_tmp[0] == 0) {
	st_tmp[0]++;
	return Random();
    }

    if ((st_tmp[1] + st_tmp[2] + st_tmp[3]) == 1) {
	st_tmp[0]++;
	return 1;
    }

    else {
	mv_tmp = FindBestMove(st_tmp, 0, 0);
	st_tmp[0]++;
	if (mv_tmp.liczba == 0)
	    return 1;
	else
	    return 0;
    }
}

//Funkcja zwraca losowo wartosc 1 lub 0
static int Random(void)
{
    struct timeval sek;
    int temp;

    gettimeofday(&sek, 0);

    temp = sek.tv_usec;

    temp = temp % 2;

    return temp;
}
