/*
    1. przepełnianie buforu (buffer overruns)
       przykład:
         Robert T. Morris (or just Morris) finger worm.
*/

#include <stdio.h>
#include <string.h>

void DontDoThis(char* input) {
  char buf[4];
  strcpy(buf, input);
  printf("%s\n", buf);
}

int main(int argc, char *argv[]) {
  /* nie sprawdzamy argumentów wywołania programu */
  DontDoThis(argv[1]);
  return 0;
}

/*
   $ sin-01 123         # ok
   $ sin-01 1234567     # dziwne?
   $ sin-01 12345678    # naruszenie ochrony pamięci
*/
