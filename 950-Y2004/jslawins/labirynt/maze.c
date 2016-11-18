
#include <stdlib.h>
#include "mazelib.h"

#define	NoSolution	1000000

/* Funkcja `SolveMaze(pt)' próbuje znale¼æ drogê do wyj¶cia 
   z labiryntu z podanego punktu `pt'. Funkcja zwraca TRUE 
   je¶li jest taka droga, a FALSE w przeciwnym wypadku.
   Funkcja korzysta z rekurencji do rozwi±zania podlabiryntów
   powstaj±cych przez zaznaczenie bie¿±cego punktu 
   i przej¶cie o jeden krok dalej niezablokowanym przej¶ciem. */

static bool SolveMaze(pointT pt);

/* !!! */ 

directionT tablica[] = {North, East, South, West};
extern pointT PunktObok(pointT pt, directionT dir); /* jednak siê tutaj przyda */

/* Funkcja `Rysuj(znaczek)' wyrysowuje na ekranie labirynt.
 * Oznaczaj±c znaczkiem punkt startowy
 */

void Rysuj(char znaczek); /* do rysowania wykresu labiryntu */

/* Funkcja `ShortestPathLength(pt)' próbuje znale¼æ d³ugo¶æ najkrótszej
 * ¶cie¿ki prowadz±cej z punktu pt do wyj¶cia
 */

int ShortestPathLength(pointT pt); /* zadanie 2 */

/* Funkcja `NajkrotszaDlugoscSciezki(pt)' rekurencyjnie wyszukuje
 * najkrótsz± d³ugo¶æ ¶cie¿ki
 */

int NajkrotszaDlugoscSciezki(pointT pt); /* zadanie 2 */

/* Obiekt wyniki typu struktury s³u¿±cy do wynajdowania najkrótszej ¶cie¿ki */

static struct {
	int xsize, ysize;
	int** powierzchnia;
} wyniki;

/* Funkcja `FindPath(pt, path[], pathSize)' próbuje znale¼æ najkrótsz± ¶cie¿ke z punktu pt do wyj¶cia - kolejne punkty s± zapisywane w tablicy path (je¿eli ¶cie¿ka jest d³u¿sza ni¿ pathSize - tylko pathSize punktów jest zapisywanych lecz zwracana jest poprawna d³ugo¶æ ¶cie¿ki
 */

#define	MaxPath	100 /* ¶cie¿ki o takiej max d³. bêdziemy szukaæ */
int FindPath(pointT pt, pointT path[], int pathSize);

/* !!! */

string MazeFile = "labirynt.txt";  /* nazwa pliku z labiryntem */

int main() {
	int i, len; 
	pointT path[MaxPath]; /* tablica dla zadania 3 */
	/* zadanie 1 */
  ReadMazeMap(MazeFile);
    printf("Wczytany labirynt:\n\n");
    Rysuj('S');
  if (SolveMaze(GetStartPosition())) {
    printf("Zaznaczone kwadraty pokazuj± drogê do wyj¶cia z labiryntu.\n\n");
    Rysuj('S');
  } else {
    printf("Z podanego punktu brak wyj¶cia z labiryntu.\n\n");
  }
  	/* zadanie 2 */
  len = ShortestPathLength(GetStartPosition());
  if (len != NoSolution) {
	  printf("\nD³ugo¶æ najkrótszej ¶cie¿ki to %d\n\n", len);
  }
  else {
	  printf("Najkrótsza ¶cie¿ka nie istnieje.\n\n");
  }
  	/* zadanie 3 */
  len = FindPath(GetStartPosition(), path, MaxPath);
  if (len==0)
	  printf("Nie ma wyj¶cia z labiryntu.\n\n");
  else {
	  printf("¦cie¿ka prowadz±ca do wyj¶cia:\n");
	  for (i=0; i<((MaxPath < len)?MaxPath:len); ++i)
		  printf("->(%d,%d) ", path[i].x, path[i].y);
	  if (MaxPath < len)
		  printf(" ...");
	  printf("\n\n");
  }
  return EXIT_SUCCESS;
}

/* !!! */ /* Implementacje funkcji do zadañ */ /* !!! */

bool SolveMaze(pointT pt) {
	int i;
	if (OutsideMaze(pt))
		return TRUE;
	if (IsMarked(pt))
		return FALSE;
	MarkSquare(pt);

	for (i = 0; i < 4; ++i) {
		if (!WallExists(pt, tablica[i]))
			if (SolveMaze(PunktObok(pt, tablica[i])))
				return TRUE;
	}
	
	UnmarkSquare(pt);
  return FALSE;
}

/* !!! */

int
ShortestPathLength(pointT pt)
{
	int min, i, j;
	pointT iterator; /* dla znalezienia rozmiaru labiryntu */
  	ReadMazeMap(MazeFile);

	if (wyniki.powierzchnia != NULL) { /* dealokowanie poprzedniej struktury*/
		for (i = 0; i < wyniki.xsize; ++i) {
			free(wyniki.powierzchnia[i]);
		}
		free(wyniki.powierzchnia);
	}
	
	iterator.x = 0;
	iterator.y = 0;
	
	while (TRUE) { /* znalezienie rozmiaru x */
		if (OutsideMaze(iterator)) {
			break;
		}
		iterator.x++;
	}
	wyniki.xsize = iterator.x;
	iterator.x = 0;
	
	while (TRUE) { /* znalezienie rozmiaru y */
		if (OutsideMaze(iterator)) {
			break;
		}
		iterator.y++;
	}

	wyniki.ysize = iterator.y;

	/* alokowanie struktury wyliczaj±cej wynik */
	wyniki.powierzchnia = calloc(1, wyniki.xsize * sizeof(int));
	for (i = 0; i < wyniki.xsize; ++i) {
		wyniki.powierzchnia[i] = calloc(1, wyniki.ysize * sizeof(int));
		for (j = 0; j < wyniki.ysize; ++j) { /* by pó¼niej ³atwo update'owaæ strukturê */
			wyniki.powierzchnia[i][j] = NoSolution;
		}
	}

	wyniki.powierzchnia[GetStartPosition().x][GetStartPosition().y] = 0;

	min = NajkrotszaDlugoscSciezki(pt);
	if (min) {
		return min+1; /* zaczynamy na wyj¶ciu - ¶cie¿ka ma d³. 1 */
	}
	return NoSolution;
}

int
NajkrotszaDlugoscSciezki(pointT pt)
{
	int i, k, flaga;
	pointT iterator;

	flaga = 0; /* oznacza brak zmian w strukturze */

	/* update struktury */
	iterator.x = 0;
	iterator.y = 0;
while (TRUE) { /* iteracja po y */
  if (OutsideMaze(iterator)) {
    break;
  }
  while (TRUE) { /* iteracja po x */
    if (OutsideMaze(iterator)) {
      iterator.x = 0;
      break;
    }
    for (i = 0; i < 4; ++i) {
      if (!WallExists(iterator, tablica[i])) {
	      if (OutsideMaze(PunktObok(iterator, tablica[i]))) {
		      continue; /* omijamy ten punkt */
	      }
	      iterator.x--; /* by rozpatrywaæ bie¿±cy punkt */
	      if (WallExists(iterator, East)) {
		      iterator.x++; /* powrót do wspó³rzêdnych */
		      continue; /* no i ominiêcie tego punktu */
	      }
	      iterator.x++; /* powrót do normalnych wspó³rzêdnych */
	      if (OutsideMaze(iterator)) {
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
	  while (TRUE) {
	    if (OutsideMaze(iterator)) {
	      break;
	    }
	    flaga = (wyniki.powierzchnia[iterator.x][iterator.y] < flaga)
			? wyniki.powierzchnia[iterator.x][iterator.y] : flaga;
	    iterator = PunktObok(iterator, tablica[i]);
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
FindPath(pointT pt, pointT path[], int pathSize)
{
	int i, len, ilosc;
	pointT iterator;
  len = ShortestPathLength(GetStartPosition());
  if (len != NoSolution) {
	  ilosc = len; /* ilosc wskazuje na ilo¶æ punktów w ¶cie¿ce */
	iterator.x = 0;
	iterator.y = 0;
	for (i = 0; i < 4; ++i) { /* szukanie wyj¶cia */
		if (i==0) {iterator.x=0;iterator.y=wyniki.ysize-1;}
		if (i==1) {iterator.x=0;iterator.y=0;}
		if (i==2) {iterator.x=wyniki.xsize-1;iterator.y=0;}
		if (i==3) {iterator.x=wyniki.xsize-1;iterator.y=wyniki.ysize-1;}
	  while (TRUE) {
	    if (OutsideMaze(iterator)) {
	      break;
	    }
	    if (wyniki.powierzchnia[iterator.x][iterator.y] == len-1) { /* znaleziono wyj¶cie */
		    i = 4; /* wyj¶cie z pêtli for */
		    break; /* wyj¶cie z pêtli while */
	    }
	    iterator = PunktObok(iterator, tablica[i]);
	  }
	} /* koniec szukania wyj¶cia */

	/* iterator wskazuje teraz na wyj¶cie - trzeba cofaæ siê wzd³u¿ ¶cie¿ki i je¿eli pozwala na to wielko¶æ tablicy path - wpisywaæ kolejne pola do tej tablicy */
	do {
		if (ilosc < pathSize) {
			path[ilosc] = iterator;
		}
		for (i = 0; i < 4; ++i) {
			if (!OutsideMaze(PunktObok(iterator, tablica[i]))) {
		  if ((wyniki.powierzchnia[PunktObok(iterator, tablica[i]).x]
			  [PunktObok(iterator, tablica[i]).y]) == ilosc - 1) {
			  iterator = PunktObok(iterator, tablica[i]);
			  break;
		  }
			}
		}
		ilosc--; 
	} while (ilosc >= 0);

  }
  else {
	  return 0;
  }
  return len;
}

void
Rysuj(char znaczek)
{
	pointT iterator;
    iterator.x = 0;
    iterator.y = 0;
    while (TRUE) { /* po y'ach iteracja */
	    if (OutsideMaze(iterator)) {
		    break;
	    }
	    while (TRUE) { /* po x'ach iteracja */
		    if (OutsideMaze(iterator)) {
			    printf("\n");
			    iterator.x = 0;
			    break;
		    }
		    iterator.x--;
		    if (WallExists(iterator, East)) {
			    printf("#");
			    iterator.x++;
			    iterator.x++;
			    continue;
		    }
		    iterator.x++;
		    if ((iterator.x == GetStartPosition().x) && (iterator.y == GetStartPosition().y)) {
			    putchar(znaczek);
		    }
		    else if (IsMarked(iterator) == TRUE) {
			    printf("x");
		    }
		    else {
			    printf(" ");
		    }
		    iterator.x++;
	    }
	    iterator.y++;
    }
}
/* !!! */
