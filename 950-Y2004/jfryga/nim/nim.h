

#ifndef NIM_INCLUDED
#define NIM_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "simpio.h"
#include "strlib.h"

 

#define NoGoodMove -1


typedef enum { Human, Computer } playerT;

typedef struct {
int nKtory, nTaken;
} moveT;

typedef struct 
{
int r[4];
} stosT;

stosT stos;
moveT ile;
playerT whoseTurn;

/*  Funkcja wypisujca rezultat gry. */

void AnnounceWinner(int nCoins, playerT whoseTurn);

/*  Funkcja umoliwiajca wykonanie ruchu uytkownikowi.
    Jej argumentem jest liczba etonw pozostawionych na stosie.
    Funkcja zwraca liczb�etonw zabranych ze stosu przez uytkownika.
    Sprawdza te, czy ruch jest poprawny; jeli nie to umoliwia 
    powtrzenie ruchu. */

moveT GetUserMove(int tab[]);

/*  Funkcja znajdujca najlepszy ruch dla komputera i zwracajca 
    liczb�zabranych etonw. Aby znale�wygrywajcy ruch woa ona 
    `FindGoodMove'. Jeli nie ma wygrywajcego ruchu, to komputer
    zabiera 1 eton, dajc szans�wygranej czowiekowi. */

moveT ChooseComputerMove(int tab[]);
void pokaz(int tab[]);

#endif
