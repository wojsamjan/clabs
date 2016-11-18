
#include <stdio.h>
#include <stdlib.h>

/*  wykorzystanie powłoki sh do wywołania programów:
    popen, system, pclose */

/* obie funkcje powinny być zadeklarowane w stdio.h (a nie są?) */
FILE *popen(const char *, const char *);
int pclose(FILE *);

int main() {
  FILE *fp;
  char string[1024];
  /* wywołanie polecenia */
  // system("date");
  /* wywołanie polecenia i przechwycenie jego wyników */
  fp = popen("date", "r");  /* r = odczyt */
  if (fp==NULL)
    fprintf(stderr,"! nie można uruchomić polecenia date\n");
  else {
    fgets(string,1024,fp);
    printf("Wynik wykonania polecenia date: [%s]\n", string);
    pclose(fp);
  }
}
