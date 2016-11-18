#include <stdio.h>
#include <stdlib.h> /* atof, exit, EXIT_SUCCESS */
#include <math.h> /* funkcje trygonometryczne */
#include <string.h> /* strcmp */

/* Łącznik? między nazwą funkcji a nią samą. */
struct table_entry 
{
  char *nazwa;
  double (*funkcja)(double);  /* wkaźnik do funkcji zwracającej double */
};

typedef struct table_entry lacznikT;

void pomoc(lacznikT *tp) 
{
  printf("\nUzycie: %s funkcja argument\n", "dtable");
  printf("gdzie argument podajemy w radianach.\n\n");
  printf("Wybierz jedna z funkcji: ");
  fflush(stdout);
  for ( ; tp->nazwa; tp++) printf("%s ", tp->nazwa);
  printf("\n");
  return;
}

/* Tablica łącznikowa z wartownikiem */
lacznikT tablica_lacznikowa[] = {
  {"sin",sin}, {"cos",cos}, {"tan",tan},{NULL,NULL}
};

char *output_format = "\t%s %g = %g\n";


int main(int argc, char *argv[])
{
  lacznikT *tp;
  double argument, odp;
  
  if (argc!=3) { 
    pomoc(tablica_lacznikowa);
    exit(-1);
  }
  for (tp=tablica_lacznikowa; tp->nazwa && strcmp(tp->nazwa,argv[1]); tp++)
    ;
  if (tp->funkcja==NULL) {
    printf("\n! Nieznana funkcja `%s'.\n", argv[1]);
    pomoc(tablica_lacznikowa);
    exit(-1);
  }
  /* oblicz wartosc funkcji dla podanego argumentu */
  argument=atof(argv[2]);
  odp=(*tp->funkcja)(argument) ; 
  printf(output_format, tp->nazwa, argument, odp);

  return EXIT_SUCCESS;
}
