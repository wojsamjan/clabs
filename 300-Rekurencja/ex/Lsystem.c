#include <stdio.h>
#include <stdlib.h>
#include "genlib.h"
#include "simpio.h"
#include "strlib.h"
#include "graphics.h"

void DrawLsystem(int line_length);

int main()
{
  int n;
  printf("Podaj d³ugo¶æ odcinka: ? ");
  n = GetInteger();
  DrawLsystem(n);
  return EXIT_SUCCESS;
}

void DrawLsystem(int line_length)
{
}
