/*
    File: DigitalSum.c

    DigitalSum(1955) = 2, poniewaz

       Krok 1: 1+9+5+5 => 20
       Krok 2:     2+0 =>  2

    Sumujemy cyfry tak dlugo, az zostanie tylko jedna cyfra.
 */

#include <stdio.h>
#include <stdlib.h>  // atoi

int DigitalSum(int);

int main(int argc, char *argv[]) {
  int n = atoi(argv[1]), r;

  r = DigitalSum(n);
  printf("\tDigitalSum(%d) = %d\n",n,r);
}

int DigitalSum(int n) {
  if (n < 10)
    return n;
  else
    return DigitalSum(n % 10 + DigitalSum(n / 10));
}
