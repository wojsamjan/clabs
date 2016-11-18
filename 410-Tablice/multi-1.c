
#include <stdio.h>
#include <stdlib.h>

int main() {
  double **a;

  int m=2, n=2, i, j;

  a = (double **)malloc(m*sizeof(double*));

  a[0] = (double *)malloc(m*n*sizeof(double));

  for (i=1; i<m; i++)
    a[i] = a[0] + i*n;

  a[0][0]=1; a[0][1]=2; a[1][0]=2;
  *(*(a+1)+1)=4; //  <=> a[1][1]=4; 

  for (i=0; i<n; i++) {
    for (j=0; j<m; j++)
      printf("a[%d][%d]=%.1f\t", i, j, a[i][j]);
    printf("\n");
  }

  return 0;
}
