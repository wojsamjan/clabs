/*
 * File: dicetest2.c
 * ----------------
 * Sprawdzamy generator rand
 */

#include <stdio.h>
#include "genlib.h"
#include "random.h"

#define NTrials 6000

int RollDie(void);

int main()
{
    int i, ave[7] = { 0, 0, 0, 0, 0, 0, 0 };

    Randomize();
    for (i = 0; i < NTrials; i++)
      ave[RollDie()]++;
    for (i=1; i<7; i++)
      printf("ave[%d] = %d\n",i,ave[i]);

    return 0;
}

/*
 * Function: RollDie
 * Usage: die = RollDie();
 * -----------------------
 * This function generates and returns a random integer in the
 * range 1 to 6, representing the roll of a six-sided die.
 */

int RollDie(void)
{
    return (RandomInteger(1, 6));
}
