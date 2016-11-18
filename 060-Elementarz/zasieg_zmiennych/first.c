#include <stdio.h>

int a = 1;

void fun(int a) {
  printf("#fun 1: %d\n", a);
  a = 3;
  {
    int a = 4;
    printf("#fun 2: %d\n", a);
  }
  printf("#fun 3 %d\n", a);
}

void afun(void) {
  printf("#afun: %d\n", a);
}

int main(void) {
  int a = 2;
  printf("#main przed fun: %d\n", a);
  fun(a);
  printf("#main po fun: %d\n", a);
  afun();
}
