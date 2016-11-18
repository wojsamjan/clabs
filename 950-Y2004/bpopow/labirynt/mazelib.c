/*Moje funkcje*/
#include <stdio.h>
#include <stdlib.h>
#include "mazelib.h"
#include "random.h"
#include <ncurses/curses.h>

/*F-a przyporzadkowuje punktowi, na ktory wskazuje wskaznik p, nowe
wspolrzedne a i b.
Poza tym rysuje ludzika w nowym miejscu*/
void Daj(int a, int b){
  p->x = a;
  p->y = b;
  lab[b][a] = '@';
}

/*Pomocnicza f-a, ktora po prostu wypisuje mna ekran aktualne
wspolrzedne danego punktu.*/
void PiszPunkt(TPoint punkt){
  printw("X = %d  Y = %d\n",punkt.x, punkt.y);
}

/*F-a, ktora rysuje labirynt. Czyli tablice dwuwymiarowa lab.*/
void RysujLab(int **labirynt){
  int i,j;
  system("usleep 150000");
  erase();
  for(i = 0; i<=LabX; i++){
    for(j = 0; j<=LabY; j++){
      (lab[i][j] == '#') ? color_set(1,0) : color_set(2,0);
      printw("%c",labirynt[i][j]);
    }
    printw("\n");
  }
 
  printw("\n");
  color_set(3,0);
  refresh();
}


/*F-a sprawdza, czy w danym punkcie jest sciana.
Jesli tak, to zwraca 1.*/
static bool CzySciana(TPoint punkt){
  if(lab[punkt.y][punkt.x] == '#') return TRUE;
  else return FALSE;
}

/*F-a sprawdza, czy w danym punkcie jest X.
Jesli tak, to zwraca 1.*/
static bool CzyZaznaczony(TPoint punkt){
  if(lab[punkt.y][punkt.x] == 'X') return TRUE;
  else return FALSE;
}

/*Jesli punkt jest pusty, to f-a go zaznacza.*/
static void Zaznacz(TPoint punkt){
  int temp = lab[punkt.y][punkt.x];

  if(temp == ' ') lab[punkt.y][punkt.x] = 'X';
}

/*Jesli w danym p-cie jest X, to f-a go wymazuje.*/
static void Odznacz(TPoint punkt){
  int temp = lab[punkt.y][punkt.x];

  if(temp == 'X') lab[punkt.y][punkt.x] = ' ';
}

/*Jesli p-t jest pusty, to f-a rysuje w nim ludka.*/
void RysujLudka(TPoint punkt){
int temp = lab[punkt.y][punkt.x];

  if(temp == ' ') lab[punkt.y][punkt.x] = '@';
}

/*F-a losuje miejsce startu w labiryncie.*/
TPoint LosujMiejsceStartu(){
 TPoint punkt;
 punkt.x = punkt.y = 0;
 Randomize();

 while(lab[punkt.y][punkt.x] == '#'){

 punkt.y = RandomInteger(1, LabX-1);
 punkt.x = RandomInteger(1, LabY-1);
 }
 RysujLudka(punkt);
 return punkt;
}

/*Jesli w p-cie jest ludzik, to f-a go wymazuje.*/
static void WymazLudka(TPoint punkt){
  int temp = lab[punkt.y][punkt.x];

  if(temp == '@') lab[punkt.y][punkt.x] = ' ';
}

/*F-a sprawdza, czy ludzik znalazl wyjscie z labiryntu.*/
static bool CzyKoniec(TPoint punkt){
  if(punkt.x == LabY || punkt.y == LabX || punkt.x == 0 || punkt.y == 0) return TRUE;
  else return FALSE;
}

/*Jest glowna f-a calego programu.
Rekrencyjnie znajduje wyjscie z labiryntu oraz przedstawia je graficznie na ekranie.*/
bool RozwLab(TPoint pt){
  int i, check;
  TPoint temp = pt;
  check = 0;

  if(CzyKoniec(pt) == TRUE){
    RysujLudka(pt);
    RysujLab(lab);
    return TRUE;
  }
  if(CzyZaznaczony(pt) == TRUE) return FALSE;
  RysujLudka(pt);
  RysujLab(lab);

  WymazLudka(pt);
  Zaznacz(pt);

  for(i = 1; i<=4; i++){
    pt = temp;
    check = 0;
    switch (i) {
    case 1:    
      pt.y--;
      if(CzySciana(pt) == FALSE) {
	if(RozwLab(pt) == TRUE) return TRUE;
	else{
	  WymazLudka(pt);
	}
      }
      break;
    case 2:
      pt.x++;
      if(CzySciana(pt) == FALSE) {
	if(RozwLab(pt) == TRUE) return TRUE;
	else{
	  WymazLudka(pt);
	}
      }
      break;
    case 3:
      pt.y++;
      if(CzySciana(pt) == FALSE) {
	if(RozwLab(pt) == TRUE) return TRUE;
	else{
	  WymazLudka(pt);
	}
      }
      break;
    case 4:
      pt.x--;
      if(CzySciana(pt) == FALSE) {
	if(RozwLab(pt) == TRUE) return TRUE;
	else{
	  WymazLudka(pt);
	}
      }
      break;
    }
  }
  Odznacz(temp);
  RysujLudka(temp);
  RysujLab(lab);
  
  return FALSE;
}

/*F-a sprawdza jaka jest wielkosc labiryntu w pliku.
Robi to po to, aby f-a BierzLab wiedziala, ile ma zaalokowac
miejsca w dwuwymiarowej tablicy lab.
NALE¯Y USPRAWNIÆ!
*/
static TPoint SkanujPlik(char *plik[]){
  TPoint punkt;
  int c,i,j;
  FILE *fp;
  i = j = 0;
  punkt.x = 0;
  punkt.y = 0;
  fp = fopen(plik[1], "r");

  if(fp == NULL) printw("BRAK PLIKU!!!");
  else{
    while((c = getc(fp)) != EOF){
      if(c == 10){
	i++;
	j = 0;
      }
      else if(c!=' ' && c!='#' && c!='@' && c!='S')
	return punkt;
      else j++;
    }
  }
  fclose(fp);

  LabX = punkt.x = i;
  LabY = punkt.y = j-1;
  /*  PiszPunkt(punkt);*/
  return punkt;
}

/*F-a przydziela odp. duzo miejsca tablicy lab oraz wpisuje do niej labirynt z pliku.
  NALE¯Y USPRAWNIÆ!*/
int BierzLab(char *plik[]){
  TPoint punkt;
  int c,i,j;
  FILE *fp;
  i = j = 0;
  fp = fopen(plik[1], "r");

  if(fp == NULL) printw("shit...");
  else{
    punkt = SkanujPlik(plik);
    if(punkt.x == 0 && punkt.y == 0) return 0;
    lab = malloc(sizeof(int*)*(punkt.x+1));
    for(i = 0; i<=punkt.x+1; i++)
      lab[i] = malloc(sizeof(int*)*punkt.y);
    i = j = 0;
    while((c = getc(fp)) != EOF){
      if(c == 10){
	i++;
	j = 0;
      }
      else {
	lab[i][j] = c;
	j++;
      }
    }
  }
  return 1;
}

/*F-a sprawdza, ile jest X'ów w labiryncie. 
F-a ta jest pomocna, przy znajdywaniu najkrótszej drogi. */
static int IleX(){
  int wynik = 0;
  int i,j;
  for(i = 0; i<= LabX; i++)
    for(j = 0; j<=LabY; j++){
      if(lab[i][j] == 'X') wynik++;
    }
  return wynik;
}

/*F-a dzia³a na zasadzie f-i RozwLab(), tylko, ¿e nigdy nie znajduje wyj¶cie z labiryntu,
aby przepadaæ wszystkie ¶cie¿ki i dziêki temu sprawdziæ która jest najkrótsza. */
bool FindShortestPath(TPoint pt){
  int i, check;
  TPoint temp = pt;
  check = 0;

  if(CzyKoniec(pt) == TRUE){
    RysujLudka(pt);
    if(IleX() < LICZBA){
      Kopiuj(lab, lab2);
      LICZBA = IleX();
    }
    return 0;
  }
  if(CzyZaznaczony(pt) == TRUE) return FALSE;
  RysujLudka(pt);

  WymazLudka(pt);
  Zaznacz(pt);

  for(i = 1; i<=4; i++){
    pt = temp;
    check = 0;
    switch (i) {
    case 1:    
      pt.y--;
      if(CzySciana(pt) == FALSE) {
	if(FindShortestPath(pt) == TRUE) return TRUE;
	else{
	  WymazLudka(pt);
	}
      }
      break;
    case 2:
      pt.x++;
      if(CzySciana(pt) == FALSE) {
	if(FindShortestPath(pt) == TRUE) return TRUE;
	else{
	  WymazLudka(pt);
	}
      }
      break;
    case 3:
      pt.y++;
      if(CzySciana(pt) == FALSE) {
	if(FindShortestPath(pt) == TRUE) return TRUE;
	else{
	  WymazLudka(pt);
	}
      }
      break;
    case 4:
      pt.x--;
      if(CzySciana(pt) == FALSE) {
	if(FindShortestPath(pt) == TRUE) return TRUE;
	else{
	  WymazLudka(pt);
	}
      }
      break;
    }
  }
  Odznacz(temp);
  RysujLudka(temp);
  /*  RysujLab();*/
  
  return 0;
}

/*F-a przekopiowuje labirynt z lab do lab2. */
void Kopiuj(int **labirynt1, int **labirynt2){
  int i,j;

  for(i = 0; i<= LabX; i++)
    for(j = 0; j<=LabY; j++)
      labirynt2[i][j] = labirynt1[i][j];
}

void SkasujX(int **labirynt){
  int i,j,*temp;
    for(i = 0; i<= LabX; i++)
    for(j = 0; j<=LabY; j++){
      temp = &labirynt[i][j];
      if(*temp == 'X' || *temp == '@') *temp = 32;
    }
}

int SzukajStartu(){
  int i,j;

  for(i = 0; i<= LabX; i++)
    for(j = 0; j<= LabY; j++){
      if(lab[i][j] == 'S'){
	lab[i][j] = '@';
	p->x = j;
	p->y = i;
	return 1;
      }
    }
  return 0;
}
