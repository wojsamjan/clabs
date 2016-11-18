/*
 * File: randtest.c
 * ----------------
 * This program tests the ANSI rand function.
 */

#include <stdio.h>
#include <stdlib.h>

#define NTrials 10

int main()
{
    int i, r;

    printf("On this computer, RAND_MAX = %d.\n", RAND_MAX);
    printf("Here are the results of %d calls to rand:\n", NTrials);
    for (i = 0; i < NTrials; i++) {
        r = rand();
        printf("%10d\n", r);
    }
    return 0;
}
