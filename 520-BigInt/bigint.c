/* 
    $URL: http://manta.univ.gda.pl/svn/wb/labs/c/520-BigInt/bigint.c $
    $Revision: 195 $
*/

#include <stdio.h>
#include <ctype.h>

#include "genlib.h"
#include "strlib.h"
#include "bigint.h"

#define T BigInt_T

/*   Liczby T są zaimplementowane za pomocą listy
     złożonej z komórek; każda komórka zawiera jedną cyfrę.
     Na początku listy umieszczamy liczbę jednostek,
     następnie liczbę dziesiątek, setek itd.

     W rekurencyjnej implementacji T

     -- liczba 0 jest reprezentowana przez wskaźnik NULL
     -- cyfra d i liczba n typu T reprezentują liczbę d + 10*n
 */

struct T {
  int finalDigit;
  T leadingDigits;
};

/*  prototypy funkcji prywatnych  */

static T AddWithCarry(T n1, T n2, int carry);
static T MultiplyDigit(int digit, T n);
static T DigitCons(T leadingDigits, int finalDigit);
static T LeadingDigits(T n);
static int FinalDigit(T n);

/*  funkcje exportowane  */

T NewBigInt(int i) {
  if (i<0)
    Error("interfejs BigInt nie obsługuje ujemnych liczb całkowitych");
  if (i==0) 
    return NULL;
  return DigitCons(NewBigInt(i/10), i%10);
}

T StringToBigInt(string s) {
  int len;
  char ch;
  
  len = StringLength(s);
  if (len == 0)
    return 0;
  ch = s[len-1];
  if (!isdigit(ch))
    Error("oczekiwałem cyfry an nie `%c'", ch);
  return DigitCons(StringToBigInt(SubString(s, 0, len-2)), ch-'0');
}

string BigIntToString(T n) {
  string s;

  s = CharToString(FinalDigit(n) + '0');
  if (LeadingDigits(n) != NULL) {
    s = Concat(BigIntToString(LeadingDigits(n)), s);
  }
  return s;
}

/* funkcja AddbigInt jest funkcją opakowującą, która wywołuje
   AddWithCarry do wykonania dodawania  */

T AddBigInt(T n1, T n2) {
  return AddWithCarry(n1, n2, 0);
}

static T AddWithCarry(T n1, T n2, int carry) {
  int sum;
  T p1, p2;

  p1 = LeadingDigits(n1);
  p2 = LeadingDigits(n2);
  sum = FinalDigit(n1) + FinalDigit(n2) + carry;
  if (sum == 0 && p1 == NULL && p2 == NULL)
    return NULL;
  return DigitCons(AddWithCarry(p1, p2, sum/10), sum%10);
}

/*  w implementacji MultiplyBigInt korzystamy ze zwykłego
    szkolnego algorytmu mnożenia, mnożąc n2 kolejno
    przez każdą cyfrę n1.
    Funkcja ta jest rekurencyjna. 
    W implementacji korzystamy ze wzoru (por. wykład):

      n1 * n2 = FinalDigit(n1) * n2 + LeadingDigits(n1) * n2 + 10   

    Uwagi: 
    1. mnożenie przez 10 zaimplementowano przez
       dołączenie 0 do liczby za pomocą DigitCons.
    2. mnożenie przez cyfrę zaimplementowano za pomocą
       rekurencyjnego dodawania  
*/

T MultiplyBigInt(T n1, T n2) {
  if (n1 == NULL)
    return NULL;
  return AddBigInt(MultiplyDigit(FinalDigit(n1), n2),
		   MultiplyBigInt(LeadingDigits(n1), DigitCons(n2, 0)));
}

static T MultiplyDigit(int digit, T n) {
  if (digit == 0) 
    return NULL;
  return AddBigInt(n, MultiplyDigit(digit - 1, n));
}

/*  funkcja ta zwraca liczbę typu T łącząc finalDigit z leadingDigits;
    finaldigit jest dopisywane na początku listy reprezentującej 
    leadingDigits  */

static T DigitCons(T leadingDigits, int finalDigit) {
  T cp;

  if (leadingDigits == NULL && finalDigit == 0)
    return NULL;
  cp = New(T);
  cp->finalDigit = finalDigit;
  cp->leadingDigits = leadingDigits;
  return cp;
}

static T LeadingDigits(T n) {
  return (n == NULL) ? NULL : n->leadingDigits;
}

static int FinalDigit(T n) {
  return (n == NULL) ? 0 : n->finalDigit;
}
