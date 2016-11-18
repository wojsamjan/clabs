/*
    BUGS:
     ta wersja usuwa komentarze w napisach, na przykład
     "/\gwiazdka takie jak ten \gwiazdka/"

    Implementacja `table driven' DFA usuwającego komentarze
 */

#include <stdio.h>
#include <stdlib.h>

int error(int);

int main() {
  int accept[7];  /* DFA ma 6 stanów */
  int T[7][257];  /* tablica przejść */
  int advance[7][257];  /* przejścia po których czytany jest znak z wejścia */
  int c, state, newstate;
  int i, j;

  /* inicjalizacja tablicy accept */
  /* tylko stan 5 jest akceptujący; stan 6 daje błąd */
  for (i=0; i<6; i++)
    accept[i]=0;
  accept[5]=1;

  /* inicjalizacja tablicy T */
  for (i=0; i<7; i++)
    for (j=0; j<257; j++)
      T[i][j]=0;
  T[1]['/']=2; T[1]['*']=1; T[1][256]=5;  /* EOF -> 256 */
  T[2]['/']=1; T[2]['*']=3; T[2][256]=5;
  T[3]['/']=3; T[3]['*']=4; T[3][256]=6;
  T[4]['/']=1; T[4]['*']=4; T[4][256]=6;
  T[5]['/']=5; T[5]['*']=5; T[5][256]=5;

  for (j=1; j<256; j++)
    if (j!='/' && j!='*')
      T[1][j]=1;
  for (j=1; j<256; j++)
    if (j!='/' && j!='*')
      T[2][j]=1;
  for (j=1; j<256; j++)
    if (j!='/' && j!='*')
      T[3][j]=3;
  for (j=1; j<256; j++)
    if (j!='/' && j!='*')
      T[4][j]=3;
  for (j=1; j<256; j++)
    if (j!='/' && j!='*')
      T[5][j]=5;


  /* inicjalizacja tablicy advance */
  for (i=0; i<7; i++)
    for (j=0; j<256; j++)
      advance[i][j]=1;

  /* automat */
  state=1;
  c=getchar();

  while (!accept[state] && !error(state)) {
    newstate=T[state][(unsigned int)c];

    /* output */
    if (state==1 && newstate==1)
      putchar(c);
    if (state==2 && newstate==5)
      putchar('/');
    if (state==2 && newstate==1) {
      putchar('/');
      putchar(c);
    }

    if (advance[state][(unsigned int)c]) {
      c=getchar();
      if (c==EOF)
        c=256;
    }
    state=newstate;
  }
  return error(state);
}

int error(int state)
{
  if (state==6) {
    return 11;
  } else {
    return 0;
  }
}
