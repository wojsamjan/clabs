#ifndef INCLUDED__DIRECTION_STACK_H
#define INCLUDED__DIRECTION_STACK_H

#include "mazelib.h"

/* Funkcje do obs³ugi stosu u¿ywanego do ¶ledzenia rozpatrywanej
 * drogi w algorytmie wyszukiwania wyj¶cia.
 * (musimy rêcznie symulowaæ rekurencjê, bo funkcja szukaj±ca
 * drogê musi wyj¶æ, aby mo¿na by³o efektywnie akutalizowaæ obraz)
 *
 * Na stosie znajduj± siê trójki (d, p, b), gdzie
 * d wyznacza kierunek dalszej wêdrówki, p jest
 * koñcowym punktem drogi, a warto¶æ logiczna b okre¶la,
 * czy poszli¶my ju¿ we wszystkich kierunkach tego punktu */

void ds_push(directionT dir, pointT pt, bool);
void ds_pop(void);
void ds_top(directionT* dir, pointT* pt, bool*);
bool ds_empty(void);
void ds_clear(void);
/* Ustaw warto¶æ kierunku na szczycie stosu */
void ds_set_dir_at_top(directionT dir);
void ds_set_last_d_at_top(bool ld);
void ds_print(void);

#endif

