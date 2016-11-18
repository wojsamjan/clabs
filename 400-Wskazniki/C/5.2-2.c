
#include <stdio.h>

void swap(int x, int y) {
  int temp;
  temp=x; x=y; y=temp;
}
int main() {
  int a, b;
  a=1; b=2;
  printf("a=%d b=%d\n",a,b);
  swap(a,b);
  printf("po wywolaniu funkcji swap: a=%d b=%d\n",a,b);
  return 0;
}
