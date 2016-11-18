/* Plik: euclid.c                                    24 III 2002
 * -------------------------------------------------------------
 * Program ten oblicza największy wspólny dzielnik (NWD) z dwóch
 * liczb podanych na standardowym wejściu.
 * NWD jest obliczany przy pomocy algorytmu Euklidesa.
 * 
 * Ten program korzysta również z biblioteki `cslib.a'
 * (zob. `oddeven.c').
 */

#include <stdio.h>
#include "genlib.h"
#include "simpio.h"

/* Prototyp funkcji */

int NWD(int x, int y);

int main() {
    int x, y;

    printf("Program ten oblicza Największy Wspólny Dzielnik (NWD).\n");
    printf("Podaj dwie liczby całkowite, x i y.\n");
    printf("\tx = ? ");
    x = GetInteger();
    printf("\ty = ? ");
    y = GetInteger();
    printf("\tNWD(%d,%d) = %d.\n", x, y, NWD(x, y));

    return 0;
}

/*
 * Funkcja: NWD
 * Użycie: nwd = NWD(x, y);
 * -----------------------
 * Funkcja zwraca największy wspólny dzielnik x i y.
 * wyliczony przy pomocy algorytmu Euklidesa (zob.
 * Twierdzenie 7 w Księdze II Elementów Euklidesa).
 */

int NWD(int x, int y)
{
    int r;

    while (TRUE) {
        r = x % y;
        if (r == 0) break;
        x = y;
        y = r;
    }
    return (y);
}
