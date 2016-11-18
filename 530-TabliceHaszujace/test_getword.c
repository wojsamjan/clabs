#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "getword.h"

int first(int c) {
  return isalpha(c);
}
int rest(int c) {
  return isalpha(c) || c == '_';
}

int main(int argc, char *argv[]) {
  char buf[1024];
  int  buf_size = atoi(argv[1]);

  while (getword(stdin, buf, buf_size, first, rest)) {
    printf("buf = \"%s\"\n", buf);
  }

  return EXIT_SUCCESS;
}
