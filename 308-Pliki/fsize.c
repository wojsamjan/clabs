#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>

/*  zob. man stat(2), opendir(3), readdir(2)  */

#include "fsize.h"

#define MAX_PATH 1024

/*  zastosuj funkcję fcn do wszystkich plików w dir  */

void dirwalk(char *dir, void(*fcn)(char *));

/*  funkcja fsize wypisuje rozmiary plików;
    ale jeśli plik jest katalogiem, to fsize
    wywołuje funkcję dirwalk, przetwarzającą
    wszystkie pliki w tym katalogu  */

void fsize(char *name) {
  struct stat stbuf;  /* opis w podręczniku użytkownika funkcji stat */

  if (stat(name, &stbuf) == -1) {
    fprintf(stderr, "fsize: nie mogę znaleźć %s\n", name);
    return;
  }
  if ((stbuf.st_mode & S_IFMT) == S_IFDIR)
    dirwalk(name, fsize);  /* skorowidz: rekurencja */
  printf("%8ld %s\n", stbuf.st_size, name);
}


void dirwalk(char *dir, void(*fcn)(char *)) {
  char name[MAX_PATH];
  struct dirent *dp;
  DIR *dfd;

  if ((dfd = opendir(dir)) == NULL) {
    fprintf(stderr, "dirwalk: nie mogę otworzyć %s\n", dir);
    return;
  }
  while ((dp = readdir(dfd)) != NULL) {
    if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0)
      continue;  /* pomiń siebie i przodka */
    if (strlen(dir) + strlen(dp->d_name) + 2 > sizeof(name))
      fprintf(stderr, "dirwalk: za długa nazwa %s/%s\n", dir, dp->d_name);
    else {
      sprintf(name, "%s/%s", dir, dp->d_name);
      (*fcn)(name);
    }
  }
  closedir(dfd);
}
