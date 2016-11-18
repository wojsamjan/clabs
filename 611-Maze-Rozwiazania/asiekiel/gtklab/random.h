/* Artur Siekielski, 30 pa¼dziernika 2003
 * Funkcje obs³uguj±ce generator liczb losowych -- deklaracje */

#ifndef INCLUDED__RANDOM_H
#define INCLUDED__RANDOM_H

#include <time.h>
#include <stdlib.h>
#include <unistd.h>

/* Zainicjalizuj generator liczb losowych */
void init_random_gen(void);

/* Wylosuj liczbê ca³kowit± z przedzia³u from..to-1 */
int random_integer(int from, int to);

#endif
