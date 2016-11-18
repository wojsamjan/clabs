#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <errno.h>

#include <locale.h>

#include <wchar.h>
#include <wctype.h>

int main()
{
  wchar_t *wcs = L"żyźny żywił\n";
  int      i;

  setlocale(LC_CTYPE, "");

  for (i = 0; wcs[i] != L'\0'; i++) {
    errno = 0;
    if (WEOF == putwchar(wcs[i])) {
      wprintf(L"Unable to putwchar() the wide character.\n");
      if (EILSEQ == errno)
        wprintf(L"An invalid wide character was encountered.\n");
      exit(EXIT_FAILURE);
    }
  }
  return 0;
}
