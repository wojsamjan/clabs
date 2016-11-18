/* wypisz zestawienie temperatur Fahrenheita-Celsjusza
   argumenty wywołania programu */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  int lower; /* dolna granica temperatur */
  int upper; /* górna granica */
  int step;  /* rozmiar kroku */

  int fahr;

  lower = atoi(argv[1]);
  upper = atoi(argv[2]);
  step =  atoi(argv[3]);

  printf("lower = %d, upper = %d, step = %d\n",lower,upper,step);
  for (fahr=lower; fahr <= upper; fahr = fahr+step) {
    printf("%3d%6.1f\n", fahr, (5.0/9.0)*(fahr-32));
  }
}
