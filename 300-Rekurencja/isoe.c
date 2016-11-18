#include <stdio.h>
#include <stdlib.h>

int IsOdd(int);
int IsEven(int);

int main() {
  int i;
  for (i=1024; i<1033; i++)
    printf("\tLiczba `%d' %s\n",
	   i,IsEven(i) ? "jest parzysta" : "jest nieparzysta");
  return EXIT_SUCCESS;
}

int IsEven(int n) {
  if (n==0)
    return 1;
  else
    return IsOdd(n-1);
}

int IsOdd(int n) {
  return !IsEven(n);
}
