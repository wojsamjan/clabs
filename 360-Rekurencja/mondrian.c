/* Plik: mondrian.c
 * ----------------
 * rekurencja, biblioteka cslib.a, grafika, PostScript
 */

#include <stdio.h>
#include <stdlib.h> /* EXIT_SUCCESS */
#include "random.h"
#include "graphics.h"

#define MinArea 0.5
#define MinEdge 0.15

static void SubdivideCanvas(double x, double y, double width, double height);

int main() {
  InitGraphics();
  Randomize();
  SubdivideCanvas(0, 0, GetWindowWidth(), GetWindowHeight());
  return EXIT_SUCCESS;
}

static void SubdivideCanvas(double x, double y, double width, double height) {
  double divider;

  if (width*height>=MinArea) {
    if (width>height) {
      divider=width*RandomReal(MinEdge,1-MinEdge);
      MovePen(x+divider,y);
      DrawLine(0,height);
      SubdivideCanvas(x,y,divider,height);
      SubdivideCanvas(x+divider,y,width-divider,height);
    } else {
      divider=height*RandomReal(MinEdge,1-MinEdge);
      MovePen(x,y+divider);
      DrawLine(width,0);
      SubdivideCanvas(x,y,width,divider);
      SubdivideCanvas(x,y+divider,width,height-divider);
    }
  }
}
