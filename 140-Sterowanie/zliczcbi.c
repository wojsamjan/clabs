/*  $Revision: 1.1 $
    $Date: 2004/11/19 12:38:30 $ 
*/

#include <stdio.h>
#include <stdlib.h>

/*  zlicz cyfry, bia³e znaki, inne 
*/

int main()
{
  int c, i, nwhite, nother, ndigit[10];

  /* inicjalizacja zmiennych */
  nwhite=nother=0;
  for (i=0; i<10; i++)
    ndigit[i]=0;
  /* zliczanie */
  while ((c=getchar())!=EOF) {
    switch (c) {
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
      ndigit[c-'0']++;
      break;
    case ' ': case '\n': case '\t':
      nwhite++;
      break;
    default:
      nother++;
      break;
    }
  }
  /* wypisz wyniki */
  printf("cyfry =");
  for (i=0; i<10; i++)
    printf(" %d", ndigit[i]);
  printf(" bia³e znaki = %d, inne = %d\n", nwhite, nother);

  return EXIT_SUCCESS;
}
