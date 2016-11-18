/*  
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

int main() {
  ListMnemonics("731"); 
  return EXIT_SUCCESS;
}

static void ListMnemonics(char *s) {
  printf("???\n");
}
