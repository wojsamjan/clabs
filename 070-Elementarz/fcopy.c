/*  Plik: fcopy.c
 *
 *  Argumenty wywołania programu oraz pliki w C (zob. też remove_comments.c)
 */

/* Napisać w sposób czytelny część kodu obsługującą
   argumenty wywołania programu. */

#include <stdio.h>

FILE *fin;  /* uchwyt do pliku wejściowego */
FILE *fout;  /* uchwyt do pliku wyjściowego */

int main (int argc, char *argv[]) {
  int c;
  if (argc==3)
    if ((fin=fopen(argv[1],"r"))!=NULL)
      if ((fout=fopen(argv[2],"w"))!=NULL) {
        while ((c=fgetc(fin))!=EOF)
          fputc(c,fout);
        fclose(fin); fclose(fout);
      } else
        printf("Nie mogę otworzyć pliku wyjściowego `%s'\n",argv[2]);
    else
      printf("Nie mogę otworzyć pliku do wejściowego `%s'\n",argv[1]);
  else
    printf("Użycie: copy plik_wejściowy plik_wyjściowy\n");
  return 0;
}
