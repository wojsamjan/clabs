/*   
     $URL: http://manta.univ.gda.pl/svn/wb/labs/c/520-BigInt/div1.c $
     $Revision: 195 $
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*   8585 : 7  = 1226 reszta 3
     
     8, 5, 8, 5  :  7  =  1
       15, 8, 5  :  7  =  2
          18, 5  :  7  =  2
             45  :  7  =  6  reszta:  3
*/

void div1(?) {
  return;
}

int main(int argc, char *argv[]) {
  int x, y;

  if (argc != 3 && strlen(argv[2]) != 1) {
    printf("\tUżycie: div licznik mianownik[jedna cyfra]\n");
    return EXIT_FAILURE;
  }

  printf("wynik dzielenia\n");

  return EXIT_SUCCESS;
}
