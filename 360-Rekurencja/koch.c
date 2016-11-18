/* Plik: koch.c
 * -----------
 * rekurencja, biblioteka cslib.a, grafika, PostScript
 */

#include <stdio.h>
#include <stdlib.h> /* EXIT_SUCCESS */
#include <math.h>
#include "simpio.h"
#include "genlib.h"
#include "graphics.h"

#define Pi 3.1415926535
#define MaxOrder 6

static void KochFractal(double size, int order);
static void DrawFractalLine(double len, double theta, int order);
static void DrawPolarLine(double r, double theta);

int main() {
  double size;
  int order;

  InitGraphics();
  printf("Program ten rysuje platki Kocha.\n");
  printf("Podaj dlugosc krawedzi w calach (1cal=2.54cm): ");
  size = GetReal();
  printf("Podaj rzad platka: ");
  if ((order = GetInteger()) > MaxOrder) {
    printf("! Za duzy rzad (maks. 6)\n");
    exit(1);
  }
  KochFractal(size, order);

  return EXIT_SUCCESS;
}

static void KochFractal(double size, int order) {
  double x0, y0;
  x0 = GetWindowWidth() / 2 - size / 2;
  y0 = GetWindowHeight() / 2 - sqrt(3) * size / 6;
  MovePen(x0, y0);
  DrawFractalLine(size, 0, order);
  DrawFractalLine(size, 120, order);
  DrawFractalLine(size, 240, order);
}
static void DrawFractalLine(double len, double theta, int order) {
  if (order == 0)
    DrawPolarLine(len, theta);
  else {
    DrawFractalLine(len / 3, theta, order - 1);
    DrawFractalLine(len / 3, theta - 60, order - 1);
    DrawFractalLine(len / 3, theta + 60, order - 1);
    DrawFractalLine(len / 3, theta, order - 1);
  }
}
static void DrawPolarLine(double r, double theta) {
  double radians;
  radians = theta / 180 * Pi;
  DrawLine(r * cos(radians), r * sin(radians));
}
