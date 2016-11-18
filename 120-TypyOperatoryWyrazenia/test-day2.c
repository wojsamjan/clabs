
#include <stdio.h>

typedef enum { 
  Monday=1, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday
} weekdayT;

char *nazwa[] = 
  { "", 
    "poniedziałek", "wtorek", "środa", "czwartek", "piątek", 
    "sobota", "niedziela" };

int main() {
  weekdayT d;

  d=Friday;

  printf("%d. dzień tygodnia to %s\n", d, nazwa[d]);
  return 0;
}
