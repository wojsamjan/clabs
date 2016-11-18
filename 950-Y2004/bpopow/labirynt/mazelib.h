#include <ncurses/curses.h>

typedef struct {
  int x, y;
} TPoint;

TPoint *p;
int **lab;
int **lab2;
int LabX, LabY;
int LICZBA;

void Daj(int a, int b);
void PiszPunkt(TPoint punkt);
void RysujLab(int **labirynt);
TPoint LosujMiejsceStartu();
bool RozwLab(TPoint pt);
int BierzLab(char *plik[]);
bool FindShortestPath(TPoint pt);
void Kopiuj(int **labirynt1, int **labirynt2);
void SkasujX(int **labirynt);
void RysujLudka(TPoint pt);
int SzukajStartu();

