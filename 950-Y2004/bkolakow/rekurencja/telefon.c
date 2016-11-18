/*  
 *  File: telefon.c
 *
 *  $Revision: 1.1.1.1 $
 *  $Date: 2004/01/24 10:40:28 $
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

static void ListMnemonics(char *s);
static void generator(int num, int liczba_cyfr, string str, char *s);

int main()
{
    ListMnemonics("723");
    return EXIT_SUCCESS;
}

static void ListMnemonics(char *s)
{
    int num;
    for (num = 0; s[num] != '\0'; num++);
    generator(num, num, "", s);
}

static void generator(int num, int liczba_cyfr, string str, char *s)
{
    int i, n;
    string temp;

    if (num == 0)
	printf("%s\n", str);
    else {
	for (i = 0; i <= 2; i++) {
	    temp = CopyString(str);
	    n = StringToInteger(SubString
				(s, liczba_cyfr - num, liczba_cyfr - num));
	    str =
		Concat(str,
		       SubString(telephone, (n - 2) * 3 + i,
				 (n - 2) * 3 + i));
	    generator(num - 1, liczba_cyfr, str, s);
	    str = CopyString(temp);
	}
    }
}
