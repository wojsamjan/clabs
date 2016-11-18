/*  
 *  File: nim.c
 *
 *  $Revision: 1.1 $
 *  $Date: 2003/10/18 19:04:56 $
 *
    Interfejs do gry w NIM.
 */

#ifndef NIM_INCLUDED
#define NIM_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "simpio.h"
#include "strlib.h"

/* Sta³e:
      MaxTake -- maksymalna liczba ¿etoñw, które gracz mo¿e zabraæ;
      NoGoodMove -- wartownik wskazuj±cy, ¿e nie ma dobrego ruchu. */ 

#define MaxTake 3
#define NoGoodMove -1

typedef enum { Human, Computer } playerT;

/*  Funkcja wypisuj±ca rezultat gry. */

void AnnounceWinner(int nCoins, playerT whoseTurn);

/*  Funkcja umo¿liwiaj±ca wykonanie ruchu u¿ytkownikowi.
    Jej argumentem jest liczba ¿etonów pozostawionych na stosie.
    Funkcja zwraca liczbê ¿etonów zabranych ze stosu przez u¿ytkownika.
    Sprawdza te¿, czy ruch jest poprawny; je¶li nie to umo¿liwia 
    powtórzenie ruchu. */

int GetUserMove(int nCoins);

/*  Funkcja znajduj±ca najlepszy ruch dla komputera i zwracaj±ca 
    liczbê zabranych ¿etonów. Aby znale¿æ wygrywaj±cy ruch wo³a ona 
    `FindGoodMove'. Je¶li nie ma wygrywaj±cego ruchu, to komputer
    zabiera 1 ¿eton, daj±c szansê wygranej cz³owiekowi. */

int ChooseComputerMove(int nCoins);

#endif
