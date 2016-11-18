/*  $Revision: 1.1 $
    $Date: 2004/11/19 12:38:30 $ 
*/

/* Zob. man sprintf */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>  /* nowa biblioteka standardowa: isspace, isdigit */

/* itoa:
     zamieñ liczbê na znaki w tablicy s
*/
void itoa(int n, char s[]);
void reverse(char s[]);

int main()
{
  char cyfry[100];
  int liczba;
 
  liczba = -21593;
  itoa(liczba, cyfry);
  printf("Wynik konwersji liczby `%d' na napis -> `%s'\n", liczba, cyfry); 
  return EXIT_SUCCESS;
}

void itoa(int n, char s[])
{
  int i, sign;

  if ((sign=n)<0)
    n = -n;

  i=0;
  do {
    s[i++] = n%10 + '0';
  } while ((n /= 10) > 0);

  if (sign<0)
    s[i++]='-';

  s[i]='\0';

  reverse(s);
}

void reverse(char s[])
{
  return;
}
