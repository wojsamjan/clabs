/* Jakub S³awiñski (Slaughter House Entertainment Group)
 * plik nag³ówkowy do obs³ugi ró¿nych stanów programu
 * stany.h
 */

#ifndef _JS_STANY_H
#define _JS_STANY_H

void Intro(void); /* intro do programu */
void Menu(void); /* g³ówne menu */
void StdMaze(void); /* menu standardowego labiryntu */
void WczytMaze(void); /* wczytywanie nazwy pliku */
void WyswMaze(void); /* wy¶wietlanie labiryntu z StdMaze */
void PojGra(void); /* gra pojedyñcza */
void MultiGra(void); /* gra wieloosobowa */
int HostPort(char*, char*, char*, char*); /* wprowadzenie hosta i portu */

#endif
