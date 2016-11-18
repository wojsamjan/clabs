#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int q;
  int r;
} Result_T;

Result_T divmod(int x, int y) {
  int r, q, rr, qq;
  Result_T result;

  if (x < y) { 
    q = 0;
    r = x;
  } else {
    Result_T w;
    w = divmod(x, 2*y);
    qq = w.q;
    rr = w.r;
    if (rr < y) {
      q = 2 * qq;
      r = rr;
    } else {
      q = 2 * qq + 1;
      r = rr - y;
    }
  }
  result.q = q;
  result.r = r;

  return result;
}

int main(int argc, char *argv[]) {
  int x, y;
  Result_T w;

  if (argc != 3) {
    printf("\tUżycie: div licznik mianownik\n");
    return EXIT_FAILURE;
  }

  x = atoi(argv[1]);
  y = atoi(argv[2]);
  w = divmod(x, y);

  printf("\t%d = %d * %d + %d\n", x, y, w.q, w.r);

  return EXIT_SUCCESS;
}
