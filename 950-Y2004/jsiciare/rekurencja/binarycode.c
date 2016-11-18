/*  
 *    File: binarycode.c 
 *    Author: Jacek Siciarek
 *    Date: 2003/10/27
 */

#include <stdio.h>
#define BITS 4

static void GenerateBinaryCode(int nBits);

char binary[64] = "";
int cBits = 0, counter = 0, record_nBits = 1;

int main()
{
  GenerateBinaryCode(BITS);
  return 0;
}

static void GenerateBinaryCode(int nBits)
{
  if(record_nBits){cBits = nBits;record_nBits=0;}

  if (nBits) {
	binary[cBits - nBits] = '0'; GenerateBinaryCode(nBits - 1);
	binary[cBits - nBits] = '1'; GenerateBinaryCode(nBits - 1);
  } else {
	printf("%7d -> %s\n", counter++, binary);
  }
}
