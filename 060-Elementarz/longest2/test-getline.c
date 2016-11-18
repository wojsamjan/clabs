#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 2 /* maksymalny rozmiar wiersza */

#include "getline.h"

int main() {
  char line[MAXLINE];

  while (my_getline(line,MAXLINE) > 0) {
    printf("[%s]\n",line);
  }
}
