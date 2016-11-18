/*  $Revision: 1.1 $
    $Date: 2004/11/19 11:51:13 $ 
*/

#include <stdio.h>
#include <stdlib.h>

/*  binsearch:
      szukaj x w¶ród v[0]<=v[1]<= ... <= v[n-1] 
*/
int binsearch(int x, int v[], int n);

int main()
{
  /* uporz±dkowana tablica */
  int ptwo[] = { 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024 };
  int len = sizeof(ptwo)/sizeof(int);
  int n;

  printf("Liczba elementów w tablicy `ptwo': %d\n", len); 

  n=128;
  if (binsearch(n, ptwo, len)==-1)
    printf("Liczby %d nie ma w tablicy `ptwo'\n", n); 
  else
    printf("Liczba %d jest w tablicy `ptwo'\n", n); 

  n=712;
  if (binsearch(n, ptwo, len)==-1)
    printf("Liczby %d nie ma w tablicy `ptwo'\n", n); 
  else
    printf("Liczba %d jest w tablicy `ptwo'\n", n); 

  return EXIT_SUCCESS;
}

/* wyszukiwanie metod± bisekcji */

int binsearch(int x, int v[], int n)
{
  int low, high, mid;

  low=0; high=n-1;
  while (low<=high) {
    mid = (low+high)/2;
    if (x<v[mid])
      high = mid-1;
    else if (x>v[mid])
      low = mid+1;
    else  /* znaleziono */
      return mid;
  }
  return -1;
}
