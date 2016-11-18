/* Plik: conv.c
 * ----------------
 * Konwersja typów.
 *
 * Wersja z dnia: 4.X.2000
 */

#include <stdio.h>

int main () {
  unsigned char uc; /* ma³e liczby ca³kowite bez znaku */
  signed char sc; /* ma³e liczby ca³kowite ze znakiem */
  int i;
  unsigned int ui;

  uc=128; sc=uc; printf("signed <- unsigned %d <- %d\n",sc,uc);
  uc=255; sc=uc; printf("signed <- unsigned %d <- %d\n",sc,uc);
  i='±';  printf("int <- char %d <- %d\n",i,'±');
  ui='±';  printf("unsigned int <- char %u <- %d\n",ui,'±');
  uc='±'; printf("unsigned char: %d\n", uc);

  return 0;
}
