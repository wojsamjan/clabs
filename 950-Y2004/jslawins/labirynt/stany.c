/* Jakub S³awiñski (Slaughter House Entertainment Group)
 * plik nag³ówkowy do obs³ugi ró¿nych stanów programu
 * stany.h
 */

#include "mw_lib.h"
#include "mw_maze.h"
#include "mw_serw.h"
#include "mw_klie.h"
#include "stany.h"
#include "grafika.h"
#include "myfunkc.h"
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

void
Intro(void)
{
	int i, ilosc;
	int* tablica;
	int test, num;
	char* napisy[] = {"Slaughter House Entertainment Group", "presents"};
	fd_set rset;
	struct timeval tv;
	
	tablica = calloc(MaxEkranX(), sizeof(int));
	ilosc = 2 * MaxEkranX() * (MaxEkranY()-5);
	
	OczyscMain();
	for (i = 0; i < ilosc; ++i) { /* troszkê namieszane, ale spe³nia swoj± funkcjê */
		test = 1; 	      /* losowe literki spadaj± w dó³ ekranu, a wyjawia siê z nich */
		while (test) {	      /* okre¶lony napis */
			num = myrand(0, MaxEkranX()-1);
			if (tablica[num] < 2 * (MaxEkranY()-5)) {
				if (tablica[num] < (MaxEkranY()-5)) {
				PiszNaMain(5, num, tablica[num]%(MaxEkranY()-5), "%c", myrand('A', 'z'));
				}
				else {
					if ((tablica[num]%(MaxEkranY()-5))==5) {
				if ((num >= ((MaxEkranX())/2)-17) && (num - ((MaxEkranX()/2)-17)< 35)) {
		PiszNaMain(5, num, tablica[num]%(MaxEkranY()-5), "%c", napisy[0][num - (MaxEkranX()/2)+17]);
				}
				else {
					PiszNaMain(5, num, tablica[num]%(MaxEkranY()-5), " ");
				}
					}
					else if ((tablica[num]%(MaxEkranY()-5))==10) {
				if ((num >= ((MaxEkranX())/2)-4) && (num - ((MaxEkranX()/2)-4)< 8)) {
		PiszNaMain(5, num, tablica[num]%(MaxEkranY()-5), "%c", napisy[1][num - (MaxEkranX()/2)+4]);
				}
				else {
					PiszNaMain(5, num, tablica[num]%(MaxEkranY()-5), " ");
				}
					}
					else {
						PiszNaMain(5, num, tablica[num]%(MaxEkranY()-5), " ");
					}
				}
				++tablica[num];
				Odswiez();
				test = 0;
			}
		}
		if ((i%100) == 0) {
			FD_ZERO(&rset);
			FD_SET(STDIN_FILENO, &rset);
			tv.tv_sec = 0;
			tv.tv_usec = 10000;
			select(STDIN_FILENO+1, &rset, NULL, NULL, &tv);
			if (FD_ISSET(STDIN_FILENO, &rset)) {
				return; /* wy³±czenie intra */
			}
			mysleep(0.01);
		}
	}
	mysleep(0.5);
	PiszNaMainS(7, 15, "MAZE WALKER");
	Odswiez();
	flash();
	flash();
	flash(); /* dla zwiêkszenia efektu grozy ;P */
	mysleep(2);
	OczyscMain();
	Odswiez();
}

void
Menu(void)
{
	int checked, znak;
	checked = 1;
	flushinp(); /* zignorowanie wcze¶niej naci¶nietych klawiszy */
	while (1) { /* wy¶wietlanie menu */
		OczyscMain();
		PiszNaMainS(5, 4, "MENU");
		PiszNaMainS((checked==1)?3:5, 6, "standardowy labirynt");
		PiszNaMainS((checked==2)?3:5, 7, "gra jednoosobowa");
		PiszNaMainS((checked==3)?3:5, 8, "gra wieloosobowa");
		PiszNaMainS((checked==4)?3:5, 9, "wyj¶cie");

		PiszNaMainS(7, 12, "Klawiszologia:");
		PiszNaMainS(7, 13, "a, w, s, d - strza³ki");
		PiszNaMainS(7, 14, "q - zazwyczaj koñczenie");
		PiszNaMainS(7, 15, "e, enter - zatwierdzanie");
		PiszNaMainS(7, 16, "By co¶ zmieniæ/u¿yc - zatwierd¼ to");
		PiszNaMainS(8, 18, "Zanim przeklniesz - miej na uwadze wersjê");
		PiszNaMainS(6, 19, "No i jak jaki¶ problem/bug/request -> jeremian@poczta.fm");
		RysujInfo(0);
		Odswiez();
		while (1){ /* wybór z menu */
			znak = PobierzZnak();
			if (znak == 's') {
				if (checked < 4) {
					++checked;
				}
				else {
					checked = 1;
				}
				break;
			}
			if (znak == 'w') {
				if (checked > 1) {
					--checked;
				}
				else {
					checked = 4;
				}
				break;
			}
			if ((znak == '\r') || (znak == 'e') || (znak == 'E')) {
				switch (checked) {
					case 1: {
							StdMaze();
							break;
						}
					case 2: {
							PojGra();
							break;
						}
					case 3: {
							MultiGra();
							break;
						}
					case 4: {
							return;
							break;
						}
				}
				break;
			}
		}
	}
}

void
StdMaze(void)
{
	int checked, znak;
	checked = 1;
lStdM:	while (1) { /* wy¶wietlanie menu standard maze */
		OczyscMain();
		PiszNaMainS(5, 4, "STANDARDOWY LABIRYNT");
		PiszNaMainS((checked==1)?3:5, 6, "wygeneruj");
		PiszNaMainS((checked==2)?3:5, 7, "wczytaj z pliku");
		PiszNaMainS((checked==3)?3:5, 8, "wyj¶cie");
		RysujInfo(0);
		Odswiez();
		while (1){ /* wybór z menu */
			znak = PobierzZnak();
			if (znak == 's') {
				if (checked < 3) {
					++checked;
				}
				else {
					checked = 1;
				}
				break;
			}
			if (znak == 'w') {
				if (checked > 1) {
					--checked;
				}
				else {
					checked = 3;
				}
				break;
			}
			if ((znak == '\r') || (znak == 'e') || (znak == 'E')) {
				switch (checked) {
					case 1: { /* wygeneruj */
		GenerujLabirynt(myrand(5,65),myrand(5,65));
		if (RozwiazLabirynt(PobierzStart())) {
			RysujInfo(1);
			WyswMaze();
		}
		else {
		OczyscMain();
		PiszNaMainS(7, 5, "B³±d w czasie generowania labiryntu!");
		PobierzZnak();
		}
							goto lStdM;
							break;
						}
					case 2: { /* wczytaj z pliku */
							WczytMaze();
							goto lStdM;
							break;
						}
					case 3: { /* wyj¶cie */
							return;
							break;
						}
				}
			}
		}
	}

}

void
WczytMaze(void)
{
	struct dirent **namelist;
	int i, n, znak, zaz, flag, pom;
	struct stat buf;
	n = zaz = flag = 0;
	pom = zaz - MaxEkranY() + 6;
	while (1) {
		if (!flag) {
			if (n) {
				for (i = 0; i < n; ++i) {
					free(namelist[i]);
				}
				free(namelist);
			}
	n = scandir(".", &namelist, 0, alphasort);
	if (n < 0) {
		PiszNaMainS(7,5,"Nie uda³o siê odczytaæ katalogu!");
		return;
	}
			flag = 1;
		}
	OczyscMain();
	if (pom < 0) pom = 0;
	for (i = 0; i < MaxEkranY()-5; ++i) {
	PiszNaMainS((zaz==(i+pom))?3:5, i, "%s", namelist[i+pom]->d_name);
		if ((i+pom) == (n-1)) break;
	}
	Odswiez();
		znak = PobierzZnak();
		switch (znak) {
			case 'w': {
					     if (zaz)
						     --zaz;
					     if (zaz < pom)
						     pom = zaz;
					     break;
				     }
			case 's': {
					       if (zaz<n-1)
					       ++zaz;
					       if (zaz > pom + MaxEkranY() - 6)
						       pom = zaz - MaxEkranY() +6;
					     break;
				     }
			case '\r': case 'e': case 'E': {
					   pom = 0;
				   if (chdir(namelist[zaz]->d_name)==0) {
					   pom = 2;
					   }
				  if (!pom) {
		  stat(namelist[zaz]->d_name, &buf);
		  if (S_ISREG(buf.st_mode)) {
				  pom = 1; /* jest to plik */
	if (CzytajLabirynt(namelist[zaz]->d_name) == 0) {
		if (RozwiazLabirynt(PobierzStart())) {
			RysujInfo(1);
			WyswMaze();
		}
		else {
			OczyscMain();
			PiszNaMainS(7, 5, "Wczytany labirynt nie ma wyj¶cia!!!");
			PobierzZnak();
		}
	}
		  else {
			  OczyscMain();
			  PiszNaMainS(7, 5, "Nie da siê odczytaæ podanego pliku!");
			  PobierzZnak();
		  }
			  }
		  else {
			  OczyscMain();
			  PiszNaMainS(7, 5, "To nie jest zwyk³y plik!");
			  PobierzZnak();
		  }
				  }
					   zaz = 0;
					   flag = 0;
					   if (pom == 1) {
						   return;
					   }
					   pom = 0;
					     break;
				     }
			default: {
					 return;
					 break;
				 }
		}
	}
	
}

void
WyswMaze()
{
	int znak;
	int xpos, ypos;
	int yoff, tryb, len;
	punktT* path;
	xpos = (PobierzStart().x - (MaxEkranX()/2));
	if (xpos < 0)
		xpos = 0;
	if ((RozmiarX(0) - MaxEkranX()) > 0)
		if (xpos > (RozmiarX(0) - MaxEkranX()))
			xpos = RozmiarX(0) - MaxEkranX();
	ypos = (PobierzStart().y - ((MaxEkranY()-5)/2));
	if (ypos < 0)
		ypos = 0;
	if ((RozmiarY(0) - MaxEkranY() + 5) > 0)
		if (ypos > (RozmiarY(0) - MaxEkranY() + 5))
			ypos = RozmiarY(0) - MaxEkranY() +5;
	yoff = 0;
	tryb = 0;
	len = NajkrotszaSciezka(PobierzStart());
	path = ZnajdzSciezke(PobierzStart());
	while (1) {
		if (tryb) {
		  RysujSciezke(yoff, path, len);
		}
		else {
			RysujLabirynt(xpos, ypos, 0);
		}
		znak = PobierzZnak();
	switch (znak) {
		case 'w': {
				     if (!tryb) {
				     	if (ypos > 0) {
					     --ypos;
					}
				     }
				     else {
					     if (yoff > 0) {
						     --yoff;
					     }
				     }
				     break;
			     }
		case 's': {
				     if (!tryb) {
				    if (ypos < (RozmiarY(0) - MaxEkranY() + 5)) {
					     ++ypos;
				    }
				     }
				    else {
					  if (yoff < (len - MaxEkranY() + 5)) {
						  ++yoff;
					  }
				    }
				     break;
			     }
		case 'a': {
				       if (!tryb)
				     if (xpos > 0)
					     --xpos;
				     break;
			     }
		case 'd': {
					if (!tryb)
				     if (xpos < (RozmiarX(0) - MaxEkranX() + 1))
					     ++xpos;
				     break;
			     }
		case '1': case '!': {
				       tryb = 0;
				     break;
			     }
		case '2': case '@': {
				       tryb = 1;
				     break;
			     }
		case 'q': case 'Q': {
				 return;
				 break;
			 }
	}
	}
	  if (path) {
		  free(path);
	  }
}

void
PojGra(void)
{
	int h;
	pthread_t pid;
	Postaw('l', 1, 0, 0);
	if (pthread_create(&pid, NULL, &Przetwarzaj, NULL)) {
		return;
	}
	OczyscMain();
	if ((h = KlientInicjuj('l', 0, 0)) == 0) {
		PiszNaMainS(5, 7, "Po³±czono...");
		Odswiez();
	}
	else {
		PiszNaMainS(7, 7, "Nie uda³o siê rozpocz±æ gry...");
		Odswiez();
		PobierzZnak();
		return;
	}
	if (RozpPoj())
		return;
	if ((h = Dzialaj())) {
		OczyscMain();
		PiszNaMainS(7, 7, "Wyst±pi³ fatalny b³±d...(%d)", h);
		Odswiez();
		PobierzZnak();
	}
}

void
MultiGra(void)
{
	int checked, znak;
	int h;
	char host[101], port[101];
	pthread_t pid;
	checked = 1;
	while (1) { /* wy¶wietlanie menu */
		OczyscMain();
		PiszNaMainS(5, 4, "Gra wieloosobowa");
		PiszNaMainS((checked==1)?3:5, 8, "do³±cz do gry");
		PiszNaMainS((checked==2)?3:5, 9, "za³ó¿ grê");
		PiszNaMainS((checked==3)?3:5, 10, "wyj¶cie");
		RysujInfo(0);
		Odswiez();
		znak = PobierzZnak();
		switch (znak) {
			case 'w': case 'W': {
						    --checked;
						    if (checked==0) checked = 3;
						    break;
					    }
			case 's': case 'S': {
						    ++checked;
						    if (checked==4) checked = 1;
						    break;
					    }
			case '\r': case 'e': case 'E':{
					   switch (checked) {
						   case 1: {
			   if (HostPort("Opisz komputer, do którego siê ³±czysz.", "Po³±cz", host, port))
					   break;
					if ((h = KlientInicjuj('n', host, port)) == 0) {
							PiszNaMainS(5, 7, "Po³±czono...");
							Odswiez();
							}
							else {
						PiszNaMainS(7, 7, "Nie uda³o siê do³±czyæ do gry...(%d)", h);
							Odswiez();
							PobierzZnak();
							return;
							}
							if (RozpMulti(0))
								break;
							if ((h = Dzialaj())) {
							OczyscMain();
							PiszNaMainS(7, 7, "Wyst±pi³ fatalny b³±d...(%d)", h);
							Odswiez();
							PobierzZnak();
							}

								   
								   break;
							   }
						   case 2: {
			   if (HostPort("Opisz komputer hostuj±cy grê (Twój)", "Za³ó¿", host, port))
					   break;
							if (Postaw('n', 5, host, port)) {
								OczyscMain();
							PiszNaMainS(7, 7, "Nie uda³o siê postawiæ serwera...");
							Odswiez();
							PobierzZnak();
							return;
							}
							if (pthread_create(&pid, NULL, &Przetwarzaj, NULL)) {
							return;
								}
							OczyscMain();
						if ((h = KlientInicjuj('l', 0, 0)) == 0) {
							PiszNaMainS(5, 7, "Po³±czono...");
							Odswiez();
							}
							else {
						PiszNaMainS(7, 7, "Nie uda³o siê do³±czyæ do gry...(%d)", h);
							Odswiez();
							PobierzZnak();
							return;
							}
							if (RozpMulti(1))
								break;
							if ((h = Dzialaj())) {
							OczyscMain();
							PiszNaMainS(7, 7, "Wyst±pi³ fatalny b³±d...(%d)", h);
							Odswiez();
							PobierzZnak();
							}

							   break;
							   }
						   case 3: {
								   return;
								   break;
							   }
					   }
						    break;
					    }
		}
	}
}

int
HostPort(char* opis, char* men1, char* host, char* port)
{
	int zaz = 1;
	int flagwyj = 1;
	int znak;
	char* pomocnik;
	memset(host, 0, 101);
	memset(port, 0, 101);
	gethostname(host, 100);
	strcpy(port, "50128");
	while (flagwyj) {
		OczyscMain();
		PiszNaMainS(6, 3, opis);
		PiszNaMainS((zaz==1)?3:5, 5, men1);
		PiszNaMainS((zaz==2)?3:5, 7, "Host: %s", host);
		PiszNaMainS((zaz==3)?3:5, 8, "Port: %s", port);
		PiszNaMainS((zaz==4)?3:5, 10, "wyj¶cie");
		Odswiez();
		znak = PobierzZnak();
		switch(znak) {
			case 'w': case 'W': {
					  --zaz;
					  if (zaz == 0) zaz = 4;
					  break;
				  }
			case 's': case 'S': {
					  ++zaz;
					  if (zaz == 5) zaz = 1;
					  break;
				  }
			case '\r': case 'e': case 'E': {
							       switch (zaz) {
								       case 1: {
										       flagwyj = 0;
										       break;
									       }
								       case 2: {
						host[0] = 0;
						while (host[0] == 0) {
							pomocnik = WprTekst("Host:", 100);
							if (pomocnik)
							strncpy(host, pomocnik, 101);
						}
						RysujInfo(0);
						break;
									       }
								       case 3: {
						port[0] = 0;
						while (port[0] == 0) {
							pomocnik = WprTekst("Port:", 10);
							if (pomocnik)
							strncpy(port, pomocnik, 101);
						}
						RysujInfo(0);
						break;
									       }
								       case 4: {
										       return 1;
										       break;
									       }
							       }
						       }
		}
	}
	return 0;
}
