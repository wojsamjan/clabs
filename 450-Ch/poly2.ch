#!/bin/ch

//  $URL: http://manta.univ.gda.pl/svn/wb/labs/c/450-Ch/poly2.ch $
//  $Revision: 116 $

#include <stdio.h>
#include <numeric.h>

int main() {

  // p[0]*x^n + p[1]*x^{n-1} + ... + p[n-1]*x^1 + p[0]
  array double complex x[2];
  array double complex p[3] = { 1, -2, 1 }; 

  roots(x, p);
  printf("pierwiastki: %.1f", x);
						
  return 0;
}
