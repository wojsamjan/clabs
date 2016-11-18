#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <errno.h>

#include <locale.h>

#include <wchar.h>
#include <wctype.h>

int main()
{
  wchar_t *word;
  wchar_t buff[40][11];
  FILE *h;
  int i = 0;

  setlocale(LC_CTYPE, "");

  wprintf(L"size of word array: %d\n", sizeof word);

  if ((h = fopen("20.dat", "r")) == NULL) {
    wprintf(L"Brak pliku ze słowami 20.dat\n");
    exit(1);
  }

  while (fgetws(buff[i], 10, h) != NULL) {
    buff[i][5] = L'\0';
    wprintf(L"%2d: %ls (%d)\n", i, buff[i], wcslen(buff[i]));
    i++;
  }

  word = buff[19];

  wprintf(L"\nword: %ls\n", word);

  *(word + 2) = L'X';
  wprintf(L"\nword[2] = %lc\n", *(word + 2));

  wprintf(L"\nword: %ls\n", word);

  return 0;
}
