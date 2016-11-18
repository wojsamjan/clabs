/* Plik: oddeven.c
 * --  -------------------------------------------------------------
 * Program ten wczytuje liczbę i klasyfikuje ją jako parzystą
 * lub nieparzystą.
 *
 *
 * Poniższy kod korzysta z funkcji `GetInteger', której kod znajduje
 * się w bibliotece o nazwie `cslib.a'. Autorem tej biblioteki jest
 * prof. E. Roberts z Uniwersytetu Stanforda, USA.
 * Opis funkcji znajdziesz w pliku `simpio.h'. W pliku tym są opisane
 * inne użyteczne funkcje. Koniecznie przeczytaj go!
 * Implementacje funkcji opisanych w `simpio.h' znajdziesz
 * w pliku `simpio.c'.
 *
 * Bardzo bardzo ważna uwaga:
 *
 *   Spróbuj samodzielnie zaimplementować funkcje opisane w `simpio.h'
 *   zanim przeczytasz `simpio.c'.
 *   Jak zwykle, dołącz program testujący Twoją implementację.
 */

#include <stdio.h>
#include "genlib.h"
#include "simpio.h"

int main() {
    long int l;

    printf("Program klasyfikujący liczbę jako parzystą lub nieparzystą.\n");
    printf("l = ? ");
    l = GetLong();
    if (l % 2 == 0) {
        printf("Podałeś liczbę parzystą.\n");
    } else {
        printf("Podałeś liczbę nieparzystą.\n");
    }

    return 0;
}
