#!/bin/ch

/* W terminologii języka Ch ten plik
   jest skryptem (ang script).
   Skrypt to program bez funkcji `main'
   lub program zaczynający się od `#!/bin/ch'.

   Każdy skrypt można uruchomić z linii poleceń
   o ile dostępny jest program `/bin/ch'.
*/

printf("\nCześć użytkowniku %s\n",  _user);
printf("\nBieżący katalog zawiera następujace pliki:\n");
ls
