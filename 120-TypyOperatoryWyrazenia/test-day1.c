
#include <stdio.h>

enum weekday { 
  Monday=1, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday
};

char *nazwa[] = 
  { "", 
    "poniedziałek", "wtorek", "środa", "czwartek", "piątek", 
    "sobota", "niedziela" };

int main() {
  enum weekday d;

  d=Thursday;

  printf("%d. dzień tygodnia to %s\n", d, nazwa[d]);
  return 0;
}
