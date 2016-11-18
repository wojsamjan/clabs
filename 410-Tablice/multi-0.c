
#include <stdio.h>
#include <stdlib.h>

// oblicz iloczyn macierzy kwadratowych: c[n][n] = a[n][n] * b[n][n]
// jak uzmienniæ 2?

void axb(double **aa, double **bb, double **cc, int n);

int main() {
  int i, j;
  int n=2;

  double a[20][20] = { { 1, 2 }, { 3, 4 } };
  double b[20][20] = { { 5, 6 }, { 7, 8 } };
  double c[20][20];

  // to nie dzia³a! czy wiesz dlaczego?
  axb(a, b, c, 2);

  for (i=0; i<n; i++) {
    for (j=0; j<n; j++)
      printf("c[%d][%d]=%.1f\t", i, j, c[i][j]);
    printf("\n");
  }

  return 0;
}

void axb(double aa[][20], double bb[][20], double cc[][20], int n) {
  int i, j, k;

  //  cc[i][j] = sum_0^m aa[i][m]*bb[m][j]

  for (i=0; i<n; i++) {
    for(j=0; j<n; j++) {
      cc[i][j] = 0;
      for (k=0; k<n; k++)
	cc[i][j] += aa[i][k] * bb[k][j];
    }
  }
}
