#include <stdio.h>

int a, b;

void fun(int a) {
  a = 3;
  {
    int b = 4;
    printf("%d %d\n", a, b);
  }
  printf("%d %d\n", a, b);
  b = 5;
}

int main(void) {
  a = 1;  // zmieniamy wartosc zmiennej zewnetrznej
  b = 2;  // jw.
  fun(a);
  printf("%d %d\n", a, b);
}
