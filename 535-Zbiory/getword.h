/*
      $URL: http://manta.univ.gda.pl/svn/wb/labs/c/535-Zbiory/getword.h $
      $Revision: 177 $
 */

#include <stdio.h>

/*  definicja: 
    _słowo_ zaczyna się od jednego ze znaków w zbiorze `first'
    po którym następuje zero lub więcej znaków ze zbioru `rest'.

    funkcja `getword' wczytuje następne słowo z otwartego pliku `fp'  i zwarca 1. 
    Słowo jest zapisywane w `buf' jako napis zakończony null.
    
    Funkcje `first()' i `rest()' służą do sprawdzania czy znak
    należy, odpowiednio, do zbioru <i>first</i> i <i>rest</i>

 */

int getword(FILE *fp, char *buf, int size, int first(int c), int rest(int c));
