/* Jakub S³awiñski (Slaughter House Entertainment Group)
 * plik implementuj±cy pomocnicze funkcje
 * myfunkc.c
 */

#include <stdlib.h>
#include <sys/time.h>
#include <sys/select.h>
#include "myfunkc.h"

static char jestpodstawa;

int
myrand(int dol, int gora)
{
	struct timeval tv;
	if (!jestpodstawa) {
		gettimeofday(&tv, 0);
		srand(tv.tv_sec);
		jestpodstawa = 1;
	}
	return ( dol + ( rand() % (gora - dol + 1) ) );
}

void
mysleep(double time)
{
	struct timeval tv;
	tv.tv_sec = (int) time;
	tv.tv_usec = (int)(time * 1000000)%1000000;
	select(0, NULL, NULL, NULL, &tv);
}
