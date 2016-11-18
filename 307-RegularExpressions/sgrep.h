/*
     wyrażenie regularne jest ciągiem znaków definiujacych
     zbiór zgodnych napisów

     Podstawowe wyrażenia regularne

     znak             |  znaczenie
     --------------------------------------------------------------
      c               |  zgodny ze samym sobą
      .   (kropka)    |  zgodny z dowolnym znakiem
      ^               |  zgodny z początkiem napisu
      $               |  zgodny z końcem napisu
      *   (gwiazdka)  |  zgodny z dowolna liczbą poprzednich znaków

      Uwaga: znaki . ^ $ * to ,metaznaki'

      Przykłady:

      1. Wyrażenie regularne 'x.y' jest zgodne z napisem
         'xay' oraz napisem 'x8y'
         ale nie jest zgodne z napisem 'xy' ani napisem 'xaby' itp.
      2. Wyrażenie regularne '^.$' jest zgodne z każdym napisem
         składającym się z jednego znaku.

      Uwaga: czasami mówimy jest dopasowane do napisu
             zamiast jest zgodne z napisem
 */

#ifndef _sgrep_h
#define _sgrep_h

/* grep: szukanie regexp w pliku */
int sgrep(char *regexp, FILE *f, char *name);

/* match: szukanie wyrażenia regexp w napisie text */
int match(char *regexp, char *text);

/* matchhere: szukanie wyrażenia regexp od początku napisu */
int matchhere(char *regexp, char *text);

/* matchstar: szukanie c*regexp od początku napisu text */
int matchstar(int c, char *regexp, char *text);

#endif
