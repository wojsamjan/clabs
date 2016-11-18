// oblicz pierwiastek równania pierwszego stopnia o współcznnikach całkowitych:
//   b = a * x
//   x = b / a

#include <stdio.h>

int rhs, lhs, result;

void GetCoefficients();
void Solve();
void Display();

int main() {
  GetCoefficients();
  Solve();
  Display();
}

void GetCoefficients() {
   printf("podaj a: ");
   scanf("%d", &rhs);
   printf("podaj b: ");
   scanf("%d", &lhs);
}
void Solve() {
  result = lhs / rhs;
}
void Display() {
  printf("wynik: %d\n", result);
}
