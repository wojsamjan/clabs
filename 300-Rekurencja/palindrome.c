/*
   Zadanie: Każde wywołanie funkcji `IsPalindrome' zaczyna
     obliczenia od wyliczenia długości napisu `str'.
     Podaj implementację funkcji `IsPalindrome', która robi
     to tylko raz. 
   Wskazówka: użyj funkcji opakowującej, której przekażesz
     obliczoną długość napisu `str'.   
 */

#include <stdio.h>
#include <stdlib.h>
#include "simpio.h"
#include "strlib.h"

bool IsPalindrome(string str) {
  int len;
  len=StringLength(str);
  if (len<=1)
    return TRUE;
  else
    return (IthChar(str,0)==IthChar(str,len-1)
	    && IsPalindrome(SubString(str,1,len-2)));
}

int main() {
  string line;
  printf("Program sprawdza, czy wpisany tekst jest palindromem.\n");
  printf("Wpisz coś: ");
  line=GetLine();
  printf("Wpisałeś: `%s'\n",line);
  printf("`%s' %s palindromem.\n",
	 line,IsPalindrome(line) ? "jest" : "nie jest"); 
  return EXIT_SUCCESS;
}
