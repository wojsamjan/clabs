#include <stdio.h>
#include <stdlib.h>

/* strlength: podaj długość tekstu w s */
int strlength(char s[]) {
  int i=0;
  while (s[i]!='\0')
    ++i;
  return i;
}

int main() {
  char msg[] = "abc";
  /* char msg[] = "witaj przygodo"; */
  printf("długość napisu `%s' = %d\n", msg, strlength(msg));

  return EXIT_SUCCESS;
}
