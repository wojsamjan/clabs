#include <stdio.h>
#include <stdlib.h>

main () {
  unsigned char *buffer="abc1.23def";
  char *cp=&buffer[4];
  char *endptr;
  double v;

  v=strtod(cp,&endptr);
  if (endptr==cp) { 
    printf("No conversion was done.\n");
  } else {
    printf("v=%g, rest=%s\n",v,endptr);
  }
  printf("\n");
}
