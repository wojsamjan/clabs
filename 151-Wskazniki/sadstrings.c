// usage: sadstrings a.out

#include <stdio.h>
#include <string.h> //strlen
#include <stdlib.h> //malloc, free, system

void get_strings(char *in) {
  char *cmd;
  int len = strlen("strings ") + strlen(in) + 1;

  cmd = malloc(len);
  snprintf(cmd, len, "strings %s", in);
  if (system(cmd))
    printf("something went wrong running %s.\n", cmd);

  free(cmd);
}

int main(int argc, char **argv) {
<<<<<<< HEAD
  get_strings(argv[1]);
}
=======
	get_strings(argv[1]);
}
>>>>>>> 320713bac15c76b59ad7b60fffedffb9c4e267c6
