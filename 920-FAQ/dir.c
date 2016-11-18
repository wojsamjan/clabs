/* Plik: dir.c
 * -------------
 * Program ten wypisuje pliki z bie¿±cego katalogu.
 * 
 * Wersja z dnia: 10.XII.2000
 */

#include <stdio.h>  /* NULL */
#include <dirent.h> /* opendir, readdir */

int main() {
    DIR           *dir_p;
    struct dirent *dir_entry_p;

    dir_p = opendir(".");  /* open the current directory */
    /* print the name of the file held in this directory entry */
    while( NULL != (dir_entry_p = readdir(dir_p))) /* read each entry until NULL */
      printf(" %s \n", dir_entry_p->d_name);
    closedir(dir_p);

    return 0;
}
