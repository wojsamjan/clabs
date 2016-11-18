# UTF-8

Programy kompilujemy tak:

    cc -std=c99 -Wall FILENAME

Some C functions are locale dependent, but work in UTF-8 locales just as well:

    strcoll
    strxfrm

Tak sprawdzamy z wiersza poleceń dostępne locales:

    locale -a | egrep -i pl
      csb_PL
      csb_PL.utf8
      pl_PL
      pl_PL.iso88592
      pl_PL.utf8

Nie używamy jednocześnie funkcji *char* i *wchar*, na przykład:
*printf* i *wprintf*.

## man pages

* `wchar.h`
* `wctype.h`

Dokumentację do funkcji znajdziemy [FreeBSD Man Pages](http://www.freebsd.org/cgi/man.cgi).

## Linki

* [The GNU C Library](http://www.gnu.org/software/libc/manual/html_mono/libc.html)
* [6.3.3](http://www.gnu.org/s/libc/manual/html_node/Converting-a-Character.html#Converting-a-Character) –
  przykład *mbstouwcs*
* [Unicode: What You Can Do About It Today](http://www.cprogramming.com/tutorial/unicode.html)
