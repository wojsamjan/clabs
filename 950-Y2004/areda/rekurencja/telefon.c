/*  
 *  w
 *  File: telefon.c
 *
 *  $Revision: 1.1.1.1 $
 *  $Date: 2004/01/24 10:38:52 $
 *
    Na przyciskach mojego telefonu przy cyfrach wydrukowano
    nastêpuj±ce litery:

       1 -       6 - MNO
       2 - ABC   7 - PRS
       3 - DEF   8 - TUV
       4 - GHI   9 - WXZ
       5 - JKL   0 - 

    Czasami, aby u³atwiæ zapamiêtanie numeru, operator
    podaje s³owo. Na przyk³ad

       767   (SOS)
       4357  (HELP)
 
    itp.

    Napisaæ funkcjê `ListMnemonics' generuj±c± wszystkie
    mo¿liwe kombinacje liter odpowiadaj±ce podanej
    liczbie, podanej jako napis z³o¿ony z cyfr.
    Na przyk³ad, wywo³anie ListMnemonics("723")
    powinno wygenerowaæ nastêpuj±cych 27 trójek:

       PAD PBD PCD RAD RBD RCD SAD SBD SCD
       PAE PBE PCE RAE RBE RCE SAE SBE SCE
       PAF PBF PCF RAF RBF RCF SAF SBF SCF

    Jakie kombinacje liter s± przy cyfrach na telefonie
    komórkowym. Czy w tym wypadku Twoje rozwi±zanie 
    te¿ zadzia³a?
 */

#include <stdio.h>
#include <stdlib.h>
#include "strlib.h"

char telephone[] = "ABCDEFGHIJKLMNOPRSTUVWXZ";

static void ListMnemonics(string, string);
string Mnem(char c);

int main() {
  ListMnemonics("731",""); 
  return EXIT_SUCCESS;
}

static void ListMnemonics(string s, string tel) 
{
	int lenS=StringLength(s);
	int lenT=StringLength(tel);
	char c;
	int i;
	string tel1, mnem;
	
	if (lenT>=lenS)
		printf("%s ",tel);
	else
	{
		c=IthChar(s,lenT);
		mnem=Mnem(c);
		
		for (i=0; i<StringLength(mnem); i++)
		{
			tel1=Concat(tel,SubString(mnem,i,i));	
			ListMnemonics(s,tel1);
		}

		printf("\n");
	}
}

string Mnem(char c)
{
	string str="";
	int i;
	char d;
	
	if(c=='0')
		return "0";
	else if (c=='1')
		return "1";
	else 
	{
		for(i=0; i<3; i++)
		{
			d=telephone[(c-'2')*3 + i];
			str=Concat(str,CharToString(d));
		}
		return str;
	}
}
