/*
* This program simulates flipping a coin.
*/

#include <stdio.h>
#include <stdlib.h>

#define NTrials 10

int main() {
  int i;

  for (i = 0; i < NTrials; i++) {
    if (rand() <= RAND_MAX / 2) {
      printf("orzełek\n");
    } else {
      printf("reszka\n");
    }
  }
}
