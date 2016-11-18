/*
 *    File: subsets.c
 *    Author: Jacek Siciarek
 *    Date: 2003/10/30
 */

#include <stdio.h>

static void ListSubsets(char str[]);
static void GenerateSubset(int subsetSize);

char napis[]="ABCD";
char binary[64] = "", subset[64] = "";
int rSize = 0, record_subsetSize = 1;

int main()
{
  ListSubsets(napis);
  return 0;
}

static void ListSubsets(char str[])
{
  int tableSize=0;
  while(str[tableSize])tableSize++;

  GenerateSubset(tableSize);
}

static void GenerateSubset(int subsetSize)
{
  int a, b = 0;

  if (record_subsetSize) {rSize = subsetSize;record_subsetSize = 0;}

  if (subsetSize) {
	binary[rSize - subsetSize] = '0'; GenerateSubset(subsetSize - 1);
	binary[rSize - subsetSize] = '1'; GenerateSubset(subsetSize - 1);
  } else {
	for (a = 0; a < rSize; a++) {
	  subset[a]='\0';
	  if (binary[a]=='1'){
		subset[b]=napis[a];
		b++;
	  }
	}
	printf("{%s}\n", subset);
  }
}
