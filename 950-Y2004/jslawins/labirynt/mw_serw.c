/* Jakub S³awiñski (Slaughter House Entertainment Group)
 * plik implementuj±cy serwer gry maze walker
 * mw_serw.c
 */

#include <string.h>
#include <sys/select.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include "mw_serw.h"
#include "mw_klie.h"
#include "mw_maze.h"
#include "siec.h"
#include "myfunkc.h"

/* struktura danych do trzymania serwera */
serwT serwer;

int
Postaw(char typ, int ilosc, char* host, char* port)
{
	Zamknij(0);
	if ((typ != 'l') && (typ != 'n'))
		return 1;
	serwer.typ = typ;
	serwer.listenfd = -1;
	if (TypS() == 'n') { /* gra wieloosobowa */
		if (tcpSluchaj(&serwer.listenfd, host, port, &serwer.addrlen))
			return 2;
	}
	pipe(serwer.sock);
	if (ilosc < 1)
		ilosc = 1;
	serwer.numspac = ilosc;
	serwer.tablica = calloc(ilosc, sizeof(playerT));
	serwer.zalid = -1;
	serwer.running = 1;
	return 0;
}

int
ZacznijGre(char wielkosc)
{
	int i;
	switch (wielkosc) {
		case 0: {
			GenerujLabirynt(myrand(5,10), myrand(5,10));
			break;
			}
		case 1: {
			GenerujLabirynt(myrand(10,20), myrand(10,20));
			break;
			}
		case 2: {
			GenerujLabirynt(myrand(20,40), myrand(20,40));
			break;
			}
		case 3: {
			GenerujLabirynt(myrand(40,60), myrand(40,60));
			break;
			}
		case 4: {
			GenerujLabirynt(myrand(60,100), myrand(60,100));
			break;
			}
		case 5: {
			GenerujLabirynt(myrand(100,150), myrand(100,150));
			break;
			}
		case 6: {
			GenerujLabirynt(myrand(150,250), myrand(150,250));
			break;
			}
		default: {
			GenerujLabirynt(myrand(5,80), myrand(5,80));
			break;
			 }
	}
	serwer.jestgra = 1;
	for (i = 0; i < Miejsca(); ++i) {
		if (serwer.tablica[i].stan == 0)
			continue;
		PiszGracz(i, 118, Zalozyciel(), S_STARTED, 0, NULL);
	}
	return 0;
}

int
PiszGracz(int numer, char magic, char id, char typ, char arg, unsigned char buf[])
{
	unsigned char wiadomosc[13];
	wiadomosc[0] = magic;
	wiadomosc[1] = id;
	wiadomosc[2] = typ;
	wiadomosc[3] = arg;
	if (buf)
		memcpy(&wiadomosc[4], buf, 9);
	if (numer < 0 || numer >= Miejsca())
		return 1;
	if (serwer.tablica[numer].stan == 0)
		return 1;
	if (write(serwer.tablica[numer].fd2, wiadomosc, 13) <= 0)
		return 1;
	return 0;
}

void *
Przetwarzaj(void* vptr)
{
	int i, j, max, n;
	fd_set rset, allset;
	unsigned char bufor[13];
	struct sockaddr *cliaddr = NULL;
	socklen_t	len;

	pthread_detach(pthread_self());
	if (DzialaSerwer() != 1)
		return NULL;
	serwer.running = 2;
	if (TypS() == 'n') { /* gra wieloosobowa */
		cliaddr = malloc(serwer.addrlen);
	}
	
	max = 0;
	FD_ZERO(&rset);
	FD_SET(serwer.sock[0], &rset);
	max = (max > serwer.sock[0]) ? max : serwer.sock[0];
	for (i = 0; i < Miejsca(); ++i) {
		if (serwer.tablica[i].stan) {
			FD_SET(serwer.tablica[i].fd, &rset);
			max = (max > serwer.tablica[i].fd) ? max : serwer.tablica[i].fd;
		}
	}
	if (TypS() == 'n') {
	FD_SET(serwer.listenfd, &rset);
	max = (max > serwer.listenfd) ? max : serwer.listenfd;
	}
	while (1) {
		allset = rset;
		select(max + 1, &allset, NULL, NULL, NULL);
			for (i = 0; i < Miejsca(); ++i) {
				if (FD_ISSET(serwer.tablica[i].fd, &allset)) {
					if ((n = read(serwer.tablica[i].fd, bufor, 13)) == 13) {
						/* przetworzenie polecenia */
						switch (bufor[2]) {
							case K_LOGIN: {
									      if (JestGra()) {
								      FD_CLR(serwer.tablica[i].fd, &rset);
											UsunGracza(i);
									      }
									      else {
							PiszGracz(i, 118, i, S_ACCEPT, serwer.numspac, NULL);
									      }
									      break;
								      }
							case S_NAME: {
							     memcpy(serwer.tablica[i].name, &bufor[4], 9);
							     if (bufor[4])
								     for (j = 0; j < Miejsca(); ++j) {
									     PrzeslijImie(j);
								     }
									     break;
								     }
							case S_KICKOFF: {
								      if (serwer.zalid == i) {
									        if (bufor[3] != i) {
							      FD_CLR(serwer.tablica[bufor[3]].fd, &rset);
										      UsunGracza(bufor[3]);
									        }
									      }
									      else {
								      FD_CLR(serwer.tablica[i].fd, &rset);
										      UsunGracza(i);
									      }
									      break;
								      }
							case K_ZALOZ: {
						      if ((!serwer.jestgra) && (serwer.zalid == i)) {
							      ZacznijGre(bufor[3]);
									      }
									      else {
								      FD_CLR(serwer.tablica[i].fd, &rset);
										      UsunGracza(i);
									      }
									      break;
								      }
							case S_MAXXY: {
									      if (serwer.jestgra) {
						      bufor[3] = RozmiarX(0);
						      bufor[2] = RozmiarX(0)>>8;
						      bufor[1] = RozmiarX(0)>>16;
						      bufor[0] = RozmiarX(0)>>24;
						      bufor[7] = RozmiarY(0);
						      bufor[6] = RozmiarY(0)>>8;
						      bufor[5] = RozmiarY(0)>>16;
						      bufor[4] = RozmiarY(0)>>24;
						      serwer.tablica[i].pozycja.x = PobierzStart().x;
						      serwer.tablica[i].pozycja.y = PobierzStart().y;
						      PiszGracz(i, 118, Zalozyciel(), S_MAXXY, 0, bufor);
									      }
									      else {
								      FD_CLR(serwer.tablica[i].fd, &rset);
										      UsunGracza(i);
									      }
								      break;
								      }
							case S_WSPOL: {
								      PrzeslijWspolrzedne(i);
								      break;
								      }
							case S_OKOLICA: {
									PrzeslijOtoczenie(i);
									break;
									}
							case K_MOVE: {
								     switch (bufor[3]) {
									     case 'n': {
				if ((NaZewnatrz(PunktObok(serwer.tablica[i].pozycja, North), 0) != 1) &&
						(!JestMur(PunktObok(serwer.tablica[i].pozycja, North), 0))) {
				serwer.tablica[i].pozycja = PunktObok(serwer.tablica[i].pozycja, North);
				PrzeslijWspolrzedne(i);
				PrzeslijOtoczenie(i);
				serwer.tablica[i].ruchy++;
				}
											       break;
										       }
									     case 's': {
				if ((NaZewnatrz(PunktObok(serwer.tablica[i].pozycja, South), 0) != 1) &&
						(!JestMur(PunktObok(serwer.tablica[i].pozycja, South), 0))) {
				serwer.tablica[i].pozycja = PunktObok(serwer.tablica[i].pozycja, South);
				PrzeslijWspolrzedne(i);
				PrzeslijOtoczenie(i);
				serwer.tablica[i].ruchy++;
				}
											       break;
										       }
									     case 'w': {
				if ((NaZewnatrz(PunktObok(serwer.tablica[i].pozycja, West), 0) != 1) &&
						(!JestMur(PunktObok(serwer.tablica[i].pozycja, West), 0))) {
				serwer.tablica[i].pozycja = PunktObok(serwer.tablica[i].pozycja, West);
				PrzeslijWspolrzedne(i);
				PrzeslijOtoczenie(i);
				serwer.tablica[i].ruchy++;
				}
											       break;
										       }
									     case 'e': {
				if ((NaZewnatrz(PunktObok(serwer.tablica[i].pozycja, East), 0) != 1) &&
						(!JestMur(PunktObok(serwer.tablica[i].pozycja, East), 0))) {
				serwer.tablica[i].pozycja = PunktObok(serwer.tablica[i].pozycja, East);
				PrzeslijWspolrzedne(i);
				PrzeslijOtoczenie(i);
				serwer.tablica[i].ruchy++;
				}
											       break;
										       }
								     }
					if (NaZewnatrz(serwer.tablica[i].pozycja, 0) == 2) {
						      bufor[3] = serwer.tablica[i].ruchy;
						      bufor[2] = serwer.tablica[i].ruchy>>8;
						      bufor[1] = serwer.tablica[i].ruchy>>16;
						      bufor[0] = serwer.tablica[i].ruchy>>24;
						      n = NajkrotszaSciezka(PobierzStart());
						      --n;
						      bufor[7] = n;
						      bufor[6] = n>>8;
						      bufor[5] = n>>16;
						      bufor[4] = n>>24;
						      for (j = 0; j < Miejsca(); ++j) {
							      if (serwer.tablica[j].stan)
					      PiszGracz(j, 118, Zalozyciel(), S_EXIT, i, bufor);
						      }
					      pthread_exit(0);
					}
					break;
								     }
							case K_LOGOUT: {
							      FD_CLR(serwer.tablica[i].fd, &rset);
									       UsunGracza(i);
								     for (j = 0; j < Miejsca(); ++j) {
									     if (serwer.tablica[j].stan) {
									     if (i==Zalozyciel()) {
					      PiszGracz(j, 118, i, S_KICKOFF, i, 0);
								     }
									     else {
					      PiszGracz(j, 118, i, K_LOGOUT, i, 0);
									     }
									     }
								     }
								     if (i == Zalozyciel()) {
									     Zamknij(0);
									       pthread_exit(0);
								     }
								       break;
								       }
						}
					}
					else if (n == 0) {
						/* gracz zakoñczy³ grê */
					      FD_CLR(serwer.tablica[i].fd, &rset);
						UsunGracza(i);
					}
					else {
						/* co¶ z³ego siê sta³o -> trzeba wyrzuciæ gracza */
					      FD_CLR(serwer.tablica[i].fd, &rset);
						UsunGracza(i);
					}
				}
			}
			
			if (TypS() == 'n')
			if (FD_ISSET(serwer.listenfd, &allset)) {
				len = serwer.addrlen;
				n = accept(serwer.listenfd, cliaddr, &len);
				DodajGracza(n, 0);
				FD_SET(n, &rset);
				max = (max > n) ? max : n;
			}
			
			if (serwer.zalid == -1)
			if (FD_ISSET(serwer.sock[0], &rset)) {
				if ((n = read(serwer.sock[0], bufor, 13)) == 13) {
					switch (bufor[2]) {
						case K_LOGIN: {
						DodajGracza(DajFd(), 1);
				PiszGracz(Zalozyciel(), 118, Zalozyciel(), S_ACCEPT, serwer.numspac, NULL);
								      break;
							      }
					}
				}
			}
	}
}

int
Zamknij(int powod)
{
	int i;
	if (JestGra()) {
		if (serwer.tablica) {
			for (i = 0; i < Miejsca(); ++i) {
				if (serwer.tablica[i].stan) {
					PiszGracz(i, 118, Zalozyciel(), S_KONIEC, 0, NULL);
					if (serwer.tablica[i].name)
						free(serwer.tablica[i].name);
				}
			}
			free(serwer.tablica);
		}
		serwer.jestgra = 0;
	}
	serwer.typ = 0;
	if (serwer.listenfd)
		close(serwer.listenfd);
	serwer.listenfd = 0;
	serwer.addrlen = 0;
	if (serwer.sock[0]) {
		close(serwer.sock[0]);
		close(serwer.sock[1]);
	}
	serwer.sock[0] = 0;
	serwer.sock[1] = 0;
	serwer.numplay = 0;
	serwer.numspac = 0;
	serwer.zalid = 0;
	serwer.running = 0;
	return 0;
}

int
DodajGracza(int fd, char tozalozyciel)
{
	int i;
	for (i = 0; i < Miejsca(); ++i) {
		if (serwer.tablica[i].stan == 0) {
			serwer.tablica[i].fd2 = fd;
			serwer.tablica[i].stan = 1;
			serwer.tablica[i].id = i;
			if (!serwer.tablica[i].name) {
				serwer.tablica[i].name = calloc(10, sizeof(char));
			}
			else {
				memset(serwer.tablica[i].name, 0, 10);
			}
			serwer.tablica[i].pozycja.x = -1;
			serwer.tablica[i].pozycja.y = -1;
			serwer.tablica[i].ruchy = 0;
			serwer.numplay++;
			if (tozalozyciel) {
				serwer.zalid = i;
				serwer.tablica[i].fd = serwer.sock[0];
			}
			else {
				serwer.tablica[i].fd = fd;
			}
			break;
		}
	}
	return 0;
}

int
UsunGracza(int num) {
	int i;
	if ((num < 0) || (num >= Miejsca()))
		return 1;
	if (serwer.tablica[num].fd) {
		PiszGracz(num, 118, Zalozyciel(), S_KICKOFF, 0, NULL);
		close(serwer.tablica[num].fd);
	}
	serwer.tablica[num].stan = 0;
	serwer.tablica[num].fd = 0;
	for (i = 0; i < Miejsca(); ++i) {
	     if (serwer.tablica[i].stan) {
		      PiszGracz(i, 118, Zalozyciel(), K_LOGOUT, num, 0);
	     }
	}
	return 0;
}

char
CoJestNa(punktT miejsce) {
	if (NaZewnatrz(miejsce, 0) == 2) {
		return 'E';
	}
	if (NaZewnatrz(miejsce, 0)) {
		return '?';
	}
	if (JestMur(miejsce, 0)) {
		return '#';
	}
	return '.';
}

int
PrzeslijOtoczenie(int num)
{
	unsigned char otoczenie[9];
	punktT iterator;
	iterator = serwer.tablica[num].pozycja;
	iterator.x--; iterator.y++;
	otoczenie[0] = CoJestNa(iterator);
	iterator.x++;
	otoczenie[1] = CoJestNa(iterator);
	iterator.x++;
	otoczenie[2] = CoJestNa(iterator);
	iterator.x--; iterator.x--; iterator.y--;
	otoczenie[3] = CoJestNa(iterator);
	iterator.x++;
	otoczenie[4] = CoJestNa(iterator);
	iterator.x++;
	otoczenie[5] = CoJestNa(iterator);
	iterator.x--; iterator.x--; iterator.y--;
	otoczenie[6] = CoJestNa(iterator);
	iterator.x++;
	otoczenie[7] = CoJestNa(iterator);
	iterator.x++;
	otoczenie[8] = CoJestNa(iterator);
	PiszGracz(num, 118, Zalozyciel(), S_OKOLICA, 0, otoczenie);
	return 0;
}

int
PrzeslijWspolrzedne(int num)
{
	unsigned char bufor[9];
	int i;
      bufor[3] = serwer.tablica[num].pozycja.x;
      bufor[2] = serwer.tablica[num].pozycja.x>>8;
      bufor[1] = serwer.tablica[num].pozycja.x>>16;
      bufor[0] = serwer.tablica[num].pozycja.x>>24;
      bufor[7] = serwer.tablica[num].pozycja.y;
      bufor[6] = serwer.tablica[num].pozycja.y>>8;
      bufor[5] = serwer.tablica[num].pozycja.y>>16;
      bufor[4] = serwer.tablica[num].pozycja.y>>24;
      for (i = 0; i < Miejsca(); ++i) {
	      if (serwer.tablica[i].stan) {
		      PiszGracz(i, 118, Zalozyciel(), S_WSPOL, num, bufor);
	      }
      }
	return 0;
}

int
Miejsca(void)
{
	return serwer.numspac;
}

int
Ilosc(void)
{
	return serwer.numplay;
}

int
JestGra(void)
{
	return serwer.jestgra;
}

char
TypS(void)
{
	return serwer.typ;
}

int
Zalozyciel(void)
{
	return serwer.zalid;
}

int
Rura(void)
{
	return serwer.sock[1];
}

int
DzialaSerwer(void)
{
	return serwer.running;
}

int
PrzeslijImie(int num)
{
	int i;
	unsigned char wiadomosc[9];
	if ((num < 0) || (num >= Miejsca()))
		return 1;
	if (serwer.tablica[num].stan) {
		if (serwer.tablica[num].name) {
			memcpy(wiadomosc, serwer.tablica[num].name, 9);
			for (i = 0; i < Miejsca(); ++i) {
				PiszGracz(i, 118, num, S_NAME, num, wiadomosc);
			}
		}
	}
	return 0;
}
