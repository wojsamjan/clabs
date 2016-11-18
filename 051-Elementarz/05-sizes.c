/*  Wypisz ile bajtow zajmuja zmienne dla typow podstawowych
    precyzja == liczba cyfr znaczacych */

#include <stdio.h>
#include <limits.h>
#include <float.h>

int main(void) {
  puts("Zmienne typow podstawowych.\n");

  puts("signed char:");
  printf("\tzajmuje %lu bajt (%i bitow)\n", sizeof(signed char), CHAR_BIT);
  printf("\tzakres od %i do %i\n\n", CHAR_MIN, CHAR_MAX);

  puts("unsigned char:");
  printf("\tzajmuje %lu bajtow(y) (%i bitow)\n", sizeof(unsigned char), CHAR_BIT);
  printf("\tzakres od %i do %i\n\n", 0, UCHAR_MAX);

  puts("signed short:");
  printf("\tzajmuje %lu bajtow(y)\n", sizeof(signed short));
  printf("\tzakres od %i do %i\n\n", SHRT_MIN, SHRT_MAX);

  puts("unsigned short:");
  printf("\tzajmuje %lu bajtow(y)\n", sizeof(unsigned short));
  printf("\tzakres od %i do %u\n\n", 0, USHRT_MAX);

  puts("signed int:");
  printf("\tzajmuje %lu bajtow(y)\n", sizeof(signed int));
  printf("\tzakres od %i do %i\n\n", INT_MIN, INT_MAX);

  puts("unsigned int:");
  printf("\tzajmuje %lu bajtow(y)\n", sizeof(unsigned int));
  printf("\tzakres od %i do %u\n\n", 0, UINT_MAX);

  puts("signed long:");
  printf("\tzajmuje %lu bajtow(y)\n", sizeof(signed long));
  printf("\tzakres od %li do %li\n\n", LONG_MIN, LONG_MAX);

  puts("unsigned long:");
  printf("\tzajmuje %lu bajtow(y)\n", sizeof(unsigned long));
  printf("\tzakres od %i do %lu\n\n", 0, ULONG_MAX);

  puts("float:");
  printf("\tzajmuje %lu bajtow(y)\n", sizeof(float));
  printf("\tzakres od +/-(1E%+i do 1E%+i) approx.\n", FLT_MIN_10_EXP, FLT_MAX_10_EXP);
  printf("\tprecyzja %i cyfr dziesietnych approx.\n\n", FLT_DIG);

  puts("double:");
  printf("\tzajmuje %lu bajtow(y)\n", sizeof(double));
  printf("\tzakres od +/-(1E%+i do 1E%+i) approx.\n", DBL_MIN_10_EXP, DBL_MAX_10_EXP);
  printf("\tprecyzja %i cyfr dziesietnych approx.\n\n", DBL_DIG);

  puts("long double:");
  printf("\tzajmuje %lu bajtow(y)\n", sizeof(long double));
  printf("\tzakres od +/-(1E%+i do 1E%+i) approx.\n", LDBL_MIN_10_EXP, LDBL_MAX_10_EXP);
  printf("\tprecyzja %i cyfr dziesietnych approx.\n\n", LDBL_DIG);

  puts("pointer:");
  printf("\tzajmuje %lu bajtow(y)\n", sizeof(void *));
  puts("");
}
