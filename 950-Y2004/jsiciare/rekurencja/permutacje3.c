/*
 *    File: permutacje3.c
 *    Author: Jacek Siciarek
 *    Date: 2003/11/02
 */

#include <stdio.h>
#include <string.h>
#include <math.h>

char napis[] = "ABBA";

static void ListPermutations(char *s);
static void RecursivePermute(char *s, int k);
static void ExchangeCharacters(char *s, int p1, int p2);

int counter = 0, checksum = 0, new = 1;
int checksums[1024];

int main()
{
  ListPermutations(napis);
  return 0;
}

static void ListPermutations(char *s)
{
  RecursivePermute(s, 0);
}

static void RecursivePermute(char *s, int k)
{
  int i, a;
  checksum = 0; new = 1;

  if (k == strlen(s)) {

	for (a = 0; a < strlen(napis); a++) {
	  checksum <<=8; checksum |= s[a];
	}

	for (a = 0; a < counter; a++) {
	  if (checksums[a] == checksum) {
		new = 0; break;
	  }
	}

	if (new) {
	  printf("%s\n", s); checksums[counter] = checksum; counter++;
	}

  } else {
	for (i = k; i < strlen(s); i++) {
	  ExchangeCharacters(s, k, i);
	  RecursivePermute(s, k + 1);
	  ExchangeCharacters(s, k, i);
	}
  }
}

static void ExchangeCharacters(char *s, int p1, int p2)
{
  char tmp;
  tmp = s[p1];
  s[p1] = s[p2];
  s[p2] = tmp;
}
