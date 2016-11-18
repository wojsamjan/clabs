
#include <stdio.h>
#include <stdlib.h>

// oblicz iloczyn macierzy: c[n][r] = a[n][m] * b[m][r]
void axb(double **aa, double **bb, double **cc, int n, int m, int r);

int main() {
  int i, j;
  int m=2, n=2, r=2;
  double a[2][2] = { { 1, 2 }, { 3, 4 } };
  double b[2][2] = { { 5, 6 }, { 7, 8 } };
  double c[2][2];

  // to nie działa! czy wiesz dlaczego?
  axb(a, b, c, n, m, r);

  for (i=0; i<n; i++) {
    for (j=0; j<r; j++)
      printf("c[%d][%d]=%.1f\t", i, j, c[i][j]);
    printf("\n");
  }

  return 0;
}

void axb(double **aa, double **bb, double **cc, int n, int m, int r) {
  int i, j, k;

  //  cc[i][j] = sum_0^m aa[i][m]*bb[m][j]

  for (i=0; i<n; i++) {
    for(j=0; j<r; j++) {
      cc[i][j] = 0;
      for (k=0; k<m; k++)
	cc[i][j] += aa[i][k] * bb[k][j];
    }
  }
}
