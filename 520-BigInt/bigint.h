/*  -*- coding: utf-8 -*-

    $URL: http://manta.univ.gda.pl/svn/wb/labs/c/520-BigInt/bigint.h $
    $Revision: 127 $
*/

#ifndef BIGINT_INCLUDED
#define BIGINT_INCLUDED
#define T BigInt_T

#include "genlib.h"

/*    Interfejs wspierający dowolnie duże liczby całkowite

      TODO:

      1. liczby całkowite ujemne
      2. odejmowanie
      3. dzielenie
      4. poprawić wydajność
 */


typedef struct T *T;


/*  utwórz nową liczbę typu T o wartości i  */

T NewBigInt(int i);

/*  funkcje do konwersji między napisami złożonymi z liczb 
    a liczbami typu T  */

T StringToBigInt(string s);
string BigIntToString(T n);

/*  dodaj dwie liczby typu T i zwróć ich sumę typu T  */

T AddBigInt(T n1, T n2);

/*  pomnóż dwie liczby typu T i zwróć ich iloczyn typu T  */

T MultiplyBigInt(T n1, T n2);


#undef T
#endif
