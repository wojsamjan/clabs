#include <stdio.h>
#include <string.h>
#include "csv1.h"

char *csv_field[20]; /* pola */

static char buf[200]; /* bufor na wczytany wiersz */
static char *unquote(char *); 

int csv_getline(FILE *fin)
{	
  int nfield;
  char *p, *q;

  if (fgets(buf, sizeof(buf), fin) == NULL)
    return -1;
  nfield = 0;
  for (q = buf; (p=strtok(q, ",\n\r")) != NULL; q = NULL)
    csv_field[nfield++] = unquote(p);
  return nfield;
}

/* unquote: usuñ pocz±tkowy i koñcowy znak cudzys³owu */
static char *unquote(char *p)
{
  if (p[0] == '"') {
    if (p[strlen(p)-1] == '"')
      p[strlen(p)-1] = '\0';
    p++;
  }
  return p;
}
