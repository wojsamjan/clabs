/*
    Na przyciskach mojego telefonu przy cyfrach wydrukowano
    następujące litery:

       1 -       6 - MNO
       2 - ABC   7 - PRS
       3 - DEF   8 - TUV
       4 - GHI   9 - WXZ
       5 - JKL   0 -

    Czasami, aby ułatwić zapamiętanie numeru, operator
    podaje słowo. Na przykład

       767   (SOS)
       4357  (HELP)

    itp.

    Napisać funkcję `ListMnemonics' generującą wszystkie
    możliwe kombinacje liter odpowiadające podanej
    liczbie, podanej jako napis złożony z cyfr.
    Na przykład, wywołanie ListMnemonics("723")
    powinno wygenerować następujących 27 trójek:

       PAD PBD PCD RAD RBD RCD SAD SBD SCD
       PAE PBE PCE RAE RBE RCE SAE SBE SCE
       PAF PBF PCF RAF RBF RCF SAF SBF SCF

    Jakie kombinacje liter są przy cyfrach na telefonie
    komórkowym. Czy w tym wypadku Twoje rozwiązanie
    też zadziała?
 */

#include <stdio.h>
#include <stdlib.h>
#include "strlib.h"

char telephone[] = "ABCDEFGHIJKLMNOPRSTUVWXZ";

static void ListMnemonics(char *s);

int main() {
  ListMnemonics("731");
}

static void ListMnemonics(char *s) {
  printf("???\n");
}
