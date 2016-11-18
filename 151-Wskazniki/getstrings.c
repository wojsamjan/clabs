// usage: getstrings a.out

#define _GNU_SOURCE // cause stdio.h to include asprintf
#include <stdio.h>
#include <stdlib.h> // free

void get_strings(char *in) {
  char *cmd;

  asprintf(&cmd, "strings %s", in);
  if (system(cmd))
    fprintf(stderr, "something went wrong running %s.\n", cmd);
  free(cmd);
  }

int main(int argc, char **argv) {
  get_strings(argv[1]);
}

// man asprintf
//
// #define _GNU_SOURCE
// #include <stdio.h>
//
// int asprintf(char **strp, const char *fmt, ...);
