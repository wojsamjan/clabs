#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *format_commas(long int n, char *out) {
  long int c;
  char buf[100];
  char *p;
  char* q = out; // backup pointer for return...

  if (n < 0) {
    *out++ = '-';
    n = labs(n);
  }

  snprintf(buf, 100, "%ld", n);
  c = 2 - strlen(buf) % 3;

  for (p = buf; *p != 0; p++) {
    *out++ = *p;
    if (c == 1) {
      *out++ = '\'';
    }
    c = (c + 1) % 3;
  }
  *--out = 0;

  return q;
}

int main() {
  char factorial20[100];
  printf("%s\n", format_commas(2432902008176640000, factorial20));
}
