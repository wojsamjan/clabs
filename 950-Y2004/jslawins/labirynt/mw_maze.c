/* Jakub S³awiñski (Slaughter House Entertainment Group)
 * plik implementuj±cy funkcje rozwi±zuj±ce problemy labiryntowe
 * mw_maze.c
 */

#include "mw_lib.h"
#include "mw_maze.h"
#include "grafika.h"
#include "mw_klie.h"
#include <stdlib.h>

#define	NoSolution	1000000

kierunkiT tablica[] = {North, East, South, West};

int
RozwiazLabirynt(punktT pt) {
	int i;
	if (NaZewnatrz(pt, 0))
		return 1;
	if (JestZaznaczone(pt, 0))
		return 0;
	Zaznacz(pt, 0);

	for (i = 0; i < 4; ++i) {
		if (!JestMur(PunktObok(pt, tablica[i]), 0))
			if (RozwiazLabirynt(PunktObok(pt, tablica[i])))
				return 1;
	}
	
	Odznacz(pt);
  return 0;
}



int
NajkrotszaDlugoscSciezki(punktT pt)
{
	int i, k, flaga;
	punktT iterator;

	flaga = 0; /* oznacza brak zmian w strukturze */

	/* update struktury */
	iterator.x = 0;
	iterator.y = 0;
while (1) { /* iteracja po y */
  if (NaZewnatrz(iterator, 0)==1) {
    break;
  }
  while (1) { /* iteracja po x */
    if (NaZewnatrz(iterator, 0)==1) {
      iterator.x = 0;
      break;
    }
    for (i = 0; i < 4; ++i) {
      if (!JestMur(PunktObok(iterator, tablica[i]), 0)) {
	      if (NaZewnatrz(PunktObok(iterator, tablica[i]), 0)) {
		      continue; /* omijamy ten punkt */
	      }
	      if (JestMur(iterator, 0)) {
		      continue; /* ominiêcie tego punktu */
	      }
	      if (NaZewnatrz(iterator, 0)==1) {
		      continue; /* omijamy ten punkt */
	      }
        k = wyniki.powierzchnia[PunktObok(iterator, tablica[i]).x]
			[PunktObok(iterator, tablica[i]).y] + 1;
	if (k < wyniki.powierzchnia[iterator.x][iterator.y]) {
		wyniki.powierzchnia[iterator.x][iterator.y] = k;
		flaga = 1;
	}
      }
      else {
      }
    }
    iterator.x++;
  }
  iterator.y++;
} /* koniec update'u struktury */

	if (flaga) { /* je¿eli by³ update struktury */
		return NajkrotszaDlugoscSciezki(pt);
	}

	/* je¿eli nie by³o update'u struktury -> odleg³o¶ci od startu s± ju¿ dobre, wiêc trzeba wyszukaæ teraz miejsca, sk±d jest wyj¶cie, a jednocze¶nie jest tam najmniejsza odleg³o¶æ od pocz±tku - flaga bêdzie trzymaæ najmniejsz± odleg³o¶æ */
	iterator.x = 0;
	iterator.y = 0;
	flaga = NoSolution;
	for (i = 0; i < 4; ++i) {
		if (i==0) {iterator.x=0;iterator.y=wyniki.ysize-1;}
		if (i==1) {iterator.x=0;iterator.y=0;}
		if (i==2) {iterator.x=wyniki.xsize-1;iterator.y=0;}
		if (i==3) {iterator.x=wyniki.xsize-1;iterator.y=wyniki.ysize-1;}
	  while (1) {
	    if (NaZewnatrz(iterator, 0)) {
	      break;
	    }
	    flaga = (wyniki.powierzchnia[iterator.x][iterator.y] < flaga)
			? wyniki.powierzchnia[iterator.x][iterator.y] : flaga;
	    iterator = PunktObok(iterator, tablica[i]);
	  }
	}
	for (i = 1; i < wyniki.xsize-1; ++i) {
		iterator.x = i;
		for (k = 1; k < wyniki.ysize-1; ++k) {
			iterator.y = k;
			if (NaZewnatrz(iterator, 0) == 2)
	    flaga = (wyniki.powierzchnia[iterator.x][iterator.y] < flaga)
			? wyniki.powierzchnia[iterator.x][iterator.y] : flaga;
		}
	}
	if (flaga != NoSolution) {
		return flaga;
	}
	else {
		return 0;
	}
}

int
NajkrotszaSciezka(punktT pt)
{
	int i, j, min;

	if (wyniki.powierzchnia != NULL) { /* dealokowanie poprzedniej struktury*/
		for (i = 0; i < wyniki.xsize; ++i) {
			free(wyniki.powierzchnia[i]);
		}
		free(wyniki.powierzchnia);
	}
	
	wyniki.xsize = RozmiarX(0);
	wyniki.ysize = RozmiarY(0);

	/* alokowanie struktury wyliczaj±cej wynik */
	wyniki.powierzchnia = calloc(1, wyniki.xsize * sizeof(int));
	for (i = 0; i < wyniki.xsize; ++i) {
		wyniki.powierzchnia[i] = calloc(1, wyniki.ysize * sizeof(int));
		for (j = 0; j < wyniki.ysize; ++j) { /* by pó¼niej ³atwo update'owaæ strukturê */
			wyniki.powierzchnia[i][j] = NoSolution;
		}
	}

	wyniki.powierzchnia[PobierzStart().x][PobierzStart().y] = 0;

	min = NajkrotszaDlugoscSciezki(pt);
	if (min) {
		return min+1;
	}
	return NoSolution;
}

punktT*
ZnajdzSciezke(punktT pt)
{
	int i, k, len, ilosc;
	punktT iterator;
	punktT tmpiter;
	punktT* path = NULL;
  len = NajkrotszaSciezka(PobierzStart());
  if (len != NoSolution) {
	  ilosc = len; /* ilosc wskazuje na ilo¶æ punktów w ¶cie¿ce */
	  path = calloc(len, sizeof(punktT));
	iterator.x = 0;
	iterator.y = 0;
	for (i = 0; i < 4; ++i) { /* szukanie wyj¶cia */
		if (i==0) {iterator.x=0;iterator.y=wyniki.ysize-1;}
		if (i==1) {iterator.x=0;iterator.y=0;}
		if (i==2) {iterator.x=wyniki.xsize-1;iterator.y=0;}
		if (i==3) {iterator.x=wyniki.xsize-1;iterator.y=wyniki.ysize-1;}
	  while (1) {
	    if (NaZewnatrz(iterator, 0)) {
	      break;
	    }
	    if (wyniki.powierzchnia[iterator.x][iterator.y] == len-1) { /* znaleziono wyj¶cie */
		    i = 4; /* wyj¶cie z pêtli for */
		    break; /* wyj¶cie z pêtli while */
	    }
	    iterator = PunktObok(iterator, tablica[i]);
	  }
	} /* koniec szukania wyj¶cia na brzegach*/
	tmpiter = iterator;
	for (i = 1; i < RozmiarX(0)-1; ++i) {
		iterator.x = i;
		for (k = 1; k < RozmiarY(0)-1; ++k) {
			iterator.y = k;
			if (NaZewnatrz(iterator, 0) == 2)
	    if (wyniki.powierzchnia[iterator.x][iterator.y] == len - 1) {
		    i = RozmiarX(0);
		    break;
	    }
		}
	}
	    if (wyniki.powierzchnia[iterator.x][iterator.y] != len - 1) {
		    iterator = tmpiter;
	    }

	/* iterator wskazuje teraz na wyj¶cie - trzeba cofaæ siê wzd³u¿ ¶cie¿ki i wpisywaæ kolejne pola do tablicy */
	do {
		path[ilosc-1] = iterator;
		for (i = 0; i < 4; ++i) {
			if (!NaZewnatrz(PunktObok(iterator, tablica[i]), 0)) {
		  if ((wyniki.powierzchnia[PunktObok(iterator, tablica[i]).x]
			  [PunktObok(iterator, tablica[i]).y]) == ilosc - 2) {
			  iterator = PunktObok(iterator, tablica[i]);
			  break;
		  }
			}
		}
		ilosc--; 
	} while (ilosc > 0);

  }
  else {
	  return 0;
  }
  return path;
}

void
RysujLabirynt(int xoff, int yoff, char typ)
{
	punktT iterator;
	int xpos, ypos;
	OczyscMain();
	xpos = ypos = 0;
	iterator.x = xoff;
	iterator.y = yoff;
	while (1) { /* iteracja po y'ach */
		if ( (NaZewnatrz(iterator, typ)==1) || (ypos == (MaxEkranY()-5)) ) {
			break;
		}
		while (1) { /* iteracja po x'ach */
		if ( (NaZewnatrz(iterator, typ)==1) || (xpos == MaxEkranX()-1) ) {
				iterator.x = xoff;
				++ypos;
				xpos = 0;
				break;
			}
			if (JestMur(iterator, typ)) {
				PiszNaMain(5, xpos, ypos, "#");
			}
			else if ( (iterator.x == PobierzStart().x) &&
					(iterator.y == PobierzStart().y) ) {
				if (typ==0)
					PiszNaMain(4, xpos, ypos, "S");
				else
					PiszNaMain(4, xpos, ypos, ".");
			}
			else if (JestZaznaczone(iterator, typ) == 1) {
				if (typ==0)
					PiszNaMain(4, xpos, ypos, "x");
				else
					PiszNaMain(4, xpos, ypos, ".");
			}
			else if (NaZewnatrz(iterator, typ)) {
				PiszNaMain(4, xpos, ypos, "E");
			}
			else {
				PiszNaMain(6, xpos, ypos, " ");
			}
			++xpos;
			iterator.x++;
		}
		iterator.y++;
	}
	Odswiez();
}

void
RysujSciezke(int yoff, punktT path[], int wielkosc)
{
	int i, ilosc;
	OczyscMain();
	i = yoff;
	ilosc = 0;
	while (ilosc < (MaxEkranY()-5)) {
		if (i >= wielkosc)
			break;
		PiszNaMainS(5,ilosc, "%d) (%d, %d)", i+1, path[i].x, path[i].y);
		++i;
		++ilosc;
	}
	Odswiez();
}

void
RysujInfo(int tryb)
{
	OczyscInfo();
	if (tryb == 0) {
	PiszNaInfoS(8,0,"Maze Walker - v0.2b");
	PiszNaInfoS(4,2,"Slaughter House Entertainment Group");
	PiszNaInfoS(7,3,"Copyleft 2003");
	}
	if (tryb == 1) {
	PiszNaInfo(5,0,0,"1 - Graficzne przedstawienie rozwi±zania labiryntu");
	PiszNaInfo(5,0,1,"D³ugo¶æ Najkrótszej ¶cie¿ki:");
	PiszNaInfo(4,29,1,"%d", NajkrotszaSciezka(PobierzStart()));
	PiszNaInfo(5,0,2,"2 - Wy¶wietlenie wspó³rzêdnych najkrótszej ¶cie¿ki");
	PiszNaInfo(7,0,3,"q - Wyj¶cie");
	}
	if (tryb == 2) {
	PiszNaInfo(5, 1, 2, "Ilo¶æ wykonanych ruchów: %d", (DajRuchy() >= 0)? DajRuchy():0);
	PiszNaInfo(7,0,3,"q - Wyj¶cie");
	}
	if (tryb == 3) {
	PiszNaInfoS(7, 2, "q - wyj¶cie");
	}
	Odswiez();
}
