#include <stdio.h>

typedef enum {
  Monday=1, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday
} weekdayT;

char *nazwa[] = { "",
  "Poniedziałek", "Wtorek", "Środa", "Czwartek", "Piątek", "Sobota", "Niedziela"
};

int main() {
  weekdayT d;

  d = Friday;

  printf("Dzień tygodnia: %d (%s)\n", d, nazwa[d]);
}
