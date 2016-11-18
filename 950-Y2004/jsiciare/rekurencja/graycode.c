/*  
 *    File: graycode.c 
 *    Author: Jacek Siciarek
 *    Date: 2003/10/29
 */

#include <stdio.h>
#define BITS 4

static void GenerateGrayCode(int nBits);

char binary[64] = "", gray[64] = "";
int cBits = 0, counter = 0, record_nBits = 1;

int main()
{
  GenerateGrayCode(BITS);
  return 0;
}

static void GenerateGrayCode(int nBits)
{
  int a;

  if (record_nBits) {cBits = nBits;record_nBits = 0;}

  if (nBits) {
	binary[cBits - nBits] = '0'; GenerateGrayCode(nBits - 1);
	binary[cBits - nBits] = '1'; GenerateGrayCode(nBits - 1);
  } else {
	for (a = cBits - 1; a > 0; a--) {
	  gray[a] = (binary[a] ^ binary[a - 1])?'1':'0';
	}
	gray[0] = binary[0];
	printf("%7d -> %s\n", counter++, gray);
  }
}
