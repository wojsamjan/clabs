#include "power.h"

int power(int m, int n) {
  int i,p;
  p = 1;
  for (i = 1; i <= n; ++i) {
    p = p * m;
  }
  return p;
}
