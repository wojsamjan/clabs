/*  
 *  File: nim.c
 *
 *  $Revision: 1.1.1.1 $
 *  $Date: 2004/01/24 10:40:34 $
 *
    Interfejs do gry w NIM.
 */

#ifndef NIM_INCLUDED
#define NIM_INCLUDED

#include <stdio.h>
#include <stdlib.h>

/* Sta³e:
      MaxTake -- maksymalna liczba ¿etoñw, które gracz mo¿e zabraæ;
      NoGoodMove -- wartownik wskazuj±cy, ¿e nie ma dobrego ruchu. */ 

#define MaxTake 3
#define NoGoodMove -1

#define NofCoins 5
#define NofRows 3

typedef enum { Human, Computer } playerT;
typedef struct {int row, number;} rowsT;
typedef struct {int tab[4];} stosT;

/*  Funkcja wypisuj±ca rezultat gry. */

void AnnounceWinner(int nCoins, playerT whoseTurn);

/*  Funkcja umo¿liwiaj±ca wykonanie ruchu u¿ytkownikowi.
    Jej argumentem jest liczba ¿etonów pozostawionych na stosie.
    Funkcja zwraca liczbê ¿etonów zabranych ze stosu przez u¿ytkownika.
    Sprawdza te¿, czy ruch jest poprawny; je¶li nie to umo¿liwia 
    powtórzenie ruchu. */

rowsT GetUserMove(int tab[]);

/*  Funkcja znajduj±ca najlepszy ruch dla komputera i zwracaj±ca 
    liczbê zabranych ¿etonów. Aby znale¿æ wygrywaj±cy ruch wo³a ona 
    `FindGoodMove'. Je¶li nie ma wygrywaj±cego ruchu, to komputer
    zabiera 1 ¿eton, daj±c szansê wygranej cz³owiekowi. */

rowsT ChooseComputerMove(int tab[]);
void Wypis(int tab[]);

#endif
