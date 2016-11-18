#!/bin/ch

#include <stdio.h>
#include <numeric.h>

int main() {
  array double A[3][3] = {
    {1,2,2},
    {4,4,6},
    {7,8,9}
  };
  array double b[3] = {5,6,8}, x[3];

  linsolve(x,A,b);
  // x=inverse(A)*b;
  printf("x = %.3f",x);

  return 0;
}
