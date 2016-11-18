#!/bin/ch

/* 
   Tutaj rozwi±zujemy numerycznie równanie ró¿niczkowe: 
      y'=cos(t)
   przy za³o¿eniu, ¿e y(0)=0 i t nale¿y do [0,2*PI].
   Oczywi¶cie rozwi±zaniem jest funkcja
      y=sin(t)
   co widaæ na rysunku.
*/

#include <stdio.h>
#include <numeric.h>

#define NVAR 1
#define POINTS 30

int main() {
  void func(double t, double y[], double dydt[]); // deklaracja
  double t0=0;
  double tf=2*M_PI;
  double y0[NVAR]={0};
  double t[POINTS], y[POINTS];
  int i, points;

/* return -1: rozbie¿ne 
   return >1: ok, zwróæ wyliczon± liczbê punktów
*/
  points = odesolve(t, y, func, t0, tf, y0);
  printf("points = %d\n", points);
  if(points > 0) {
    printf("\n%8s %17s %12s\n","t","odesolve()","sin(t)");
    for (i=0; i<points; i++)
      printf("%10.4f %14.6f %14.6f\n", t[i],y[i],sin(t[i]));
    plotxy(t, y, "result of odesolve", "t", "y");
  }
  else
    printf("odesolve() failed\n");
}

void func(double t, double y[], double dydt[]) { 
  dydt[0]=cos(t); /* y' = cos(t) */
}

