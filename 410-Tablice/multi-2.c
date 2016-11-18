
#include <stdio.h>
#include <stdlib.h>

int main() {
  double **a;

  int m=2, n=2, i, j;

  a = (double **)malloc(m*sizeof(double*));

  for (i=0; i<m; i++)
    a[i] = (double *)malloc(n*sizeof(double));

  a[0][0]=5; a[0][1]=6; a[1][0]=7;
  *(*(a+1)+1)=8; //  <=> a[1][1]=4; 

  for (i=0; i<n; i++) {
    for (j=0; j<m; j++)
      printf("a[%d][%d]=%.1f\t", i, j, a[i][j]);
    printf("\n");
  }

  return 0;
}
