#include <stdio.h>

int main () {
  double sum = 0, v;

  printf("Podaj kilka liczb oddzielonych spacjami, np. 2 1.5 1:\n");
  while (scanf("%lf", &v) == 1)
    printf("\tsuma: %.2f\n", sum += v);
  return 0;
}
