#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINES 100
#define MAXLEN 80

void read_lines(char *filename, char *array[], int *n);
void write_lines(char *filename, char *array[], int n);

int lines_cmp(const void *a, const void *b) {
  return strcmp(*(char **)a, *(char **)b);
}

int main(int argc, char *argv[]) {
  char *text[MAXLINES];
  int total;

  read_lines(argv[1], text, &total);
  qsort(text, total, sizeof(char *), lines_cmp);
  write_lines(argv[2], text, total);
}

void read_lines(char *filename, char *array[], int *n) {
  FILE *fin;
  char buffer[MAXLEN];
  int total = 0;

  if ((fin = fopen(filename, "r")) == NULL) {
    printf("Nie mogę otworzyć pliku do czytania '%s'.\n", filename);
    exit(1);
  }

  while (fgets(buffer, MAXLEN, fin) != NULL) {
    if (total >= MAXLINES) {
      fprintf(stderr,"Za dużo linii do posortowania.\n");
      break;
    }
    array[total] = malloc(MAXLEN);
    strcpy(array[total], buffer);
    total++;
  }
  *n = total;
}

void write_lines(char *filename, char *array[], int n) {
  FILE *fout;

  if ((fout = fopen(filename, "w")) == NULL) {
    printf("Nie mogę otworzyć pliku do zapisu '%s'\n", filename);
    exit(2);
  }

  for (int i = 0; i < n; i++)
    fprintf(fout, "%s", array[i]);
}
