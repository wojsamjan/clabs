#include "fsize.h"

/*  funkcja main dla funkcji fsize wypisującej rozmiary plików  */

int main(int argc, char *argv[])
{
  if (argc == 1)
    fsize(".");  /* domyślnie: bieżący skorowidz */
  else
    while (--argc > 0)
      fsize(*++argv);
  return 0;
}
