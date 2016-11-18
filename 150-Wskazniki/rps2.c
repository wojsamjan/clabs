// oblicz pierwiastek równania pierwszego stopnia o współcznnikach całkowitych:
//   b = a * x
//   x = b / a

#include <stdio.h>

void GetCoefficients(int *a, int *b);
void Solve(int a, int b, int *x);
void DisplayResults(int x);

int main() {
  int rhs, lhs, result;

  GetCoefficients(&rhs, &lhs);
  Solve(rhs, lhs, &result);
  DisplayResults(result);
}

void GetCoefficients(int *a, int *b) {
   printf("podaj a: ");
   scanf("%d", a);
   printf("podaj b: ");
   scanf("%d", b);
}
void Solve(int a, int b, int *x) {
  *x = b / a;
}
void DisplayResults(int x) {
  printf("wynik: %d\n", x);
}
