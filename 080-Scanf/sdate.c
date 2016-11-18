#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main () {
  int day, year, month;
  char monthname[20], *line = 0;
  size_t maxline;

  printf("Podaj datę, np. 1 maja 2003 lub 2003/5/1 lub 2 x 2003\n");

  while ((getline(&line, &maxline, stdin)) != -1) {
    if (sscanf(line, "%d %s %d", &day, monthname, &year) == 3)
      printf("ok. poprawna data: %s\n", line); /* format: 1 maja 2003 */
    else if (sscanf(line,"%d/%d/%d", &year, &month, &day) == 3)
      printf("ok. poprawna data: %s\n", line); /* format: 2003/5/1 */
    else
      printf("źle. błędny format: %s\n", line); /* błędny format */
  }
}
