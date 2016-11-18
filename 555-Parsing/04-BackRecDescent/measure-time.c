#include <sys/timeb.h>
#include <stdio.h>
#include <math.h>

#define MAX 10000000

main() {
  unsigned czas_m, czas_s;
  struct timeb start, stop;
  int i;
  double x;
  ftime(&start);
  for (i=0; i<MAX; i++) x=sin(x);
  ftime(&stop);
  czas_m=abs(stop.millitm-start.millitm);
  czas_s=difftime(stop.time-start.time);
  printf("Czas: %d %d (%g)\n", czas_s, czas_m, x);
}
