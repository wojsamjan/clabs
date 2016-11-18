// oblicz pierwiastek równania pierwszego stopnia o współcznnikach całkowitych:
//   b = a * x
//   x = b / a

#include "helpers.h"

int main() {
  int rhs, lhs, result;

  GetCoefficients(&rhs, &lhs);
  Solve(rhs, lhs, &result);
  DisplayResults(result);
}
