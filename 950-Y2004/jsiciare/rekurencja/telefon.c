/*  
 *    File: telefon.c 
 *    Author: Jacek Siciarek
 *    Date: 2003/11/02
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NEWLINE printf("\n       ")
#define COLUMNS 9

static void ListMnemonics(char s[]);
static void GenerateMnemonic(char s[], int i);


static char number[]="997";

#ifdef BEZ1
char telephone[] = "ABCDEFGHIJKLMNOPRSTUVWXZ";int jedynka=6;
#else
char telephone[] = "   ABCDEFGHIJKLMNOPRSTUVWXZ";int jedynka=3;
#endif

char word[64];
int counter=0;


int main()
{
  ListMnemonics(number); 
  return 0;
}

static void ListMnemonics(char s[])
{
  GenerateMnemonic(s,0);
  printf("\n\n");
}

static void GenerateMnemonic(char s[], int i)
{
  int a;

  if(i==(int)strlen(s)){
	if(!(counter%COLUMNS)){NEWLINE;}
	printf("%s  ",word);counter++;
  }else{
	for(a=0;a<3;a++){
	  word[i]=telephone[3*(s[i]-'0')-jedynka+a];
	  GenerateMnemonic(s, i+1);
	}
  }

}
