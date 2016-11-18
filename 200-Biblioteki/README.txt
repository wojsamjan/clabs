Biblioteki statyczne i dzielone
===============================

Przykłady z książki:

  K. Wall. Linux -- Programowanie w przykładach. MIKOM 2000


Narzędzia biblioteczne
----------------------

  nm  -- wypisz wszystkie symbole z pliku obiektowego/binarnego

  Przykłady:

    nm /usr/lib/libm.so
    nm -u /usr/lib/libm.so   # tylko niezdefiniowane symbole

  ar  -- utwórz, modyfikuj, rozpakuj archiwum (bibliotekę statyczną)

  Przykład:

    ar rcs liberr.a liberr.o  # insert, create, create index

  ldd  -- wypisz biblioteki dzielone wymagane do działania programu

  Przykład:

    ldd a.out
    ldd /bin/bash

  Zobacz też: man ldconfig, man ld.so (zmienna LD_LIBRARY_PATH)


Narzędzie libtool
-----------------

    Zadanie domowe: jak z niego korzystać -- modyfikacja Makefile
