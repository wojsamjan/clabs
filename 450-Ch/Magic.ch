/* 
   Przyk³ad programu korzystaj±cego z funkcji
   `specialmatrix' z bibloteki numerycznej
   jêzyka `ch'.
   Zwróæ uwagê na ró¿nice w deklarowaniu 
   tablic miêdzy jêzykami `Ch' i `C' oraz
   na u¿ycie zmiennych tablicowych w funkcji
   printf. 
*/

#include <numeric.h>

int main() {
  int i, n=4; /* Czy istnieje kwadrat magiczny 2x2 ? */
  array double y[n][n], sum1[n];
  y=specialmatrix("Magic",n);
  printf("specialmatrix(\"Magic\",n) =\n%4.0f\n",y);
  sum(y,sum1);
  printf("sumy w kolumnach =%4.0f",sum1);
  sum(transpose(y),sum1);
  printf("sumy w wierszach =%4.0f",sum1);
  printf("suma elementów na przek±tnej =%4.0f\n",trace(y));
  rot90(y,y);
  printf("suma elementów na anty-przek±tnej =%4.0f\n",trace(y));
}
