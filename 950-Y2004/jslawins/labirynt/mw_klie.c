/* Jakub S³awiñski (Slaughter House Entertainment Group)
 * plik implementuj±cy klienta gry maze walker
 * mw_klie.c
 */

#include <string.h>
#include <sys/select.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include "mw_serw.h"
#include "mw_maze.h"
#include "siec.h"
#include "myfunkc.h"
#include "mw_klie.h"
#include "grafika.h"


klientT klient;

int
KlientInicjuj(char typ, char* host, char* port)
{
	int gniazda[2];
	unsigned char bufor[13];
	int miejsca;
	if ((typ != 'n') && (typ != 'l'))
		return 1;
	klient.ruchy = 0;
	if (typ == 'l') { /* gra pojedyñcza */
		pipe(gniazda);
		klient.fd = klient.fds = klient.fd2 = -1;
		klient.fd = gniazda[1];
		klient.fds = Rura();
		klient.fd2 = gniazda[0];
	}
	else { /* gra wieloosobowa */
		if(tcpPolacz(&klient.fd2, host, port))
			return 2;
		klient.fds = klient.fd2;
	}
	if (klient.czygracz)
		free(klient.czygracz);
	if (klient.pozgraczy)
		free(klient.pozgraczy);
	if (klient.imionagraczy) {
		for (miejsca = 0; miejsca < klient.miejsca; ++miejsca) {
			if (klient.imionagraczy[miejsca]) {
				free(klient.imionagraczy[miejsca]);
			}
		}
		free(klient.imionagraczy);
	}
	PiszDoSerwera(118, 0, K_LOGIN, 0, 0);
	if (read(klient.fd2, bufor, 13) != 13)
		return 3;
	if (bufor[2] != S_ACCEPT)
		return 4;
	miejsca = bufor[3];
	klient.miejsca = miejsca;
	klient.czygracz = calloc(miejsca, sizeof(char));
	klient.pozgraczy = calloc(miejsca, sizeof(punktT));
	klient.imionagraczy = calloc(miejsca, sizeof(char*));
	for (miejsca = 0; miejsca < klient.miejsca; ++miejsca) {
		klient.imionagraczy[miejsca] = calloc(10, sizeof(char));
	}
	miejsca = bufor[1];
	klient.id = miejsca;
	return 0;
}

int
PiszDoSerwera(char magic, char id, char typ, char arg, char buf[])
{
	char wiadomosc[13];
	memset(wiadomosc, 0, 13);
	wiadomosc[0] = magic;
	wiadomosc[1] = id;
	wiadomosc[2] = typ;
	wiadomosc[3] = arg;
	if (buf)
		memcpy(&wiadomosc[4], buf, 9);
	if (write(klient.fds, wiadomosc, 13) <= 0)
		return 1;
	return 0;
}

void
ZamienAnaII(int* sx, int* sy, unsigned char bufor[])
{
	(*sx) = bufor[4];
	(*sx) <<= 8;
	(*sx) += bufor[5];
	(*sx) <<= 8;
	(*sx) += bufor[6];
	(*sx) <<= 8;
	(*sx) += bufor[7];
	(*sy) = bufor[8];
	(*sy) <<= 8;
	(*sy) += bufor[9];
	(*sy) <<= 8;
	(*sy) += bufor[10];
	(*sy) <<= 8;
	(*sy) += bufor[11];
}

void
ZmienOkolice(unsigned char bufor[])
{
	punktT iterator;
	iterator = klient.pozycja;
	iterator.x--; iterator.y++;
	Zaznacz(iterator, bufor[4]);
	iterator.x++;
	Zaznacz(iterator, bufor[5]);
	iterator.x++;
	Zaznacz(iterator, bufor[6]);
	iterator.x--; iterator.x--; iterator.y--;
	Zaznacz(iterator, bufor[7]);
	iterator.x++;
	Zaznacz(iterator, bufor[8]);
	iterator.x++;
	Zaznacz(iterator, bufor[9]);
	iterator.x--; iterator.x--; iterator.y--;
	Zaznacz(iterator, bufor[10]);
	iterator.x++;
	Zaznacz(iterator, bufor[11]);
	iterator.x++;
	Zaznacz(iterator, bufor[12]);
}

int
Dzialaj(void)
{
	int sx, sy, znak, maxfdp1, n, i;
	unsigned char bufor[13];
	char flagawyjscia;
	fd_set rset, allset;
	struct timeval tv;
	char wielok, wspok, okook;

	wielok = wspok = okook = 1;
	flagawyjscia=1;
	FD_ZERO(&rset);
	FD_SET(STDIN_FILENO, &rset);
	FD_SET(klient.fd2, &rset);
	maxfdp1 = (klient.fd2 > STDIN_FILENO) ? (klient.fd2+1) : (STDIN_FILENO+1);

	PiszDoSerwera(118, 0, S_MAXXY, 0, 0);
	PiszDoSerwera(118, 0, S_WSPOL, 0, 0);
	PiszDoSerwera(118, 0, S_OKOLICA, 0, 0);

	while (wielok || wspok || okook) {
		if (read(klient.fd2, bufor, 13) != 13)
			return 1;
		switch (bufor[2]) {
			case S_MAXXY: {
					      if (wielok == 0) return 2;
					      wielok = 0;
					      ZamienAnaII(&sx, &sy, bufor);
					      PustyLabirynt(1, sx, sy, '?');
					      break;
				      }
			case S_WSPOL: {
					      ZamienAnaII(&sx, &sy, bufor);
					      if (bufor[3] == klient.id) {
						      if (wspok == 0) return 3;
						      wspok = 0;
					      klient.pozycja.x = sx;
					      klient.pozycja.y = sy;
					      }
					      klient.pozgraczy[bufor[3]].x = sx;
					      klient.pozgraczy[bufor[3]].y = sy;
					      break;
				      }
			case S_OKOLICA: {
						if (okook == 0) return 4;
						okook = 0;
						ZmienOkolice(bufor);
					      break;
				      }
			default: {
					 return 5;
					 break;
				 }
		}
	}
	
	gettimeofday(&klient.tv, 0);
	
	while (flagawyjscia) {
		allset = rset;
		RysujLabirynt(((klient.pozycja.x-(MaxEkranX()/2))>0)?(klient.pozycja.x-(MaxEkranX()/2)):0,
		((klient.pozycja.y-((MaxEkranY()-5)/2))>0)?(klient.pozycja.y-((MaxEkranY()-5)/2)):0, 1);
		for (i = 0; i < klient.miejsca; ++i) {
			if (i != klient.id)
				if (klient.czygracz[i]) {
					if (((klient.pozycja.x - klient.pozgraczy[i].x) >= (MaxEkranX()/2))||
					   ((klient.pozgraczy[i].x - klient.pozycja.x) >= (MaxEkranX()/2)))
						continue;
				if (((klient.pozycja.y - klient.pozgraczy[i].y) >= ((MaxEkranY()-5)/2))||
				   ((klient.pozgraczy[i].y - klient.pozycja.y) >= ((MaxEkranY()-5)/2)))
					continue;
				/* w tym miejscu wiemy ju¿, ¿e widaæ drugiego gracza */
PiszNaMain(5, (klient.pozycja.x > (MaxEkranX()/2))?
		((MaxEkranX()/2)-klient.pozycja.x+klient.pozgraczy[i].x):
		(klient.pozycja.x-klient.pozycja.x+klient.pozgraczy[i].x),
	(klient.pozycja.y>((MaxEkranY()-5)/2))?(((MaxEkranY()-5)/2)-klient.pozycja.y+klient.pozgraczy[i].y):
	(klient.pozycja.y-klient.pozycja.y+klient.pozgraczy[i].y),
		"@");
				}
		}
		PiszNaMain(7, (klient.pozycja.x > (MaxEkranX()/2))?(MaxEkranX()/2):klient.pozycja.x,
				(klient.pozycja.y>((MaxEkranY()-5)/2))?((MaxEkranY()-5)/2):klient.pozycja.y,
				"@");
		RysujInfo(2);
		Odswiez();
		select(maxfdp1, &allset, NULL, NULL, NULL);
		if (FD_ISSET(STDIN_FILENO, &allset)) {
			znak = PobierzZnak();
			switch (znak) {
				case 'w': {
						  PiszDoSerwera(118, 0, K_MOVE, 'n', 0);
						  break;
					  }
				case 's': {
						  PiszDoSerwera(118, 0, K_MOVE, 's', 0);
						  break;
					  }
				case 'a': {
						  PiszDoSerwera(118, 0, K_MOVE, 'w', 0);
						  break;
					  }
				case 'd': {
						  PiszDoSerwera(118, 0, K_MOVE, 'e', 0);
						  break;
					  }
				case 'q': case 'Q': {
						  PiszDoSerwera(118, 0, K_LOGOUT, 0, 0);
						  flagawyjscia=0;
						  OczyscMain();
						  PiszNaMainS(7, 10, "Zakoñczy³e¶ grê!");
						  RysujInfo(3);
						  Odswiez();
						  mysleep(1);
							    break;
						    }
			}
		}
		if (FD_ISSET(klient.fd2, &allset)) {
			if (read(klient.fd2, bufor, 13) != 13) 
				return 1;
			switch (bufor[2]) {
				case S_WSPOL : {
						ZamienAnaII(&sx, &sy, bufor);
						if (bufor[3] == klient.id) {
						klient.ruchy++;
						klient.pozycja.x = sx;
						klient.pozycja.y = sy;
						}
						klient.pozgraczy[bufor[3]].x = sx;
						klient.pozgraczy[bufor[3]].y = sy;
						break;
					       }
				case S_OKOLICA : {
							 ZmienOkolice(bufor);
							 break;
						 }
				case S_NAME : {
						      if (bufor[3] < klient.miejsca) {
							      klient.czygracz[bufor[3]] = 1;
						      }
					      }
				case K_LOGOUT : {
							OczyscInfo();
					PiszNaInfoS(7, 1, "%s siê wylogowa³!", klient.imionagraczy[bufor[3]]);
							Odswiez();
							mysleep(0.2);
							klient.czygracz[bufor[3]] = 0;
							break;
						}
				case S_KICKOFF : {
							 flagawyjscia=0;
							 OczyscMain();
							 PiszNaMainS(7,5,"Zosta³e¶ wyrzucony!");
							 Odswiez();
							 PobierzZnak();
							 break;
						 }
				case S_EXIT : {
							ZamienAnaII(&sx, &sy, bufor);
							 flagawyjscia=0;
							 gettimeofday(&tv, 0);
							 OczyscMain();
						      if (bufor[3] == klient.id) {
						 PiszNaMainS(5, 5, "Gratulacje!");
			 PiszNaMainS(5, 7, "Ukoñczy³e¶ planszê wielko¶ci %dx%d", RozmiarX(1), RozmiarY(1));
			 PiszNaMainS(5, 8, "Wykonuj±c ruchów: %d (najkrótsza ¶cie¿ka:%d)", sx, sy);
			 n = RozmiarX(1)+RozmiarY(1) + ((10*RozmiarX(1))/RozmiarY(1))+
				 ((10*RozmiarY(1))/RozmiarX(1));
			 n -= sx;
			 if (sx == sy)
				 n +=100;
			 n += sy;
			 n -= tv.tv_sec - klient.tv.tv_sec;
			 PiszNaMainS(5, 10, "Twój wynik to: %d", n);
			 PiszNaMainS(5,11,"Zajêty czas: %0.3f sekund", (((tv.tv_sec-klient.tv.tv_sec)*1000000+
					 tv.tv_usec-klient.tv.tv_usec)/(float)1000000));
			 if (sx < sy)
				 PiszNaMainS(7,12, "Eeee... to jest mo¿liwe?");
			 RysujInfo(3);
			 Odswiez();
						      }
						      else {
							      PiszNaMainS(7, 5, "Przegra³e¶!");
					      PiszNaMainS(5, 8, "Wygra³: %s", klient.imionagraczy[bufor[3]]);
					      RysujInfo(3);
					      Odswiez();
						      }
			 while ((n = PobierzZnak())!='q' && (n != 'Q'));
							 break;
						 }
			}
		}
	}
	return 0;
}

int
DajFd(void)
{
	return klient.fd;
}

int
DajRuchy(void)
{
	return klient.ruchy;
}

int
RozpPoj(void)
{
	unsigned char bufor[13];
	int zaz, znak;
char* nazwy[] = {"bardzo ma³y", "ma³y", "¶redni", "du¿y", "bardzo du¿y", "gigantyczny", "nie do przej¶cia"};
	unsigned char typ;
	int flagwyj = 1;
	typ = 1;
	zaz = 1;
	while (flagwyj) {
		OczyscMain();
		PiszNaMainS((zaz==1)?3:5, 5, "start");
		PiszNaMainS((zaz==2)?3:5, 6, "wielko¶æ: %s", nazwy[typ]);
		PiszNaMainS((zaz==3)?3:5, 8, "wyj¶cie");
		Odswiez();
		znak = PobierzZnak();
		switch (znak) {
			case 'w': case 'W': {
						    --zaz;
						    if (zaz == 0) zaz = 3;
						    break;
					    }
			case 's': case 'S': {
						    ++zaz;
						    if (zaz == 4) zaz = 1;
						    break;
					    }
			case '\r': case 'e': case 'E': {
						         switch (zaz) {
								 case 1: {
										 flagwyj = 0;
										 break;
									 }
								 case 2: {
										 typ = (typ + 1)%7;
										 break;
									 }
								 case 3: {
										 return 1;
										 break;
									 }
		  				         }
						       }
		}
	}
	PiszDoSerwera(118, 0, K_ZALOZ, typ, 0);
	if (read(klient.fd2, bufor, 13) != 13)
		return 1;
	if (bufor[2] != S_STARTED)
		return bufor[2];
	return 0;
}

int
RozpMulti(char typ)
{
	unsigned char bufor[13];
	int i, posz, flwyj, maxfdp1, znak, czywpisanoimie;
	fd_set rset, allset;
	char* pomocnik;
char* nazwy[] = {"bardzo ma³y", "ma³y", "¶redni", "du¿y", "bardzo du¿y", "gigantyczny", "nie do przej¶cia"};
	unsigned char typek;
	typek = 1;
	posz = 1;

	flwyj = 1;
	czywpisanoimie = 1;
	FD_ZERO(&rset);
	FD_SET(STDIN_FILENO, &rset);
	FD_SET(klient.fd2, &rset);
	maxfdp1 = (klient.fd2 > STDIN_FILENO) ? (klient.fd2+1) : (STDIN_FILENO+1);

	PiszDoSerwera(118, 0, S_NAME, 0, getenv("LOGNAME")?getenv("LOGNAME"):"player");
	while (flwyj) {
		allset = rset;
		posz = 1;
		OczyscMain();
		PiszNaMainS(5,posz, "Zalogowani gracze:");
		posz++;
		for (i = 0; i < klient.miejsca; ++i) {
			if (klient.czygracz[i] == 1) {
				posz++;
				if (i == klient.id) {
					PiszNaMainS(7, posz, "%s", klient.name);
				}
				else {
					PiszNaMainS(5, posz, "%s", klient.imionagraczy[i]);
				}
			}
			
		}
		posz++;
		PiszNaMainS(4, posz, "----------------------------------------------------------------");
		if (typ) {
			posz++;
		PiszNaMainS(5, posz, "wielko¶æ: %s", nazwy[typek]);
			posz++;
		PiszNaMainS(4, posz, "----------------------------------------------------------------");
		}
		posz++;
		if (typ) {
			PiszNaMainS(5, posz, "n - zmiana imienia, s - start gry, q - zakoñczenie gry");
			posz++;
			PiszNaMainS(5, posz, "w - zmiana wielko¶ci planszy do gry");
			posz++;
		PiszNaMainS(4, posz, "----------------------------------------------------------------");
			for (i = 0; i < klient.miejsca; ++i) {
				if ((klient.czygracz[i] == 1)&&(i != klient.id)) {
					posz++;
				PiszNaMainS(5, posz, "%d - wyrzucenie %s", i+1, klient.imionagraczy[i]);
				}
			}
		}
		else {
			PiszNaMainS(5, posz, "n - zmiana imienia, q - zakoñczenie gry");
		}
		Odswiez();
		
		select(maxfdp1, &allset, NULL, NULL, NULL);
		
		if (FD_ISSET(STDIN_FILENO, &allset)) {
			if (czywpisanoimie) {
			znak = PobierzZnak();
			switch (znak) {
				case '1': case '2': case '3': case '4': case '5': {
					if (klient.czygracz[znak-'1'] == 1) {
						PiszDoSerwera(118, 0, S_KICKOFF, znak-'1', 0);
					}
							break;
										  }
				case 'q': case 'Q': {
					PiszDoSerwera(118, 0, K_LOGOUT, 0, 0);
							    return 1;
							    break;
						    }
				case 's': case 'S': {
							    if (typ)
							    flwyj = 0;
							    break;
						    }
				case 'n': case 'N': {
							    czywpisanoimie = 0;
							   WprTekst("Imie (max 9 znaków):", 9);
							    break;
						    }
				case 'w': case 'W': {
							 typek = (typek + 1)%7;
							 break;
						    }
			}
			}
			else {
				pomocnik = WprTekst("Imie (max 9 znaków):", 9);
				if (pomocnik) {
					czywpisanoimie = 1;
				    RysujInfo(0);
				    PiszDoSerwera(118, 0, S_NAME, 0, pomocnik);
				}
			}
		}
		
		if (FD_ISSET(klient.fd2, &allset)) {
			if (read(klient.fd2, bufor, 13) != 13) 
				return 1;
			switch (bufor[2]) {
				case S_NAME : {
						      if (bufor[3] < klient.miejsca) {
							      klient.czygracz[bufor[3]] = 1;
						      memcpy(klient.imionagraczy[bufor[3]], &bufor[4], 9);
						      if (bufor[3] == klient.id) {
						      memcpy(klient.name, &bufor[4], 9);
						      }
						      }
						      break;
					      }
				case S_STARTED : {
							 flwyj = 0;
							 break;
						 }
				case S_KICKOFF : {
							 OczyscMain();
							 PiszNaMainS(7, 7, "Zosta³e¶ wyrzucony!");
							 Odswiez();
							 PobierzZnak();
							 WprTekst(0, 0);
							 return 1;
						 }
				case K_LOGOUT : {
							if (bufor[3] == klient.id)
								return 1;
							klient.czygracz[bufor[3]] = 0;
						}
			}
		}
	}
	WprTekst(0, 0);
	if (typ) {
	PiszDoSerwera(118, 0, K_ZALOZ, typek, 0);
	if (read(klient.fd2, bufor, 13) != 13)
		return 1;
	if (bufor[2] != S_STARTED)
		return bufor[2];
	}
	return 0;
}

char*
WprTekst(char* opis, int ogr)
{
	static int wpr;
	static char buforeeek[101];
	static int status;
	int znak = 0;
	if (ogr == 0) {
		status = 0;
		return 0;
	}
	if ((ogr < 0) || (ogr > 100)) {
		ogr = 100;
	}
	if (!status) {
	memset(buforeeek, 0, 101);
	wpr = 0;
	}
		OczyscInfo();
		PiszNaInfoS(5,0, opis);
		PiszNaInfo(4,1,2,buforeeek);
		Odswiez();
		znak = PobierzZnak();
		switch (znak) {
			case '\r': { /* zakoñczenie wpisywania */
					   status = 0;
					   return buforeeek;
					   break;
				   }
			case '\b': case 127: case 263: {
							       --wpr;
							       if (wpr < 0) wpr = 0;
							       buforeeek[wpr] = 0;
							       break;
						       }
			default: {
					 if (wpr < ogr) {
					 buforeeek[wpr] = znak;
					 wpr++;
					 }
				 }
			
		}
		OczyscInfo();
		PiszNaInfoS(5,0, opis);
		PiszNaInfo(4,1,2,buforeeek);
		Odswiez();
		status = 1;
		return 0;
}
