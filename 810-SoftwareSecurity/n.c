
#include <stdio.h>

int main(int argc, char* argv[])
{
  unsigned int bytes;

  printf("%s%n\n", argv[1], &bytes);
  printf("liczba wpisanych znaków: %d\n", bytes);

  return 0;
}

