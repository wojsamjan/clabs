/* Plik: hilbert.c
 * ------------------
 * rekurencja wzajemna, biblioteka cslib.a, grafika, PostScript
 *
 * N. Wirth, Algorytmy + Struktury Danych = Programy, WNT 1989, s. 143
 * (uproszczone do dwóch funkcji wzajemnie rekurencyjnych)
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

static void A(double size, double theta, int order); /* krzywa Hilberta */
static void B(double size, double theta, int order);
static void L(double size, double theta, int order); /* linia łącznikowa */
static void DrawPolarLine(double r, double theta);

int main() {
  double size;
  int order;

  InitGraphics();
  printf("Program ten rysuje krzywą Hilberta.\n");
  printf("Podaj długość krawędzi w calach (1cal=2.54cm): ");
  size=GetReal();
  printf("Podaj rząd krzywej: ");
  if ((order=GetInteger())>MaxOrder || order<1) {
    printf("! Błąd: rząd jest liczbą z zakresu [1..6]\n");
    exit(1);
  }
  MovePen(1.5*size,1.5*size);
  A(size,0,order);

  return EXIT_SUCCESS;
}

/* A:  B | A - A | B  (dół, lewo, góra) */
static void A(double size, double theta, int order) {
  if (order>0) {
    B(size/2,theta+90,order-1);
    L(size/2,theta-90,order-1);
    A(size/2,theta,order-1);
    L(size/2,theta-180,order-1);
    A(size/2,theta,order-1);
    L(size/2,theta+90,order-1);
    B(size/2,theta-90,order-1);
  }
}

/* B:  A | B - B | A  (góra, lewo, dół) */
static void B(double size, double theta, int order) {
  if (order>0) {
    A(size/2,theta-90,order-1);
    L(size/2,theta+90,order-1);
    B(size/2,theta,order-1);
    L(size/2,theta+180,order-1);
    B(size/2,theta,order-1);
    L(size/2,theta-90,order-1);
    A(size/2,theta+90,order-1);
  }
}

/* Łącznik */
static void L(double size, double theta, int order) {
  if (order==0) DrawPolarLine(size,theta);
  else L(size/2,theta,order-1);
}

static void DrawPolarLine(double r, double theta) {
  double radians=theta/180*Pi;
  DrawLine(r*cos(radians),r*sin(radians));
}
