#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include <locale.h>

#include <wchar.h>
#include <wctype.h>

void set_locale(void) {
  char *lc_type_name;
  if (!(lc_type_name = setlocale(LC_CTYPE, ""))) {
    fwprintf(stderr, L"Can't set the specified locale!");
    fwprintf(stderr, L"Check LANG, LC_CTYPE, LC_ALL.\n");
    exit(1);
  }
  fwprintf(stderr, L"Convert stdin to uppercase\n\u00AE 2011-2011 Włodek Bzyl\n");
  fwprintf(stderr, L"Current locale LC_CTYPE: %s\n\n", lc_type_name);
}

/*  zamień małe litery na duże  */

int main(int argc, char *argv[]) {
  wint_t c;

  set_locale();

  while ((c = getwchar()) != WEOF)
    putwchar(towupper(c));

  return EXIT_SUCCESS;
}
