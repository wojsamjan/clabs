/* Jakub S³awiñski (Slaughter House Entertainment Group)
 * plik nag³ówkowy do obs³ugi grafiki
 * grafika.h
 */

#include <ncurses/ncurses.h>

#ifndef _JS_GRAFIKA_H
#define _JS_GRAFIKA_H

void Inicjuj(void);
void Zakoncz(void);
void Odswiez(void);
void PiszNaMain(int, int, int, char*, ...);
void PiszNaMainS(int, int, char*, ...);
void PiszNaInfo(int, int, int, char*, ...);
void PiszNaInfoS(int, int, char*, ...);
void OczyscMain(void);
void OczyscInfo(void);
int MaxEkranX(void);
int MaxEkranY(void);

int PobierzZnak(void); /* ta funkcja tutaj, gdy¿ ncurses pobiera znaki */

#endif
