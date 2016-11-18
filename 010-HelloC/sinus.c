#!/bin/ch

#include <stdio.h>
#include <math.h>
#include <chplot.h>

int main() {
  array double x[100], y[100];
  char *title = "sinus",
    *xlabel = "radiany",
    *ylabel = "amplituda";
  linspace(x,-M_PI,M_PI);
  y=sin(x);
  plotxy(x,y,title,xlabel,ylabel);
  return 0;
}
