/* Jakub S³awiñski (Slaughter House Entertainment Group)
 * plik nag³ówkowy do funkcji operuj±cych na labiryntach
 * mw_lib.h
 */

#ifndef _JS_MW_LIB_H
#define _JS_MW_LIB_H

/* punktT - podstawowy typ dla wspó³rzêdnych na p³aszczy¼nie */

typedef struct {
  int x, y;
} punktT;

/* labiryntT - struktura danych do zapamiêtywania labiryntów */

typedef struct {
	int xsize, ysize;
	punktT startpos;
	char** powierzchnia;
} labiryntT;

/* kierunkiT - reprezentuje mo¿liwe kierunki w labiryncie */

typedef enum { North, East, South, West} kierunkiT;

int CzytajLabirynt(char*); /* czytanie z pliku */
int GenerujLabirynt(int, int); /* generowanie labiryntu */
int PustyLabirynt(char, int, int, char); /* stworzenie pustego labiryntu (wype³nionego znakami znak) */
punktT PobierzStart(void); /* wspó³rzêdne punktu startowego */
punktT PunktObok(punktT, kierunkiT); /* wspó³rzêdne punktu w danym kierunku */
int NaZewnatrz(punktT, char); /* czy punkt jest poza labiryntem? */
int JestMur(punktT, char); /* czy w danym punkcie jest ¶ciana? */
void Zaznacz(punktT, char); /* zaznaczenie punktu */
void Odznacz(punktT); /* odznaczenie punktu */
int JestZaznaczone(punktT, char); /* czy punkt jest zaznaczony? */
int RozmiarX(char); /* podaje rozmiar x */
int RozmiarY(char); /* podaje rozmiar y */

void KlientaLabRysuj(int xoff, int yoff); /* rysuje labirynt klienta */
                   
#endif
