/* Artur Siekielski, 30 pa¼dziernika 2003
 * Funkcje obs³uguj±ce generator liczb losowych -- implementacja */

#include "random.h"
#include <stdlib.h>

void init_random_gen(void)
{
      /* Jako 'seed' daj generatorowi liczbê sekund od 1.1.1970 + PID */
      srand(time(NULL) + getpid());
}

int random_integer(int from, int to)
{
      return (rand() % (to - from)) + from;
}

