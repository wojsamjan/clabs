/* Plik: sierpinski.c
 * ------------------
 * rekurencja, biblioteka cslib.a, grafika, PostScript
 *
 * N. Wirth, Algorytmy + Struktury Danych = Programy, WNT 1989, s. 146
 * (uproszczone do jednej funkcji rekurencyjnej)
 */

#include <stdio.h>
#include <stdlib.h> /* EXIT_SUCCESS */
#include <math.h>
#include "simpio.h"
#include "genlib.h"
#include "graphics.h"

#define Pi 3.1415926535
#define sqrt2 sqrt(2)
#define MaxOrder 6

static void A(double len, double theta, int order); /* ćwiartka krzywej */
static void L(double size, double theta, int order); /* linia łącznikowa */
static void DrawPolarLine(double r, double theta);
static void Sierpinski(double size, int order);

int main() {
  double size;
  int order;

  InitGraphics();
  printf("Program ten rysuje krzywą Sierpińskiego.\n");
  printf("Podaj długość krawędzi w calach (1cal=2.54cm): ");
  size=GetReal();
  printf("Podaj rząd krzywej: ");
  if ((order=GetInteger())>MaxOrder || order<1) {
    printf("! Błąd: rząd jest liczbą z zakresu [1..6]\n");
    exit(1);
  }
  MovePen(2*size/3,3*size);
  Sierpinski(size,order);

  return EXIT_SUCCESS;
}

static void Sierpinski(double size, int order) {
  A(size,   0,order); L(size,   0-45,order);  // A
  A(size, -90,order); L(size, -90-45,order);  // B
  A(size,-180,order); L(size,-180-45,order);  // C
  A(size,-270,order); L(size,-270-45,order);  // D
}

/* A \ B -- D / A */
static void A(double size, double theta, int order) {
  if (order>0) {
    A(size/2,theta,order-1);
    L(size/2,theta-45,order-1);
    A(size/2,theta-90,order-1);
    L(size/sqrt2,theta,order-1);
    A(size/2,theta+90,order-1);
    L(size/2,theta+45,order-1);
    A(size/2,theta,order-1);
  }
}

static void L(double size, double theta, int order) {
  if (order==0) DrawPolarLine(size,theta);
  else L(size/2,theta,order-1);
}

static void DrawPolarLine(double r, double theta) {
  double radians=theta/180*Pi;
  DrawLine(r*cos(radians),r*sin(radians));
}
